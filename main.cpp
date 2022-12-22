#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

int main()
{
    srand(time(NULL));
    bool gameover = false, turnend = false;
    int foemind[3] = {0};
    int foedecision = -1;
    int foediscardnumber;
    int foehand = 0;
    int foenumbers[6] = {0};
    int foepalenumbers[6] = {0};
    int foepoints = 0;
    int decision = -1;
    int discardnumber;
    int hand = 0;
    int numbers[6] = {0};
    int palenumbers[6] = {0};
    int points = 0;
    int power = -1;
    int turn = 0;
    string pales [6] = {""};
    string foepales[6] = {""};

    while (gameover != true)
    {
        if ((hand < 5) || (hand == 5 && turnend == false && turn != 0))
        {
            for (int i = 0; i <= 5; i++)
            {
                if (numbers[i] == 0 && (i <= 4 || (i == 5 && turnend == false && turn != 0)))
                {
                    Sleep(50);
                    numbers[i] = rand()%13 + 1;
                    palenumbers[i] = rand()%4 + 1;
                    if (palenumbers[i] == 1) {pales[i] = "spades";}
                    else if (palenumbers[i] == 2) {pales[i] = "clubs";}
                    else if (palenumbers[i] == 3) {pales[i] = "diamonds";}
                    else if (palenumbers[i] == 4) {pales[i] = "hearts";}
                    cout << "Drew " << numbers[i] << " of " << pales[i] << "." << endl;
                    hand++;
                }
            }
        }
        if ((foehand < 5) || (foehand == 5 && turnend == false && turn != 0))
        {
            for (int i = 0; i <= 5; i++)
            {
                if (foenumbers[i] == 0 && (i <= 4 || (i == 5 && turnend == false && turn != 0)))
                {
                    Sleep(50);
                    foenumbers[i] = rand()%13 + 1;
                    foepalenumbers[i] = rand()%4 + 1;
                    if (foepalenumbers[i] == 1) {foepales[i] = "spades";}
                    else if (foepalenumbers[i] == 2) {foepales[i] = "clubs";}
                    else if (foepalenumbers[i] == 3) {foepales[i] = "diamonds";}
                    else if (foepalenumbers[i] == 4) {foepales[i] = "hearts";}
                    cout << "Your opponent drew a card." << endl;
                    foehand++;
                }
            }
        }
        cout << "Hand:" << endl;
        for (int i = 0; i <= 5; i++) {if (i != 5 || turn != 0) {cout << numbers[i] << " of " << pales[i] << endl;}}
        while (hand == 6 && turnend == false)
        {
            cout << "Discard 1 card." << endl;
            cin >> decision;
            if (decision >= 1 && decision <= 6)
            {
                for (int i = 0; i <= 2; i++) {if (foemind[i] == 0) {foemind[i] = numbers [decision - 1]; break;}}
                cout << "Discarded " << numbers[decision - 1] << " of " << pales[decision - 1] <<"." << endl; numbers[decision - 1] = 0; hand--; decision = -1;
            }
            else {cin.clear(); cin.ignore(10000000,'\n'); cout << "Please enter a valid number (numbers between 1 and 6)." << endl;}
        }
        if (foehand == 6 && turnend == false)
        {
            foedecision = rand() % 6 + 1;

            int lowNumberIndex = 0;
            int highNumberIndex = 0;
            float average = 0;
            for (int i = 0; i <= 5; i++)
            {
                average += foenumbers[i];
                if (foenumbers[i] < foenumbers[lowNumberIndex]) {lowNumberIndex = i;}
                if (foenumbers[i] > foenumbers[highNumberIndex]) {highNumberIndex = i;}
            }
            average /= 6;
            if (foenumbers[highNumberIndex] - average > average - foenumbers[lowNumberIndex]) {foedecision = highNumberIndex + 1;}
            else if (foenumbers[highNumberIndex] - average < average - foenumbers[lowNumberIndex]) {foedecision = lowNumberIndex + 1;}
            else if (foenumbers[highNumberIndex] - average == average - foenumbers[lowNumberIndex])
            {
                if (rand() % 2 == 1) {foedecision = highNumberIndex + 1;}
                else if (rand() % 2 == 0) {foedecision = lowNumberIndex + 1;}
            }
            for (int i = 1; i <= 6; i++)
            {
                for (int j = 1; j <= 6; j++)
                {
                    if (foenumbers[i-1] == foenumbers[j-1] && i != j) {foedecision = j;}
                }
            }
            cout << "Your opponent discarded a " << foenumbers[foedecision - 1] << " of " << foepales[foedecision - 1] <<"." << endl; foenumbers[foedecision - 1] = 0; foehand--; foedecision = -1;
            foedecision = -1;
        }
        for (int i = 0; i <= 5; i++)
        {
            for (int j = 0; j <= 5; j++)
            {
                if (numbers[i] == (numbers[j] + 1)) {points++;}
                else if (numbers[i] == numbers[j] && j != i) {points = -1000;}
                if (foenumbers[i]==(foenumbers[j] + 1) && foenumbers[i] != 0) {foepoints++;}
                else if (foenumbers[i] == foenumbers[j] && j != i) {foepoints = -1000;}
            }
        }
        if (points == 4 && foepoints == 4) {cout << "It's a draw"; gameover = true; power = -1000;}
        else if (points == 4) {cout << "You win!"; gameover = true; power = -1000;}
        else if (foepoints == 4) {cout << "Your opponent has finished his straight! You lose..."; gameover = true; power = -1000;}
        else {points = 0; foepoints = 0;}
        power++;
        if (power == 3)
        {
            cout << "Time to discard!" << endl;
            while(true)
            {
                cin >> discardnumber;
                if (discardnumber >= 1 && discardnumber <= 13) {break;}
                else {cin.clear(); cin.ignore(10000000,'\n'); cout << "Please enter a valid number (numbers between 1 and 13)." << endl;}
            }
            int average = 0;
            for (int i = 0; i <= 2; i++) {average += foemind[i]; foemind[i] = 0;}
            foediscardnumber = 13 - average/3;
            cout << "Your opponent has chosen the number " << foediscardnumber << "." << endl;
            for (int i = 0; i <= 5; i++)
            {
                if (foediscardnumber == numbers[i]){cout << "Discarded " << numbers[i] << " of " << pales[i] <<"." << endl; numbers[i] = 0; hand--;}
            }
            if (hand == 5) {cout << "You don't have any " << foediscardnumber << " in your hand." << endl;}
            power = 0;

            for (int i = 0; i <= 5; i++)
            {
                if (discardnumber == foenumbers[i]){cout << "Your opponent discarded a " << foenumbers[i] << " of " << foepales[i] <<"." << endl; foenumbers[i] = 0; foehand--;}
            }
            if (foehand == 5) {cout << "Your opponent doesn't have any " << discardnumber << " in his hand." << endl;}

        }
        turnend = true;

        if (turn == 0 && hand == 5) {Sleep(100); cout << "Start!" << endl;}
        if (turnend == true && gameover == false) {Sleep(200); turn++; cout << endl << endl; cout << "Turn " << turn << "." << endl; turnend = false;}
    }
    return 0;
}
