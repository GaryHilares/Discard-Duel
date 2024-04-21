#include "../../include/model/Hand.hpp"

Card Hand::draw()
{
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].getNumber() == 0) {
            hand[i] = getRandomCard();
            return hand[i];
        }
    }
    return Card();
}

int Hand::getSize() const
{
    int number_of_cards = 0;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].getNumber() != 0) {
            number_of_cards++;
        }
    }
    return number_of_cards;
}

std::ostream& operator<<(std::ostream& out, const Hand& hand)
{
    out << "Hand:" << std::endl;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand.hand[i].getNumber() != 0) {
            out << hand.hand[i].getNumber() << " of " << hand.hand[i].getPale() << "\n";
        }
    }
    return out;
}

Card Hand::discard(int index, bool is_oponent)
{
    Card tmp = hand[index];
    hand[index] = { "", 0 };
    return tmp;
}

bool Hand::isStraight() const
{
    std::array<Card, MAX_HAND_SIZE> temporal_hand;
    std::copy(hand.begin(), hand.end(), temporal_hand.begin());
    std::sort(temporal_hand.begin(), temporal_hand.end());
    for (int i = 2; i < MAX_HAND_SIZE; i++) {
        if (temporal_hand[i].getNumber() != temporal_hand[i - 1].getNumber() + 1) {
            return false;
        }
    }
    return true;
}

std::vector<Card> Hand::discardAllByNumber(int number, bool is_oponent)
{
    std::vector<Card> ret;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].getNumber() == number) {
            ret.push_back(discard(i, is_oponent));
        }
    }
    return ret;
}

std::array<Card, MAX_HAND_SIZE> Hand::getArray()
{
    return hand;
}