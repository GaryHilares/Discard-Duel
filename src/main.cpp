#include "../include/bot.hpp"
#include "../include/card.hpp"
#include "../include/game.hpp"
#include "../include/hand.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>

int main()
{
    // Set the rand seed
    srand(time(NULL));
    bool gameover = false, turnend = false;
    int foemind[3] = { 0 };
    int turn = 0;

    Hand hand, foe_hand;
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };

    while (hand.getSize() < MAX_HAND_SIZE - 1) {
        hand.draw();
    }
    while (foe_hand.getSize() < MAX_HAND_SIZE - 1) {
        foe_hand.draw(true);
    }

    // Game loop
    while (gameover != true) {
        if (turn == 0) {
            std::cout << "Start!" << std::endl;
        }
        if (!gameover) {
            turn++;
            std::cout << std::endl
                      << std::endl;
            std::cout << "Turn " << turn << "." << std::endl;
            turnend = false;
        }

        // Draw cards
        while (hand.getSize() < MAX_HAND_SIZE) {
            hand.draw();
        }
        while (foe_hand.getSize() < MAX_HAND_SIZE) {
            foe_hand.draw(true);
        }

        // Print hand
        hand.print();

        // Prompt for which card to discard
        while (hand.getSize() >= MAX_HAND_SIZE) {
            int decision = -1;
            std::cout << "Discard 1 card." << std::endl;
            while (!(std::cin >> decision) || (decision < 1 || decision > MAX_HAND_SIZE)) {
                std::cout << "Please enter a valid number (numbers between 1 and 6)." << std::endl;
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
        }

        // Choose what card should foe discard
        while (foe_hand.getSize() >= MAX_HAND_SIZE) {
            int foedecision = AI::chooseCardToDiscard(foe_hand.getArray());
            foe_hand.discard(foedecision - 1, true);
        }

        // Check for winning conditions
        std::pair<bool, int> game_outcome = checkWinningConditions(hand, foe_hand);
        if (game_outcome.first) {
            gameover = true;
            switch (game_outcome.second) {
            case -1:
                std::cout << "You lost!";
                break;
            case 0:
                std::cout << "It's a tie!";
                break;
            case 1:
                std::cout << "You won!";
                break;
            }
        } else if (turn % 3 == 0 && turn > 0) {
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
    return 0;
}
