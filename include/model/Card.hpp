#ifndef CARD_HPP
#define CARD_HPP
#include <ostream>
#include <string>

class Card {
private:
    std::string pale;
    int number;

public:
    Card();
    Card(std::string pale, int number);
    bool operator!=(const Card& other);
    bool operator<(const Card& other);
    int getNumber() const;
    std::string getPale() const;
};

std::ostream& operator<<(std::ostream& out, const Card& card);

Card getRandomCard();

#endif // CARD_HPP