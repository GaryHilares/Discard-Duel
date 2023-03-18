#ifndef BOT_HPP
#define BOT_HPP
#include "./card.hpp"

namespace AI {
int chooseCardToDiscard(const Card foe_hand[6]);
int chooseNumberToDeclare(int foe_memory[3]);
};

#endif // BOT_HPP