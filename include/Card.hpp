#ifndef CARD_HPP
#define CARD_HPP
#include <string>

class Card {
public:
    std::string pale;
    int number;
    bool operator!=(const Card& other);
    bool operator<(const Card& other);
};

Card getRandomCard();

#endif // CARD_HPP