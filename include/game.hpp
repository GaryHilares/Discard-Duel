#ifndef GAME_HPP
#define GAME_HPP
#include "card.hpp"
#include <utility>

std::pair<bool, int> checkWinningConditions(const Card player_hand[6], const Card foe_hand[6]);

#endif // GAME_HPP