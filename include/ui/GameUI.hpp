#ifndef GAME_UI_HPP
#define GAME_UI_HPP
#include "../model/Game.hpp"
#include <utility>

class GameUI {
private:
    Game m_game;

    /**
     * EFFECTS: Asks the user for an integer between lower and upper through the standard stream,
     *          and returns it.
     */
    int inputNumberInRange(int lower, int upper);

public:
    /**
     * EFFECTS: Creates a new GameUI, makes both player draw cards until their hand is full,
     *          and begins the game.
     */
    GameUI();

    /**
     * MODIFIES: this
     * EFFECTS: Starts the next turn, printing a message and drawing cards for both players.
     */
    void nextTurn();

    /**
     * MODIFIES: this
     * EFFECTS: Asks the user for input, and makes both players discard cards.
     */
    void executeTurn();

    /**
     * EFFECTS: Prints the winner and returns true if game has ended, just returns false otherwise.
     */
    bool isGameOver() const;

    /**
     * MODIFIES: this
     * EFFECTS: If there should be a discard round this turn, asks the user for input and performs it.
     */
    void checkDiscardRound();
};

#endif // GAME_UI_HPP