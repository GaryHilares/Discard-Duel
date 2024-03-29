#include "../include/bot.hpp"
#include "../include/card.hpp"
#include "../include/game.hpp"
#include "../include/hand.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

class Game {
    int m_turn_number;
    Hand hand, foe_hand;
    int foemind[3] = { 0, 0, 0 };

public:
    Game()
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
    void nextTurn()
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
    void executeTurn()
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

        // Store discarded card to foe's memory
        for (int i = 0; i < 3; i++) {
            if (foemind[i] == 0) {
                foemind[i] = 6; // TODO: Update AI. hand[decision - 1].number;
                break;
            }
        }

        // Delete card
        hand.discard(decision - 1);

        int foedecision = AI::chooseCardToDiscard(foe_hand.getArray());
        foe_hand.discard(foedecision - 1, true);
    }
    bool isGameOver()
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
    void checkDiscardRound()
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

            int foediscardnumber = AI::chooseNumberToDeclare(foemind);
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
};

int main()
{
    Game game;
    while (true) {
        game.nextTurn();
        game.executeTurn();
        if (game.isGameOver()) {
            break;
        }
        game.checkDiscardRound();
    }
    return 0;
}
