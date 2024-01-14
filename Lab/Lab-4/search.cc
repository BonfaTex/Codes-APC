#include <iostream>
#include <algorithm>

#include "search.hh"
#include "timing.hh"

/* Template for extracting time from the search methods to be implemented:
 *
 * timing::time_point start = std::chrono::steady_clock::now();
 * --- Search ---
 * timing::time_point finish = std::chrono::steady_clock::now();
 * timing::elapsed_between (start, finish);
 *
 * This will print the elapsed time for each search implementation */

namespace Arcade {
bool binary_search(const std::vector<Arcade::Player> &player_vec, unsigned player_username) {
    timing::time_point start = std::chrono::steady_clock::now();

    auto begin = player_vec.begin(), end = player_vec.end(),
            musername = begin + (end - begin) / 2;
    unsigned n_iter = 1;

    while (begin != end and musername->getUsername() != player_username) {
        /* end is meant to be invalusername, so in both cases
         * we are ignoring musername at the following iteration
         */
        if (player_username < musername->getUsername())
            end = musername;
        else
            begin = musername + 1;

        musername = begin + (end - begin) / 2;
        ++n_iter;
    }

    std::cout << "Number of Iterations " << n_iter << "\n";

    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);

    if (musername != player_vec.end() and player_username == musername->getUsername()) {
        return true;
    } else {
        return false;
    }
}

bool stl_binary_search(const std::vector<Arcade::Player> &player_vec, unsigned player_username) {
    timing::time_point start = std::chrono::steady_clock::now();
    bool val = std::binary_search(player_vec.begin(), player_vec.end(), Player(player_username));
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return val;
}

// Version 1: use of find
// c.find(k) returns an iterator to the first element with key k,
//           or the off-the-end iterator if k is not in c
bool set_search1(const std::set<Arcade::Player>& player_set, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    if (player_set.find(Player(player_username)) != player_set.end()) {
        timing::time_point finish = std::chrono::steady_clock::now();
        timing::elapsed_between(start, finish);
        return true;
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

// Version 2: use of count
// c.count(k) returns the number of elements with key k, zero otherwise;
//            note that for set/map (not multi) the result is zero or one
bool set_search2(const std::set<Arcade::Player>& player_set, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    if (player_set.count(Player(player_username)) != 0) {
        timing::time_point finish = std::chrono::steady_clock::now();
        timing::elapsed_between(start, finish);
        return true;
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

// Version 3: scan element by element
bool set_search3(const std::set<Arcade::Player>& player_set, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    for (auto& it: player_set) {
        if (it.getUsername() == player_username) {
            timing::time_point finish = std::chrono::steady_clock::now();
            timing::elapsed_between(start, finish);
            return true;
        }
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

// Version 1: use of find
bool map_search1(const std::unordered_map<unsigned, Arcade::Player> &player_map, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    if (player_map.find(player_username) != player_map.end()) {
        timing::time_point finish = std::chrono::steady_clock::now();
        timing::elapsed_between(start, finish);
        return true;
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

// Version 2: use of count
bool map_search2(const std::unordered_map<unsigned, Arcade::Player> &player_map, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    if (player_map.count(player_username) != 0) {
        timing::time_point finish = std::chrono::steady_clock::now();
        timing::elapsed_between(start, finish);
        return true;
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

// Version 3: scan element by element
bool map_search3(const std::unordered_map<unsigned, Arcade::Player> &player_map, unsigned player_username)
{
    timing::time_point start = std::chrono::steady_clock::now();
    for (auto& it: player_map) {
        if (it.first == player_username) {
            timing::time_point finish = std::chrono::steady_clock::now();
            timing::elapsed_between(start, finish);
            return true;
        }
    }
    timing::time_point finish = std::chrono::steady_clock::now();
    timing::elapsed_between(start, finish);
    return false;
}

}