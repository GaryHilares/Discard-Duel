#include "../../include/model/BotPlayer.hpp"
#include <cmath>

BotPlayer::BotPlayer()
    : Player("Computer")
    , m_memory({})
{
}

void BotPlayer::rememberOpponentChoice(int discarded_number)
{
    for (int i = 0; i < 3; i++) {
        if (m_memory[i] == 0) {
            m_memory[i] = discarded_number;
            break;
        }
    }
}

int BotPlayer::chooseCardToDiscard() const
{
    const std::array<Card, MAX_HAND_SIZE> hand = m_hand.getArray();
    // Check for repeated cards and discards them first
    for (int i = 1; i <= hand.size(); i++) {
        for (int j = i + 1; j <= hand.size(); j++) {
            if (hand[i - 1].getNumber() == hand[j - 1].getNumber()) {
                return j;
            }
        }
    }

    // Find average value
    int average = 0;
    for (int i = 0; i < 6; i++) {
        average += hand[i].getNumber();
    }
    average = round((float)average / 6);

    // Search card which has a number furthest from the average
    int maximum_difference = -1;
    int index = -1;
    for (int i = 0; i < 6; i++) {
        int difference = abs(hand[i].getNumber() - average);
        if (difference >= maximum_difference) {
            maximum_difference = difference;
            index = i;
        }
    }

    return index + 1;
}

int BotPlayer::chooseNumberToDeclare()
{
    int average = 0;
    for (int i = 0; i <= 2; i++) {
        average += m_memory[i];
        m_memory[i] = 0;
    }
    return 13 - average / 3;
}