#include "game.h"
#include "pyramid.h"

Game::Game()
{
    startGame();
}

void Game::startGame()
{
    pieces[0] = Pyramid(5,5,90,Color::Grey);
}

int Game::possibleTranslationsForPiece(const Piece& piece)
{
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
    return possibleTranslations;
}