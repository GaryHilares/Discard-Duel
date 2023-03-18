#include "../include/game.hpp"

std::pair<bool, int> checkWinningConditions(const Card player_hand[6], const Card foe_hand[6])
{
    int points = 0;
    int foepoints = 0;
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (player_hand[i].number == (player_hand[j].number + 1)) {
                points++;
            } else if (player_hand[i].number == player_hand[j].number && j != i) {
                points = -1000;
            }
            if (foe_hand[i].number == (foe_hand[j].number + 1) && foe_hand[i].number != 0) {
                foepoints++;
            } else if (foe_hand[i].number == foe_hand[j].number && j != i) {
                foepoints = -1000;
            }
        }
    }
    if (points == 4 && foepoints == 4) {
        return { true, 0 };
    } else if (points == 4) {
        return { true, 1 };
    } else if (foepoints == 4) {
        return { true, -1 };
    }
    return { false, 0 };
}