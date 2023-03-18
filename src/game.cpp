#include "../include/game.hpp"

std::pair<bool, int> checkWinningConditions(const Hand player_hand, const Hand foe_hand)
{
    bool player_win = player_hand.isStraight();
    bool foe_win = foe_hand.isStraight();
    if (player_win && foe_win) {
        return { true, 0 };
    } else if (player_win) {
        return { true, 1 };
    } else if (foe_win) {
        return { true, -1 };
    }
    return { false, 0 };
}