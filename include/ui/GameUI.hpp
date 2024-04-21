#ifndef GAME_UI_HPP
#define GAME_UI_HPP
#include "../model/Game.hpp"
#include <utility>

class GameUI {
private:
    Game m_game;
    int inputNumberInRange(int lower, int upper);

public:
    GameUI();
    void nextTurn();
    void executeTurn();
    bool isGameOver();
    void checkDiscardRound();
};

#endif // GAME_UI_HPP