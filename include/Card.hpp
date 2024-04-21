#ifndef CARD_HPP
#define CARD_HPP
#include <string>

class Card {
public:
    std::string pale;
    int number;
    bool operator!=(const Card& other)
    {
        return this->pale == other.pale && this->number == other.number;
    }
    bool operator<(const Card& other)
    {
        return this->number < other.number;
    }
};

Card getRandomCard();

#endif // CARD_HPP