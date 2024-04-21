#include "../../include/model/Game.hpp"

Game::Game()
    : m_turn_number(0)
{
}

Player& Game::getPlayerRef()
{
    return m_player;
}

const Player& Game::getConstPlayerRef() const
{
    return m_player;
}

BotPlayer& Game::getBotPlayerRef()
{
    return m_opponent;
}

const BotPlayer& Game::getConstBotPlayerRef() const
{
    return m_opponent;
}

int Game::nextTurnNumber()
{
    return ++m_turn_number;
}

bool Game::isDiscardRound() const
{
    return m_turn_number % 3 == 0 && m_turn_number > 0;
}

std::pair<bool, int> Game::checkWinningConditions() const
{
    bool player_win = m_player.getConstHandRef().isStraight();
    bool foe_win = m_opponent.getConstHandRef().isStraight();
    if (player_win && foe_win) {
        return { true, 0 };
    } else if (player_win) {
        return { true, 1 };
    } else if (foe_win) {
        return { true, -1 };
    }
    return { false, 0 };
}