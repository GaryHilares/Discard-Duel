#ifndef GAME_HPP
#define GAME_HPP
#include "../model/Bot.hpp"
#include "../model/Hand.hpp"
#include <utility>

std::pair<bool, int> checkWinningConditions(const Hand player_hand, const Hand foe_hand);

class Game {
    int m_turn_number;
    Hand hand, foe_hand;
    Bot m_foe_mind;

public:
    Game();
    void nextTurn();
    void executeTurn();
    bool isGameOver();
    void checkDiscardRound();
};

#endif // GAME_HPP