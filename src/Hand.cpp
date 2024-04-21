#include "../include/Hand.hpp"

void Hand::draw(bool is_opponent)
{
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].number == 0) {
            hand[i] = getRandomCard();
            if (!is_opponent) {
                std::cout << "Drew " << hand[i].number << " of " << hand[i].pale << "." << std::endl;
            } else {
                std::cout << "Your opponent drew a card." << std::endl;
            }
        }
    }
}

int Hand::getSize() const
{
    int number_of_cards = 0;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].number != 0) {
            number_of_cards++;
        }
    }
    return number_of_cards;
}

void Hand::print() const
{
    std::cout << "Hand:" << std::endl;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].number != 0) {
            std::cout << hand[i].number << " of " << hand[i].pale << std::endl;
        }
    }
}

Card Hand::discard(int index, bool is_oponent)
{
    if (!is_oponent) {
        std::cout << "Discarded " << hand[index].number << " of " << hand[index].pale << "." << std::endl;
    } else {
        std::cout << "Your opponent discarded a " << hand[index].number << " of " << hand[index].pale << "." << std::endl;
    }
    Card tmp = hand[index];
    hand[index] = { "", 0 };
    return tmp;
}

bool Hand::isStraight() const
{
    Card temporal_hand[MAX_HAND_SIZE] = { { "", 0 } };
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        temporal_hand[i] = hand[i];
    }
    std::sort(std::begin(temporal_hand), std::end(temporal_hand));
    for (int i = 2; i < MAX_HAND_SIZE; i++) {
        if (temporal_hand[i].number != temporal_hand[i - 1].number + 1) {
            return false;
        }
    }
    return true;
}

void Hand::discardAllByNumber(int number, bool is_oponent)
{
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].number == number) {
            discard(i, is_oponent);
        }
    }
}

Card* Hand::getArray()
{
    return hand;
}