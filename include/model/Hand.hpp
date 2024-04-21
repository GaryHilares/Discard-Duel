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
    /**
     * MODIFIES: this
     * EFFECTS: Draws a card, adds to the hand, and returns it.
     */
    Card draw();

public:
    /**
     * EFFECTS: Get the size of the current hand.
     */
    int getSize() const;

    /**
     * MODIFIES: this
     * EFFECTS: Discards the card at the given 1-indexed position.
     */
    Card discard(int index);

    /**
     * EFFECTS: Returns true if this hand forms a straight, false otherwise.
     */
    bool isStraight() const;

    /**
     * MODIFIES: this
     * EFFECTS: Discards all cards with the given number, and returns them.
     */
    std::vector<Card> discardAllByNumber(int number);

    /**
     * EFFECTS: Returns an array of the cards in this hand.
     */
    std::array<Card, MAX_HAND_SIZE> getArray() const;

    /**
     * MODIFIES: this
     * EFFECTS: Draws cards until hand is full, adds them to the hand, and returns them.
     */
    std::vector<Card> drawUntilFull();

    /**
     * MODIFIES: out
     * EFFECTS: Streams current hand to the given ostream.
     */
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};

#endif // HAND_HPP