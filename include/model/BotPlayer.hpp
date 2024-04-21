#ifndef BOT_HPP
#define BOT_HPP
#include "./Hand.hpp"
#include "./Player.hpp"

class BotPlayer : public Player {
private:
    static constexpr int MEMORY_SIZE = 3;
    std::array<int, BotPlayer::MEMORY_SIZE> m_memory;

public:
    BotPlayer();
    void rememberOpponentChoice(int discarded_number);
    int chooseCardToDiscard(const std::array<Card, MAX_HAND_SIZE> foe_hand);
    int chooseNumberToDeclare();
};

#endif // BOT_HPP