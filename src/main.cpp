#include "../include/Game.hpp"

int main()
{
    Game game;
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
