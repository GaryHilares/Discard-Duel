#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Hand.hpp"

class Player {
protected:
    std::string name;
    Hand m_hand;

public:
    /**
     * EFFECTS: Creates a new player with the given name.
     */
    Player(std::string name = "Player");

    /**
     * MODIFIES: this
     * EFFECTS: Returns a reference to this player's hand.
     */
    Hand& getHandRef();

    /**
     * EFFECTS: Returns a constant reference to this player's hand.
     */
    const Hand& getConstHandRef() const;
};

#endif // PLAYER_HPP