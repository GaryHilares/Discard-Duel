#ifndef GAME_HPP
#define GAME_HPP
#include "./hand.hpp"
#include <utility>

std::pair<bool, int> checkWinningConditions(const Hand player_hand, const Hand foe_hand);

#endif // GAME_HPP