#ifndef HAND_HPP
#define HAND_HPP
#include "./Card.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

constexpr int MAX_HAND_SIZE = 6;

class Hand {
private:
    Card hand[MAX_HAND_SIZE] = { { "", 0 } };

public:
    void draw(bool is_opponent = false);
    int getSize() const;
    void print() const;
    void discard(int index, bool is_oponent = false);
    bool isStraight() const;
    void discardAllByNumber(int number, bool is_oponent = false);
    Card* getArray();
};

#endif // HAND_HPP