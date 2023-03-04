#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <thread>

class Card {
public:
    std::string pale;
    int number;
};

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

int chooseCardToDiscard(const Card foe_hand[6])
{
    // Check for repeated cards and discards them first
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if (foe_hand[i - 1].number == foe_hand[j - 1].number && i != j) {
                return j;
            }
        }
    }

    // Find average value
    int average = 0;
    for (int i = 0; i < 6; i++) {
        average += foe_hand[i].number;
    }
    average = round((float)average / 6);

    // Search card which has a number furthest from the average
    int maximum_difference = -1;
    int index = -1;
    for (int i = 0; i < 6; i++) {
        int difference = abs(foe_hand[i].number - average);
        if (difference >= maximum_difference) {
            maximum_difference = difference;
            index = i;
        }
    }

    return index + 1;
}

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
                    hand[i].number = rand() % 13 + 1;
                    hand[i].pale = pales[rand() % 4];
                    std::cout << "Drew " << hand[i].number << " of " << hand[i].pale << "." << std::endl;
                    hand_size++;
                }
            }
        }
        if ((foe_hand_size < 5) || (foe_hand_size == 5 && turnend == false && turn != 0)) {
            for (int i = 0; i <= 5; i++) {
                if (foe_hand[i].number == 0 && (i <= 4 || (i == 5 && turnend == false && turn != 0))) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    foe_hand[i].number = rand() % 13 + 1;
                    foe_hand[i].pale = pales[rand() % 4];
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
            int foedecision = chooseCardToDiscard(foe_hand);
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
            int foediscardnumber;
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
            int average = 0;
            for (int i = 0; i <= 2; i++) {
                average += foemind[i];
                foemind[i] = 0;
            }
            foediscardnumber = 13 - average / 3;
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
