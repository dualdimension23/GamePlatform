//
// Created by n00b on 28.12.20.
//
#ifndef GAMEPROJECT_PLAYER_H
#define GAMEPROJECT_PLAYER_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>

class Game;

enum class Mode{Ranked,Unranked};

class Player: public std::enable_shared_from_this<Player>{
private:
    std::string name;
    int mmr;
    std::shared_ptr<Game> hosted_game { nullptr };
    std::map<std::string, std::weak_ptr<Game>> games;

public:
    Player(std::string, int);
    std::string get_name() const;
    int get_mmr() const;
    std::shared_ptr<Game> get_hosted_game() const;
    void change_mmr(int);
    bool host_game(std::string, Mode);
    bool join_game(std::shared_ptr<Game>);
    bool leave_game(std::shared_ptr<Game>);
    std::vector<std::weak_ptr<Player>> invite_players(const std::vector<std::weak_ptr<Player>>&);
    bool close_game();
    std::ostream& print(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const Player&);

};


#endif //GAMEPROJECT_PLAYER_H
