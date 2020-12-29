//
// Created by n00b on 29.12.20.
//

#include "Tester.h"
#include <algorithm>

Tester :: Tester() { test(); };

void Tester :: test_host_game() {
    std::cout << "Host: " << (_players.at(0)->host_game(gameNames.at(0), Mode::Ranked)) << '\n';
    std::cout << "Host: " << (_players.at(0)->host_game(gameNames.at(1), Mode::Ranked)) << '\n';
    try {
        std::cout << "Host: " << (_players.at(1)->host_game("", Mode::Ranked));
    } catch (std::runtime_error& e) {
        std::cout << "Error: Game name is empty!\n";
    }
    std::cout << "Host: " << (_players.at(2)->host_game(gameNames.at(0), Mode::Unranked)) << '\n';
    std::cout << "Host: " << (_players.at(2)->host_game(gameNames.at(1), Mode::Unranked)) << '\n';
}

void Tester :: test_best_player() {
    try {
        std::cout << "Best: " << (_players.at(2)->get_hosted_game()->best_player()) << '\n';
        std::cout << "There should not be a best player!\n";
    } catch (std::runtime_error& e) {
        std::cout << "Error Best\n";
    }
}

void Tester :: test_join_game() {
    auto game { _players.at(0)->get_hosted_game() };
    std::vector<int> v1 {1, 0, 0, 0, 0};
    std::vector<int> v2;
    if (game) {
       v2.push_back(_players.at(0)->join_game(game));
       v2.push_back(_players.at(0)->join_game(game));
       v2.push_back(_players.at(1)->join_game(game));
       v2.push_back(_players.at(7)->join_game(game));
       v2.push_back(_players.at(8)->join_game(game));
       if (v2.size() == v1.size() && std::equal(v1.begin(), v1.end(), v2.begin())) {
          std::cout << "CASE [" << game->get_name() << "] Check.\n";
       }
    }
    v1.clear();
    v2.clear();

    game = _players.at(1)->get_hosted_game();
    v1 = {0, 0, 1, 0, 0};
    if (game) {
        v2.push_back(_players.at(0)->join_game(game));
        v2.push_back(_players.at(0)->join_game(game));
        v2.push_back(_players.at(1)->join_game(game));
        v2.push_back(_players.at(7)->join_game(game));
        v2.push_back(_players.at(8)->join_game(game));
        if (v2.size() == v1.size() && std::equal(v1.begin(), v1.end(), v2.begin())) {
            std::cout << "Should not be equal!\n";
        }
    }
    if (!game)
        std::cout << "CASE [" << _players.at(1)->get_name() << "] Check.\n";
    game = _players.at(2)->get_hosted_game();
    if (game) {
        std::cout << *game << '\n';
        for(auto p : _players)
            std::cout << "Join: " << (p->join_game(game)) << '\n';
        std::cout << *game << '\n';
    }
}

void Tester :: test_invite_players() {
    auto v1{ _players.at(0)->invite_players(_wplayers) };
    std::cout << "Rejected Players: {";
    std::transform(v1.begin(), v1.end(),
                   std::experimental::make_ostream_joiner(std::cout, ", "),
                   [] (const auto& x) {return *x.lock();});
    std::cout << "}\n";

    v1 = _players.at(0)->invite_players(_wplayers);
    std::cout << "Rejected Players: {";
    std::transform(v1.begin(), v1.end(),
                   std::experimental::make_ostream_joiner(std::cout, ", "),
                   [] (const auto& x) {return *x.lock();});
    std::cout << "}\n\n";
}

void Tester ::test_play_game() {
    auto game { _players.at(0)->get_hosted_game() };
    if (game) {
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(0) << '\n';
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(game->number_of_players() - 1) << '\n';
        std::cout << "Game: " << *game << '\n';
    }
    game = _players.at(1)->get_hosted_game();
    if (game) {
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(0) << '\n';
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(game->number_of_players() - 1) << '\n';
        std::cout << "Game: " << *game << '\n';
    }
    game = _players.at(2)->get_hosted_game();
    if (game) {
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(0) << '\n';
        std::cout << "Game: " << *game;
        std::cout << "Winner: " << *game->play(game->number_of_players() - 1) << '\n';
        std::cout << "Game: " << *game << '\n';
    }
}

void Tester :: test_leave_game() {
    auto game { _players.at(0)->get_hosted_game() };
    std::vector<int> v1 {1, 0, 0, 1, 0, 0};
    std::vector<int> v2;
    if (game) {
        v2.push_back(_players.at(0)->leave_game(game));
        v2.push_back(_players.at(0)->leave_game(game));
        v2.push_back(_players.at(1)->leave_game(game));
        v2.push_back(_players.at(3)->leave_game(game));
        v2.push_back(_players.at(7)->leave_game(game));
        v2.push_back(_players.at(8)->leave_game(game));
        if (v2.size() == v1.size() && std::equal(v1.begin(), v1.end(), v2.begin())) {
            std::cout << "Test Leave [" << game->get_name() << "] Check.\n";
        }
    }
}

void Tester :: test_close_game() {
    for (auto player: _players)
        std::cout << "Close: " << player->close_game() << '\n';
    std::cout << '{';
    std::transform(_players.begin(), _players.end(),
                   std::experimental::make_ostream_joiner(std::cout, ", "),
                   [](const auto& x){ return *x; });
    std::cout << "}\n";
}

void Tester :: test_host_again() {
    for(size_t i { 0 }; i < gameNames.size() && i < _players.size(); ++i)
        std::cout << "Host: " << (_players.at(i)->host_game(gameNames.at(i), Mode::Ranked)) << '\n';
    std::cout << "Send invitations\n";

    for(auto x : _players) {
        if(x->get_hosted_game())
            x->invite_players(_wplayers);
    }

    for(auto x : _players) {
        if(x->get_hosted_game()) {
            try {
                std::cout << "Best: " << *(x->get_hosted_game()->best_player()) << '\n';
            } catch (std::runtime_error& e) {
                std::cout << "Error BestX\n";
            }
        }
    }
    std::cout << '{';
    std::transform(_players.begin(), _players.end(),
                   std::experimental::make_ostream_joiner(std::cout, ", "),
                   [](const auto& x){ return *x; });
    std::cout << "}\n";
}

void Tester :: test() {
    test_host_game();
    test_best_player();
    test_join_game();
    test_invite_players();
    test_play_game();
    test_leave_game();
    test_close_game();
    test_host_again();
}