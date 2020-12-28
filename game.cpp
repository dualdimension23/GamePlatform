//
// Created by n00b on 28.12.20.
//

#include "game.h"
#include "player.h"
#include "gamekey.h"

Game::Game(std::string name, std::shared_ptr<Player> host): name { name }, host { host } {
    if (name.size() == 0 or host == nullptr) throw std::runtime_error("Name darf nicht leer sein und es muss ein Host gewählt werden!");
}

std::string Game::get_name() const { return this->name; }

// TODO:
bool Game::is_allowed(int n) const {
    int hostScore { host->get_mmr() };
    double ratio { n / static_cast<double>(hostScore) };
    return (ratio > 0.9 && ratio < 1.1);
}

bool Game::remove_player(const gamekey& gk, std::shared_ptr<Player> p) {
    auto it { players.find(p->get_name()) };
    if(it != players.end()) {
        players.erase(it);
        return true;
    } else
        return false;
}

bool Game::add_player(const gamekey& gk, std::shared_ptr<Player> p) {
    // Still stuff TODO
    auto it { players.find(p->get_name()) };
    if(it != players.end())
        return false;
    else {
        auto newPair { std::make_pair(p->get_name(), p) };
        if(is_allowed(p->get_mmr())) {
            players.insert(newPair);
            return true;
        }
    }
    return false;
}

std::shared_ptr<Player> Game::best_player() const {
    std::shared_ptr<Player> bestPlayer { nullptr };
    if (players.size() == 0)
        throw std::runtime_error("No players!");
    else {
        int maxScore { 0 };
        for(const auto& player : players) {
            int playerScore { player.second->get_mmr() };
            if(playerScore > maxScore)
                bestPlayer = player.second;
        }
    }
    return bestPlayer;
}

size_t Game::number_of_players() const { return players.size(); }

std::shared_ptr<Player> Game::play(size_t i) {
    // Find winner
    size_t index { 0 };
    std::shared_ptr<Player> winner { nullptr };
    for(const auto& p : players) {
        if(index == i)
            winner = p.second;
        ++index;
    }
    int winnerScore { winner->get_mmr() };

    index = 0;
    for(const auto& p : players) {
        if(index != i) {
           if(p.second->get_mmr() > winnerScore)
               p.second->change_mmr(2 * change(false));
           else
               p.second->change_mmr((change(false)));
        } else {
            p.second->change_mmr(change(true));
        }
    }
    return winner;
}

Game::~Game() = default;

std::ostream& Game::print(std::ostream& o) const {
    bool is_first { true };
    o << '[';
    o << get_name() << ", ";
    o << host->get_name() << ", ";
    o << host->get_mmr() << ", ";
    o << "player: ";
    for(const auto& player : players) {
        if(!is_first) {
            is_first = false;
            o << ", ";
        }
        o << '[' << player.second->get_name();
        o << ", " << player.second->get_mmr();
        o << ']';
    }
    o << ']';
    return o;
}

UGame :: UGame(std::string s, std::shared_ptr<Player> p): Game(s,p) {}
int UGame :: change(bool x) const {
    return 0;
}

std::ostream& UGame :: print(std::ostream& o) {
   o << "Unranked Game: ";
   o << this;
   return o;
}

RGame :: RGame(std::string s, std::shared_ptr<Player> p): Game(s,p) {}
int RGame :: change(bool x) const {
    int returnMmr { 0 };
    x ? returnMmr = 5 : returnMmr = -5;
    return returnMmr;
}

std::ostream& RGame :: print(std::ostream& o) {
    o << "Ranked Game: ";
    o << this;
    return o;
}
