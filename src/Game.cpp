#include "../include/Game.hpp"

Game::Game()
    : m_turn_number(0)
{
    srand(time(NULL));
    while (hand.getSize() < MAX_HAND_SIZE - 1) {
        hand.draw();
    }
    while (foe_hand.getSize() < MAX_HAND_SIZE - 1) {
        foe_hand.draw(true);
    }
    std::cout << "Start!" << std::endl;
}

void Game::nextTurn()
{
    m_turn_number++;
    std::cout << std::endl
              << std::endl;
    std::cout << "Turn " << m_turn_number << "." << std::endl;
    while (hand.getSize() < MAX_HAND_SIZE) {
        hand.draw();
    }
    while (foe_hand.getSize() < MAX_HAND_SIZE) {
        foe_hand.draw(true);
    }
    hand.print();
}

void Game::executeTurn()
{
    std::cout << "Discard 1 card." << std::endl;
    int decision = -1;
    while (true) {
        if ((std::cin >> decision) && decision >= 1 && decision <= MAX_HAND_SIZE) {
            break;
        } else {
            std::cout << "Please enter a valid number (numbers between 1 and 6)." << std::endl;
        }
    }

    // Delete card
    Card discarded_card = hand.discard(decision - 1);

    // Store discarded card to foe's memory
    m_foe_mind.rememberOpponentChoice(discarded_card.getNumber());

    int foedecision = Bot::chooseCardToDiscard(foe_hand.getArray());
    foe_hand.discard(foedecision - 1, true);
}

bool Game::isGameOver()
{
    std::pair<bool, int> game_outcome = checkWinningConditions(hand, foe_hand);
    if (game_outcome.first) {
        switch (game_outcome.second) {
        case -1:
            std::cout << "You lost!" << std::endl;
            break;
        case 0:
            std::cout << "It's a tie!" << std::endl;
            break;
        case 1:
            std::cout << "You won!" << std::endl;
            break;
        }
        return true;
    }
    return false;
}
void Game::checkDiscardRound()
{
    if (m_turn_number % 3 == 0 && m_turn_number > 0) {
        int discardnumber;
        std::cout << "Time to discard!" << std::endl;
        while (true) {
            std::cin >> discardnumber;
            if (discardnumber >= 1 && discardnumber <= 13) {
                break;
            } else {
                std::cin.clear();
                std::cin.ignore(10000000, '\n');
                std::cout << "Please enter a valid number (numbers between 1 and 13)." << std::endl;
            }
        }

        int foediscardnumber = m_foe_mind.chooseNumberToDeclare();
        std::cout << "Your opponent has chosen the number " << foediscardnumber << "." << std::endl;

        hand.discardAllByNumber(foediscardnumber);
        if (hand.getSize() == 5) {
            std::cout << "You don't have any " << foediscardnumber << " in your hand." << std::endl;
        }

        foe_hand.discardAllByNumber(discardnumber, true);
        if (foe_hand.getSize() == 5) {
            std::cout << "Your opponent doesn't have any " << discardnumber << " in his hand." << std::endl;
        }
    }
}

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