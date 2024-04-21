#include "../include/Card.hpp"

bool Card::operator!=(const Card& other)
{
    return this->pale == other.pale && this->number == other.number;
}

bool Card::operator<(const Card& other)
{
    return this->number < other.number;
}

Card getRandomCard()
{
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };
    return { pales[rand() % 4], rand() % 13 + 1 };
}