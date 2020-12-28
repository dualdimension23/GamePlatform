//
// Created by n00b on 28.12.20.
//

#ifndef GAMEPROJECT_GAMEKEY_H
#define GAMEPROJECT_GAMEKEY_H
#include "player.h"

class Game;
class gamekey{
    gamekey() {}
    friend bool Player :: join_game(std::shared_ptr<Game>);
    friend bool Player :: leave_game(std::shared_ptr<Game>);
};
#endif //GAMEPROJECT_GAMEKEY_H
