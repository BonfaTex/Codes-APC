#include <iostream>
#include <string>
#include <vector>

#include "RandomPlayerGenerator.hh"
#include "search.hh"
#include "Player.hh"
#include "timing.hh"


using std::string;

typedef std::vector<Arcade::Player> player_vec_type;
typedef std::set<Arcade::Player> player_set_type;
typedef std::unordered_map<unsigned, Arcade::Player> player_map_type;

int main() {
    constexpr unsigned n_player = 10000000;
    player_vec_type player_vec;
    player_set_type player_set;
    player_map_type player_map;

    Arcade::RandomPlayerGenerator rs;

    // create the vector with players sorted by username
    timing::time_point start = std::chrono::steady_clock::now();
    std::cout << "\n********* populating vector *********\n";
    for (unsigned i = 0; i < n_player; ++i) {
        Arcade::Player random_player = rs.nextPlayer();
        player_vec.push_back(random_player);
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);

    start = std::chrono::steady_clock::now();
    std::cout << "\n********* populating set *********\n";
    for (unsigned i = 0; i < n_player; ++i) {
        Arcade::Player random_player = player_vec[i];
        player_set.insert(random_player);
    }
    finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);

    start = std::chrono::steady_clock::now();
    std::cout << "\n********* populating map *********\n";
    for (unsigned i = 0; i < n_player; ++i) {
        Arcade::Player random_player = player_vec[i];
        player_map.insert(std::pair<unsigned, Arcade::Player>(random_player.getUsername(), random_player));
    }
    finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);

    const unsigned player_ok_username = player_vec[player_vec.size() / 2].getUsername();
    const unsigned player_ko_username = player_vec.back().getUsername() + 1;

    std::cout << "\n********* initial binary search on vector *********\n";
    std::cout << (Arcade::binary_search(player_vec, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::binary_search(player_vec, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* stl binary search on vector *********\n";
    std::cout << (Arcade::stl_binary_search(player_vec, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::stl_binary_search(player_vec, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search1 on set *********\n";
    std::cout << (Arcade::set_search1(player_set, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::set_search1(player_set, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search2 on set *********\n";
    std::cout << (Arcade::set_search2(player_set, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::set_search2(player_set, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search3 on set *********\n";
    std::cout << (Arcade::set_search3(player_set, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::set_search3(player_set, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search1 on map *********\n";
    std::cout << (Arcade::map_search1(player_map, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::map_search1(player_map, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search2 on map *********\n";
    std::cout << (Arcade::map_search2(player_map, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::map_search2(player_map, player_ko_username) ? "Found!\n" : "Not found :(\n");
    std::cout << "\n********* search3 on map *********\n";
    std::cout << (Arcade::map_search3(player_map, player_ok_username) ? "Found!\n" : "Not found :(\n");
    std::cout << (Arcade::map_search3(player_map, player_ko_username) ? "Found!\n" : "Not found :(\n");

    return 0;
}
