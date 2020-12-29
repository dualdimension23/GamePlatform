//
// Created by n00b on 28.12.20.
//

#ifndef GAMEPROJECT_GAME_H
#define GAMEPROJECT_GAME_H


#include<string>
#include<iostream>
#include<algorithm>
#include<memory>
#include<vector>
#include<map>


class gamekey;
class Player;
class Game: public std::enable_shared_from_this<Game> {
private:
    std::string name;
    std::shared_ptr<Player> host;
    std::map<std::string, std::shared_ptr<Player>> players;
public:
    Game();
    Game(std::string, std::shared_ptr<Player>);
    virtual ~Game();

    std::string get_name() const;
    bool is_allowed(int) const;
    bool remove_player(const gamekey&, std::shared_ptr<Player>);
    bool add_player(const gamekey&, std::shared_ptr<Player>);
    std::shared_ptr<Player> best_player() const;
    size_t number_of_players() const;
    virtual int change(bool) const = 0;
    virtual std::ostream& print(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Game&);
    std::shared_ptr<Player> play(size_t);
};

class RGame: public Game {
public:
    RGame(std::string, std::shared_ptr<Player>);
    int change(bool x) const;
    std::ostream& print(std::ostream&) const;
};

class UGame: public Game {
public:
    UGame(std::string, std::shared_ptr<Player>);
    int change(bool x) const;
    std::ostream& print(std::ostream&) const;
};



#endif //GAMEPROJECT_GAME_H
