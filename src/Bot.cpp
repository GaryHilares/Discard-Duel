#include "../include/Bot.hpp"
#include <cmath>

void Bot::rememberOpponentChoice(int discarded_number)
{
    for (int i = 0; i < 3; i++) {
        if (m_memory[i] == 0) {
            m_memory[i] = discarded_number;
            break;
        }
    }
}

int Bot::chooseCardToDiscard(const Card foe_hand[6])
{
    // Check for repeated cards and discards them first
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if (foe_hand[i - 1].getNumber() == foe_hand[j - 1].getNumber() && i != j) {
                return j;
            }
        }
    }

    // Find average value
    int average = 0;
    for (int i = 0; i < 6; i++) {
        average += foe_hand[i].getNumber();
    }
    average = round((float)average / 6);

    // Search card which has a number furthest from the average
    int maximum_difference = -1;
    int index = -1;
    for (int i = 0; i < 6; i++) {
        int difference = abs(foe_hand[i].getNumber() - average);
        if (difference >= maximum_difference) {
            maximum_difference = difference;
            index = i;
        }
    }

    return index + 1;
}

int Bot::chooseNumberToDeclare()
{
    int average = 0;
    for (int i = 0; i <= 2; i++) {
        average += m_memory[i];
        m_memory[i] = 0;
    }
    return 13 - average / 3;
}