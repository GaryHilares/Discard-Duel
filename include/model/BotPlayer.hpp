#ifndef BOT_PLAYER_HPP
#define BOT_PLAYER_HPP
#include "./Hand.hpp"
#include "./Player.hpp"

class BotPlayer : public Player {
private:
    static constexpr int MEMORY_SIZE = 3;
    std::array<int, BotPlayer::MEMORY_SIZE> m_memory;

public:
    /**
     * EFFECTS: Creates a new BotPlayer with empty memory and hand.
     */
    BotPlayer();

    /**
     * REQUIRES: 1 <= discarded_number <= 13
     * MODIFIES: this
     * EFFECTS: Records the opponent choice, which will be taken into account for future choices.
     */
    void rememberOpponentChoice(int discarded_number);

    /**
     * EFFECTS: Produces the bot's choice of card to discard.
     */
    int chooseCardToDiscard() const;

    /**
     * MODIFIES: this
     * EFFECTS: Produces the bot's choice of number to declare during the discard round.
     */
    int chooseNumberToDeclare();
};

#endif // BOT_PLAYER_HPP
