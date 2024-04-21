#ifndef GAME_HPP
#define GAME_HPP
#include "../model/BotPlayer.hpp"
#include "../model/Player.hpp"

class Game {
private:
    int m_turn_number;
    Player m_player;
    BotPlayer m_opponent;

public:
    /**
     * EFFECTS: Creates a new game at turn number 0, with both players' hands empty.
     */
    Game();

    /**
     * EFFECTS: Returns a reference to the player.
     */
    Player& getPlayerRef();

    /**
     * MODIFIES: this
     * EFFECTS: Returns a constant reference to the player.
     */
    const Player& getConstPlayerRef() const;

    /**
     * EFFECTS: Returns a reference to the bot player.
     */
    BotPlayer& getBotPlayerRef();

    /**
     * EFFECTS: Returns a constant reference to the bot player.
     */
    const BotPlayer& getConstBotPlayerRef() const;

    /**
     * MODIFIES: this
     * EFFECTS: Increases the turn number by 1, and returns it.
     */
    int nextTurnNumber();

    /**
     * EFFECTS: Returns true if this turn should include a discard round, false otherwise.
     */
    bool isDiscardRound() const;

    /**
     * EFFECTS: Returns {false, 0} if no one has won yet, {true, 1} if the player won, {true, -1} if the
     *          bot player won, and {true, 0} if it was a draw.
     */
    std::pair<bool, int> checkWinningConditions() const;
};

#endif // GAME_HPP
