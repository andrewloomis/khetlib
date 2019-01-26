#ifndef PLAYER_H
#define PLAYER_H

#include "khettypes.h"
#include <QString>

class Player
{
public:
    Player() {}
    Player(QString name) { username = name; }
    Color pieceColor() const { return mColor; }
    void setColor(Color color) { mColor = color; }
    QString getUsername() const { return username == "" ?
                    "Unknown" : username; }
    void setUsername(QString name) { username = name; }
    bool isLoggedIn() { return username == "" ? false : true; }
    void logout() { username = ""; }
    bool operator==(const Player& otherPlayer)
    {
        return username == otherPlayer.getUsername();
    }

private:
    QString username;
    Color mColor;
};

#endif // PLAYER_H
