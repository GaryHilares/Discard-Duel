#ifndef GAME_HPP
#define GAME_HPP
#include "../include/Bot.hpp"
#include "../include/Hand.hpp"
#include "./Hand.hpp"
#include <utility>

std::pair<bool, int> checkWinningConditions(const Hand player_hand, const Hand foe_hand);

class Game {
    int m_turn_number;
    Hand hand, foe_hand;
    int foemind[3] = { 0, 0, 0 };

public:
    Game();
    void nextTurn();
    void executeTurn();
    bool isGameOver();
    void checkDiscardRound();
};

#endif // GAME_HPP