#ifndef GAME_HPP
#define GAME_HPP
#include "../model/Player.hpp"
#include "../model/BotPlayer.hpp"
#include "../model/Hand.hpp"
#include <utility>

class Game {
private:
    int m_turn_number;
    Player m_player;
    BotPlayer m_opponent;
    std::pair<bool, int> checkWinningConditions() const;

public:
    Game();
    void nextTurn();
    void executeTurn();
    bool isDiscardRound();
    bool isGameOver();
    void checkDiscardRound();
    int inputNumberInRange(int lower, int upper);
};

#endif // GAME_HPP