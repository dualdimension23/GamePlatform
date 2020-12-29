//
// Created by n00b on 29.12.20.
//

#ifndef GAMEPROJECT_TESTER_H
#define GAMEPROJECT_TESTER_H

#include<experimental/iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include "game.h"
#include "player.h"
#include "gamekey.h"

class Player;
class Game;
class Tester {
private:
    std::vector<std::shared_ptr<Player>> _players {
            std::make_shared<Player>("Bernhard", 200),
            std::make_shared<Player>("Hans", 257),
            std::make_shared<Player>("Alex", 99),
            std::make_shared<Player>("Markus", 199),
            std::make_shared<Player>("Clemens", 999),
            std::make_shared<Player>("Anatol", 1027),
            std::make_shared<Player>("Georgia", 100),
            std::make_shared<Player>("Niko", 567),
            std::make_shared<Player>("Noah", 301),
            std::make_shared<Player>("Philipp", 700),
            std::make_shared<Player>("David", 601),
            std::make_shared<Player>("Heinisch", 304)
    };
    std::vector<std::weak_ptr<Player>> _wplayers { _players.begin(), _players.end() };
    const std::vector<std::string> gameNames {"LoL", "Wild Rift", "Among Us"};

public:
    Tester();
    void test_host_game();
    void test_best_player();
    void test_join_game();
    void test_invite_players();
    void test_play_game();
    void test_leave_game();
    void test_close_game();
    void test_host_again();
    void test();
};


#endif //GAMEPROJECT_TESTER_H
