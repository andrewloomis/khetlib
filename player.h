#ifndef PLAYER_H
#define PLAYER_H

#include "khettypes.h"
#include <QString>

class Player
{
public:
    Player();
    Color pieceColor() const { return color; }
    QString getUsername() const { return username == "" ?
                    "Unknown" : username; }
    void setUsername(QString name) { username = name; }
    bool isLoggedIn() { return username == "" ? false : true; }
    void logout() { username = ""; }

private:
    QString username;
    Color color = Color::Grey;
};

#endif // PLAYER_H
