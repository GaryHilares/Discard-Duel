#include "../../include/model/Card.hpp"

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

std::ostream& operator<<(std::ostream& out, const Card& card)
{
    if (card.getNumber() == 0 || card.getPale() == "") {
        return out << "None";
    }
    return out << card.getNumber() << " of " << card.getPale();
}

Card getRandomCard()
{
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };
    return { pales[rand() % 4], rand() % 13 + 1 };
}