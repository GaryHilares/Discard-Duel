#ifndef HAND_HPP
#define HAND_HPP
#include "./Card.hpp"
#include <algorithm>
#include <cassert>
#include <ostream>
#include <vector>

constexpr int MAX_HAND_SIZE = 6;

class Hand {
private:
    Card hand[MAX_HAND_SIZE];

public:
    Card draw();
    int getSize() const;
    Card discard(int index, bool is_oponent = false);
    bool isStraight() const;
    std::vector<Card> discardAllByNumber(int number, bool is_oponent = false);
    Card* getArray();
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};

#endif // HAND_HPP