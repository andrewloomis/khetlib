#include "game.h"
#include "pyramid.h"

Game::Game()
{
    startGame();
}

void Game::startGame()
{
    pieces[0] = Pyramid(5,5,90,Color::Red);
    pieces[1] = Pyramid(1,1,90,Color::Red);
}

int Game::possibleTranslationsForPiece(std::size_t index)
{
    Piece piece = pieces[index];
    int possibleTranslations = 255;
    if (piece.position().x == 0) {
        possibleTranslations &= ~(Translations::Left | 
            Translations::BottomLeft | Translations::TopLeft);
    }
    if (piece.position().x == 9) {
        possibleTranslations &= ~(Translations::Right | 
            Translations::BottomRight | Translations::TopRight);
    }
    if (piece.position().y == 0) {
        possibleTranslations &= ~(Translations::Top | 
            Translations::TopLeft | Translations::TopRight);
    }
    if (piece.position().y == 7) {
        possibleTranslations &= ~(Translations::Bottom | 
            Translations::BottomLeft | Translations::BottomRight);
    }
    for (auto& otherPiece : pieces)
    {
        if (otherPiece.position().x == piece.position().x - 1) {
            if (otherPiece.position().y == piece.position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomLeft);
            }
            else if (otherPiece.position().y == piece.position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopLeft);
            }
            else if (otherPiece.position().y == piece.position().y)
            {
                possibleTranslations &= ~(Translations::Left);
            }
        }
        else if (otherPiece.position().x == piece.position().x + 1) {
            if (otherPiece.position().y == piece.position().y + 1)
            {
                possibleTranslations &= ~(Translations::BottomRight);
            }
            else if (otherPiece.position().y == piece.position().y - 1)
            {
                possibleTranslations &= ~(Translations::TopRight);
            }
            else if (otherPiece.position().y == piece.position().y)
            {
                possibleTranslations &= ~(Translations::Right);
            }
        }
        else if (otherPiece.position().x == piece.position().x &&
                 otherPiece.position().y == piece.position().y + 1)
        {
            possibleTranslations &= ~(Translations::Bottom);
        }
        else if (otherPiece.position().x == piece.position().x &&
                 otherPiece.position().y == piece.position().y - 1)
        {
            possibleTranslations &= ~(Translations::Top);
        }
    }
    return possibleTranslations;
}

void Game::updatePiecePosition(std::size_t index, int x, int y, int angle)
{
    auto& piece = pieces[index];
    piece.setPosition(x,y,angle);
}

QList<int> Game::calculateBeamCoords() const
{
    // Coords in sets of 3:
    // 0 - Xcoord
    // 1 - Ycoord
    // 2 - Interaction Type (0 is wall, 1 is piece)

    QList<int> coords;
    const Piece* nextPiece = nullptr;
    bool terminated = false;
    for (auto& piece : pieces)
    {
        if (piece.position().x == 9)
        {
            if (nextPiece == nullptr || piece.position().y > nextPiece->position().y)
            {
                nextPiece = &piece;
            }
        }
    }
    if (nextPiece == nullptr)
    {
        coords << 9 << 0 << 0;
        terminated = true;
    }
    else
    {
        coords << nextPiece->position().x << nextPiece->position().y << 1;
        Interaction nextPieceInteraction = nextPiece->laserInteraction(Direction::NegY);
        Position lastPosition = nextPiece->position();
        nextPiece = nullptr;
        if (nextPieceInteraction != Interaction::Kill)
        {
            for (auto& piece : pieces)
            {
                if (piece.position().y == lastPosition.y && piece.position().x != lastPosition.x)
                {
                    if (nextPiece == nullptr || piece.position().x > nextPiece->position().x)
                    {
                        nextPiece = &piece;
                        nextPieceInteraction = nextPiece->laserInteraction(Direction::NegX);
                    }
                }
            }
            if (nextPiece == nullptr)
            {
                coords << 0 << lastPosition.y << 0;
                terminated = true;
            }
            else
            {
                coords << nextPiece->position().x << nextPiece->position().y << 1;
            }
        }
    }

//    while (!terminated)
//    {

//    }

    return coords;
}
