#include "game.h"
#include "pyramid.h"
#include <QDebug>

Game::Game()
{
    startGame();
}

void Game::startGame()
{
    pieces.push_back(std::make_shared<Pyramid>(0,4,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(9,5,90,Color::Red));
    int i = 0;
    for (auto& piece : pieces)
    {
        piece->setIndex(i++);
    }
}

int Game::possibleTranslationsForPiece(std::size_t index)
{
    std::shared_ptr<Piece> piece = pieces[index];
    int possibleTranslations = 255;
    if (piece->position().x == 0) {
        possibleTranslations &= ~(Translations::Left | 
            Translations::BottomLeft | Translations::TopLeft);
    }
    if (piece->position().x == 9) {
        possibleTranslations &= ~(Translations::Right | 
            Translations::BottomRight | Translations::TopRight);
    }
    if (piece->position().y == 0) {
        possibleTranslations &= ~(Translations::Top | 
            Translations::TopLeft | Translations::TopRight);
    }
    if (piece->position().y == 7) {
        possibleTranslations &= ~(Translations::Bottom | 
            Translations::BottomLeft | Translations::BottomRight);
    }
    for (auto otherPiece : pieces)
    {
        if (otherPiece->position().x == piece->position().x - 1) {
            if (otherPiece->position().y == piece->position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomLeft);
            }
            else if (otherPiece->position().y == piece->position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopLeft);
            }
            else if (otherPiece->position().y == piece->position().y)
            {
                possibleTranslations &= ~(Translations::Left);
            }
        }
        else if (otherPiece->position().x == piece->position().x + 1) {
            if (otherPiece->position().y == piece->position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomRight);
            }
            else if (otherPiece->position().y == piece->position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopRight);
            }
            else if (otherPiece->position().y == piece->position().y)
            {
                possibleTranslations &= ~(Translations::Right);
            }
        }
        else if (otherPiece->position().x == piece->position().x &&
                 otherPiece->position().y == piece->position().y + 1)
        {
            possibleTranslations &= ~(Translations::Bottom);
        }
        else if (otherPiece->position().x == piece->position().x &&
                 otherPiece->position().y == piece->position().y - 1)
        {
            possibleTranslations &= ~(Translations::Top);
        }
    }
    return possibleTranslations;
}

void Game::updatePiecePosition(std::size_t index, int x, int y)
{
    auto& piece = pieces[index];
    piece->setPosition(x,y);
}

void Game::updatePieceAngle(std::size_t index, int angle)
{
    auto& piece = pieces[index];
    piece->setAngle(angle);
}

bool isBeamVertical(int& reflections)
{
    return reflections % 2 == 0;
}

QList<int> Game::calculateBeamCoords() const
{
    // Coords in sets of 3:
    // 0 - Xcoord
    // 1 - Ycoord
    // 2 - Termination Type (0 is wall, 1 is piece)

    QList<int> coords;
    std::shared_ptr<Piece> targetPiece = nullptr;
    bool terminated = false;
    Position reflectorPosition = Position{9,7};
    Direction laserDirection = Direction::NegY;
    int reflections = 0;
    while (!terminated)
    {
        // Path search
        for (const auto& piece : pieces)
        {
            bool pieceIsInPathOfBeam = isBeamVertical(reflections) ?
                        piece->position().x == reflectorPosition.x :
                        piece->position().y == reflectorPosition.y;
            bool pieceIsNotReflector = piece->position() != reflectorPosition;
            if (pieceIsInPathOfBeam && pieceIsNotReflector)
            {
                if (targetPiece == nullptr)
                {
                    targetPiece = piece;
                    continue;
                }
                bool pieceIsAheadOfTargetPiece = isBeamVertical(reflections) ? (laserDirection == Direction::NegY ?
                           piece->position().y > targetPiece->position().y :
                           piece->position().y < targetPiece->position().y) :
                           (laserDirection == Direction::NegX ?
                           piece->position().x > targetPiece->position().x :
                           piece->position().x < targetPiece->position().x);
                if (pieceIsAheadOfTargetPiece)
                {
                    targetPiece = piece;
                }
            }
        }
        // No piece in path
        if (targetPiece == nullptr)
        {
            qDebug() << "Beam hit wall";

            if (isBeamVertical(reflections))
            {
                int opposingWallY = laserDirection == Direction::NegY ? 0 : 7;
                coords << reflectorPosition.x << opposingWallY << 0;
            }
            else {
                int opposingWallX = laserDirection == Direction::NegX ? 0 : 9;
                coords << opposingWallX << reflectorPosition.y << 0;
            }
            terminated = true;
            break;
        }
        // Piece intercepted
        else
        {
            coords << targetPiece->position().x << targetPiece->position().y << 1;
            Interaction targetPieceInteraction = targetPiece->laserInteraction(laserDirection);
            qDebug() << "Piece" << targetPiece->index() << "intercepted laser from"
                     << (int)laserDirection << ", reflecting" << (int)targetPieceInteraction;
            switch (targetPieceInteraction)
            {
            case Interaction::Kill:
                qDebug() << "Piece" << targetPiece->index() << "Killed";
                terminated = true;
                break;
            case Interaction::ReflectNegX:
                qDebug() << "Piece" << targetPiece->index() << "Reflecting NegX";
                laserDirection = Direction::NegX;
                break;
            case Interaction::ReflectPosX:
                qDebug() << "Piece" << targetPiece->index() << "Reflecting PosX";
                laserDirection = Direction::PosX;
                break;
            case Interaction::ReflectNegY:
                qDebug() << "Piece" << targetPiece->index() << "Reflecting NegY";
                laserDirection = Direction::NegY;
                break;
            case Interaction::ReflectPosY:
                qDebug() << "Piece" << targetPiece->index() << "Reflecting PosY";
                laserDirection = Direction::PosY;
                break;
            case Interaction::Error:
                qDebug() << "Piece" << targetPiece->index() << "Interaction error";
            }
            reflections++;
            reflectorPosition = targetPiece->position();
            // Clearing to hand off targetPiece to next target
            targetPiece = nullptr;
        }
    }
    return coords;
}