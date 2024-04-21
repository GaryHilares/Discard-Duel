#include "../include/Card.hpp"

Card::Card()
{
    this->pale = "";
    this->number = 0;
}

Card::Card(std::string pale, int number)
{
    this->pale = pale;
    this->number = number;
}

bool Card::operator!=(const Card& other)
{
    return this->pale == other.pale && this->number == other.getNumber();
}

bool Card::operator<(const Card& other)
{
    return this->number < other.getNumber();
}

int Card::getNumber() const
{
    return number;
}

std::string Card::getPale() const
{
    return pale;
}

Card getRandomCard()
{
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };
    return { pales[rand() % 4], rand() % 13 + 1 };
}