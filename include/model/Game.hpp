#ifndef GAME_HPP
#define GAME_HPP
#include "../model/BotPlayer.hpp"
#include "../model/Player.hpp"

class Game {
private:
    int m_turn_number;
    Player m_player;
    BotPlayer m_opponent;

public:
    Game();
    Player& getPlayerRef();
    const Player& getConstPlayerRef() const;
    BotPlayer& getBotPlayerRef();
    const BotPlayer& getConstBotPlayerRef() const;
    int nextTurnNumber();
    bool isDiscardRound();
    std::pair<bool, int> checkWinningConditions() const;
};

#endif // GAME_HPP