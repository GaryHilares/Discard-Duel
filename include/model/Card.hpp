#ifndef CARD_HPP
#define CARD_HPP
#include <ostream>
#include <string>

class Card {
private:
    std::string pale;
    int number;

public:
    /**
     * EFFECTS: Creates a card with a placeholder value.
     */
    Card();

    /**
     * EFFECTS: Creates a card with the given pale and given integer.
     */
    Card(std::string pale, int number);

    /**
     * EFFECTS: Returns true if both elements have different number or pale, false otherwise.
     */
    bool operator!=(const Card& other);

    /**
     * EFFECTS: Returns true if the number of the first element is lower than that of the second element.
     */
    bool operator<(const Card& other);

    /**
     * EFFECTS: Returns the number of this card.
     */
    int getNumber() const;

    /**
     * EFFECTS: Returns the pale of this card.
     */
    std::string getPale() const;
};

/**
 * MODIFIES: out
 * EFFECTS: Prints the card to the given outstream, or "None" if it is a placeholder card.
 */
std::ostream& operator<<(std::ostream& out, const Card& card);

Card getRandomCard();

#endif // CARD_HPP
