#ifndef CARD_HPP
#define CARD_HPP
#include <string>

class Card {
public:
    std::string pale;
    int number;
};

Card getRandomCard();

#endif // CARD_HPP