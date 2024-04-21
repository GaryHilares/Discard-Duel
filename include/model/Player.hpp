#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Hand.hpp"

class Player {
protected:
    std::string name;
    Hand m_hand;

public:
    Player(std::string name);
    Hand& getHandRef();
    const Hand& getConstHandRef() const;
};

#endif // PLAYER_HPP