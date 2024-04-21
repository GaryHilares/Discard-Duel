#include "../../include/ui/GameUI.hpp"

int main()
{
    GameUI game;
    while (true) {
        game.nextTurn();
        game.executeTurn();
        if (game.isGameOver()) {
            break;
        }
        game.checkDiscardRound();
    }
    return 0;
}
