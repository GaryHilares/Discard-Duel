#include "../include/bot.hpp"
#include "../include/card.hpp"
#include "../include/game.hpp"
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

    int hand_size = 0;
    Card hand[6] = { { "", 0 } };
    int foe_hand_size = 0;
    Card foe_hand[6] = { { "", 0 } };
    const std::string pales[4] = { "spades", "clubs", "diamonds", "hearts" };

    // Game loop
    while (gameover != true) {
        // Draw cards
        if ((hand_size < 5) || (hand_size == 5 && turnend == false && turn != 0)) {
            for (int i = 0; i <= 5; i++) {
                if (hand[i].number == 0 && (i <= 4 || (i == 5 && turnend == false && turn != 0))) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    hand[i] = getRandomCard();
                    std::cout << "Drew " << hand[i].number << " of " << hand[i].pale << "." << std::endl;
                    hand_size++;
                }
            }
        }
        if ((foe_hand_size < 5) || (foe_hand_size == 5 && turnend == false && turn != 0)) {
            for (int i = 0; i <= 5; i++) {
                if (foe_hand[i].number == 0 && (i <= 4 || (i == 5 && turnend == false && turn != 0))) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    foe_hand[i] = getRandomCard();
                    std::cout << "Your opponent drew a card." << std::endl;
                    foe_hand_size++;
                }
            }
        }

        // Print hand
        std::cout << "Hand:" << std::endl;
        for (int i = 0; i <= 5; i++) {
            if (i != 5 || turn != 0) {
                std::cout << hand[i].number << " of " << hand[i].pale << std::endl;
            }
        }

        // Prompt for which card to discard
        while (hand_size == 6 && turnend == false) {
            int decision = -1;
            std::cout << "Discard 1 card." << std::endl;
            while (!(std::cin >> decision) || (decision < 1 || decision > 6)) {
                std::cout << "Please enter a valid number (numbers between 1 and 6)." << std::endl;
            }

            // Store discarded card to foe's memory
            for (int i = 0; i < 3; i++) {
                if (foemind[i] == 0) {
                    foemind[i] = hand[decision - 1].number;
                    break;
                }
            }

            // Print discarded card
            std::cout << "Discarded " << hand[decision - 1].number << " of " << hand[decision - 1].pale << "." << std::endl;

            // Delete card
            hand[decision - 1].number = 0;
            hand_size--;
        }

        // Choose what card should foe discard
        if (foe_hand_size == 6 && turnend == false) {
            int foedecision = AI::chooseCardToDiscard(foe_hand);
            std::cout << "Your opponent discarded a " << foe_hand[foedecision - 1].number << " of " << foe_hand[foedecision - 1].pale << "." << std::endl;
            foe_hand[foedecision - 1] = { "", 0 };
            foe_hand_size--;
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
        }

        // Trigger "discard round"
        if (!gameover && turn % 3 == 0 && turn > 0) {
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
            for (int i = 0; i <= 5; i++) {
                if (foediscardnumber == hand[i].number) {
                    std::cout << "Discarded " << hand[i].number << " of " << hand[i].pale << "." << std::endl;
                    hand[i] = { "", 0 };
                    hand_size--;
                }
            }
            if (hand_size == 5) {
                std::cout << "You don't have any " << foediscardnumber << " in your hand." << std::endl;
            }

            for (int i = 0; i <= 5; i++) {
                if (discardnumber == foe_hand[i].number) {
                    std::cout << "Your opponent discarded a " << foe_hand[i].number << " of " << foe_hand[i].pale << "." << std::endl;
                    foe_hand[i] = { "", 0 };
                    foe_hand_size--;
                }
            }
            if (foe_hand_size == 5) {
                std::cout << "Your opponent doesn't have any " << discardnumber << " in his hand." << std::endl;
            }
        }
        turnend = true;

        // Display messages
        if (turn == 0 && hand_size == 5) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Start!" << std::endl;
        }
        if (turnend == true && gameover == false) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            turn++;
            std::cout << std::endl
                      << std::endl;
            std::cout << "Turn " << turn << "." << std::endl;
            turnend = false;
        }
    }
    return 0;
}
