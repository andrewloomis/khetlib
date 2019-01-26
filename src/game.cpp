#include "game.h"
#include "pyramid.h"
#include "djed.h"
#include "obelisk.h"
#include "pharoah.h"
#include <QDebug>

Game::Game()
{
    startGame();
}

void Game::startGame()
{
    pieces.push_back(std::make_shared<Pyramid>(7,0,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(2,1,0,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(0,3,180,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(0,4,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(6,5,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(7,3,270,Color::Red));
    pieces.push_back(std::make_shared<Pyramid>(7,4,180,Color::Red));
    pieces.push_back(std::make_shared<Obelisk>(6,0,0,Color::Red));
    pieces.push_back(std::make_shared<Obelisk>(4,0,0,Color::Red));
    pieces.push_back(std::make_shared<Pharoah>(5,0,0,Color::Red));

    pieces.push_back(std::make_shared<Pyramid>(3,2,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,3,0,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,4,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(2,7,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(9,3,90,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(9,4,0,Color::Grey));
    pieces.push_back(std::make_shared<Pyramid>(7,6,180,Color::Grey));
    pieces.push_back(std::make_shared<Obelisk>(3,7,0,Color::Grey));
    pieces.push_back(std::make_shared<Obelisk>(5,7,0,Color::Grey));
    pieces.push_back(std::make_shared<Pharoah>(4,7,180,Color::Grey));

    pieces.push_back(std::make_shared<Djed>(4,3,0,Color::Red));
    pieces.push_back(std::make_shared<Djed>(5,3,90,Color::Red));
    pieces.push_back(std::make_shared<Djed>(4,4,90,Color::Grey));
    pieces.push_back(std::make_shared<Djed>(5,4,0,Color::Grey));

    int i = 0;
    for (auto& piece : pieces)
    {
        piece->setIndex(i++);
    }
}

Color Game::getPieceColor(std::size_t index) const
{
    return pieces[index]->color();
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
        if ((piece->canSwap() && otherPiece->type() == PieceType::Pyramid) ||
                otherPiece->isKilled())
            continue;
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

QList<int> Game::calculateBeamCoords(int startX, int startY)
{
    // Coords in sets of 3:
    // 0 - Xcoord
    // 1 - Ycoord
    // 2 - Termination Type (0 is wall, 1 is piece)

    QList<int> coords;
    std::shared_ptr<Piece> targetPiece = nullptr;
    bool terminated = false;
    Position reflectorPosition = Position{startX, startY == 0 ? -1 : 8};
    Direction laserDirection = startY == 0 ? Direction::PosY : Direction::NegY;
    int reflections = 0;
    while (!terminated)
    {
        // Path search
        for (const auto& piece : pieces)
        {
            bool pieceIsNotKilled = !piece->isKilled();
            bool pieceIsInPathOfBeam = isBeamVertical(reflections) ?
                        piece->position().x == reflectorPosition.x :
                        piece->position().y == reflectorPosition.y;
            bool pieceIsAheadOfReflector = isBeamVertical(reflections) ? (laserDirection == Direction::NegY ?
                       piece->position().y < reflectorPosition.y :
                       piece->position().y > reflectorPosition.y) :
                       (laserDirection == Direction::NegX ?
                       piece->position().x < reflectorPosition.x :
                       piece->position().x > reflectorPosition.x);

            if (pieceIsNotKilled && pieceIsInPathOfBeam &&
                pieceIsAheadOfReflector)
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
            switch (targetPieceInteraction)
            {
            case Interaction::Kill:
                qDebug() << "Piece" << targetPiece->index() << "Killed";
                targetPiece->setKilled();
                emit pieceKilled(targetPiece->index());
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
