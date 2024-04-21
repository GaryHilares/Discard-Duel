#include "../../include/ui/GameUI.hpp"

int main()
{
    srand(time(NULL));
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
