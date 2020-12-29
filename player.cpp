//
// Created by n00b on 28.12.20.
//

#include "player.h"
#include "game.h"
#include "gamekey.h"
#include<string>
#include<iostream>
#include<memory>
#include<algorithm>
#include<vector>
#include<map>

Player :: Player(std::string name, int mmr): name { name }, mmr { mmr }
{
   if (name.size() == 0 || (mmr > 9999 || mmr < 0))
       throw std::runtime_error("Name ist leer! Oder MMR > 9999 || MMR < 0");
}

std::string Player :: get_name() const { return name; }

int Player :: get_mmr() const { return mmr; }

std::shared_ptr<Game> Player :: get_hosted_game() const { return hosted_game; }

void Player :: change_mmr(int n)
{
    int newMmr { mmr + n };
    if(newMmr > 9999 || newMmr < 0) return;
    else
        mmr = newMmr;
}

bool Player :: host_game(std::string s, Mode m)
{
    if (s.size() == 0) throw std::runtime_error("Name darf nicht leer sein!");
    if (hosted_game == nullptr) {
        // Maybe need std::unique_ptr here
        std::shared_ptr<Game> newGame;
        switch(m) {
            case Mode::Unranked:
                hosted_game = std::make_shared<UGame>(s, shared_from_this());
                return true;

            case Mode::Ranked:
                hosted_game = std::make_shared<RGame>(s, shared_from_this());
                return true;
        }
        return false;
    }
    return false;
}

bool Player :: join_game(std::shared_ptr<Game> game) {
   if(game->add_player(gamekey(), shared_from_this())) {
      const auto [it, success] = games.insert_or_assign(game->get_name(), game);
      if(!success && (*it).second.expired()) {
         games[game->get_name()] = game;
         return true;
      }
      return success;
   }
   return false;
}
bool Player :: leave_game(std::shared_ptr<Game> game) {
    bool removedGame { false };
    auto it { games.find(game->get_name()) };
    if(it != games.end()) {
        games.erase(it);
        removedGame = true;
    }
    bool removedPlayer { game->remove_player(gamekey(), shared_from_this()) };
    return removedGame && removedPlayer;
}
std::vector<std::weak_ptr<Player>> Player :: invite_players(const std::vector<std::weak_ptr<Player>>& players) {
   std::vector<std::weak_ptr<Player>> returnVector;
   for(auto it { players.begin() }; it != players.end(); ++it) {
      bool joinedGame { false };
      std::shared_ptr<Player> p { it->lock() };
      if(p) {
          joinedGame = p->join_game(get_hosted_game());
      }
      if(!joinedGame)
          returnVector.push_back(*it);
   }
   return returnVector;
}

bool Player :: close_game() {
   if(hosted_game) {
       hosted_game.reset();
       return true;
   }
   return false;
}
std::ostream& Player :: print(std::ostream& o) const {
    o << '[';
    o << get_name() << ", ";
    o << get_mmr() << ", ";
    if (hosted_game)
        o << "hosts: " << hosted_game->get_name() << ", ";
    o << "games: " << "{";
    bool isFirst { true };
    for(const auto& g : games) {
        if (g.second.expired())
            continue;
        if (!isFirst)
            o << ", ";
        isFirst = false;
        o << g.first;
    }
    o << "}]";
    return o;
}
std::ostream& operator<<(std::ostream& o, const Player& p) {
    p.print(o);
    return o;
}
