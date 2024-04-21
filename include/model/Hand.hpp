#ifndef HAND_HPP
#define HAND_HPP
#include "./Card.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <ostream>
#include <vector>

constexpr int MAX_HAND_SIZE = 6;

class Hand {
private:
    std::array<Card, MAX_HAND_SIZE> hand;

public:
    Card draw();
    int getSize() const;
    Card discard(int index, bool is_oponent = false);
    bool isStraight() const;
    std::vector<Card> discardAllByNumber(int number, bool is_oponent = false);
    std::array<Card, MAX_HAND_SIZE> getArray();
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};

#endif // HAND_HPP