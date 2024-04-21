#include "../include/Card.hpp"

Card getRandomCard()
{
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };
    return { pales[rand() % 4], rand() % 13 + 1 };
}