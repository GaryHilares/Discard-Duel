#ifndef BOT_HPP
#define BOT_HPP
#include "./Card.hpp"

class Bot {
    int m_memory[3] = { 0, 0, 0 };

public:
    void rememberOpponentChoice(int discarded_number);
    static int chooseCardToDiscard(const Card foe_hand[6]);
    int chooseNumberToDeclare();
};

#endif // BOT_HPP