#include "../../include/model/Player.hpp"

Player::Player(std::string name)
{
    this->name = name;
}

Hand& Player::getHandRef()
{
    return m_hand;
}

const Hand& Player::getConstHandRef() const
{
    return m_hand;
}