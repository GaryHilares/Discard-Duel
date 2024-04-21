#include "../../include/ui/GameUI.hpp"
#include <iostream>

GameUI::GameUI()
{
    std::vector<Card> cards_drawn = m_game.getPlayerRef().getHandRef().drawUntilFull();
    for (Card card : cards_drawn) {
        std::cout << "Drew " << card << "." << std::endl;
    }
    std::vector<Card> opponent_cards_drawn = m_game.getPlayerRef().getHandRef().drawUntilFull();
    for (Card card : opponent_cards_drawn) {
        std::cout << "Your opponent drew a card." << std::endl;
    }
    std::cout << "Start!" << std::endl;
}

void GameUI::nextTurn()
{
    std::cout << std::endl
              << std::endl;
    std::cout << "Turn " << m_game.nextTurnNumber() << "." << std::endl;

    std::vector<Card> cards_drawn = m_game.getPlayerRef().getHandRef().drawUntilFull();
    for (Card card : cards_drawn) {
        std::cout << "Drew " << card << "." << std::endl;
    }

    std::vector<Card> opponent_cards_drawn = m_game.getPlayerRef().getHandRef().drawUntilFull();
    for (Card card : opponent_cards_drawn) {
        std::cout << "Your opponent drew a card." << std::endl;
    }

    std::cout << m_game.getConstPlayerRef().getConstHandRef() << std::flush;
}

void GameUI::executeTurn()
{
    std::cout << "Discard 1 card." << std::endl;
    int decision = inputNumberInRange(1, MAX_HAND_SIZE);

    // Delete card
    Card discarded_card = m_game.getPlayerRef().getHandRef().discard(decision - 1);
    std::cout << "Discarded " << discarded_card << "." << std::endl;

    // Store discarded card to foe's memory
    m_game.getBotPlayerRef().rememberOpponentChoice(discarded_card.getNumber());

    int foedecision = m_game.getBotPlayerRef().chooseCardToDiscard(m_game.getBotPlayerRef().getHandRef().getArray());
    Card opponent_discarded_card = m_game.getBotPlayerRef().getHandRef().discard(foedecision - 1, true);
    std::cout << "Your opponent discarded a " << opponent_discarded_card << "." << std::endl;
}

bool GameUI::isGameOver()
{
    std::pair<bool, int> game_outcome = m_game.checkWinningConditions();
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

void GameUI::checkDiscardRound()
{
    if (m_game.isDiscardRound()) {
        std::cout << "Time to discard!" << std::endl;
        int discardnumber = inputNumberInRange(1, 13);

        int foediscardnumber = m_game.getBotPlayerRef().chooseNumberToDeclare();
        std::cout << "Your opponent has chosen the number " << foediscardnumber << "." << std::endl;

        const std::vector<Card>& discarded_cards = m_game.getPlayerRef().getHandRef().discardAllByNumber(foediscardnumber);
        for (const Card& card : discarded_cards) {
            std::cout << "Discarded " << card << "." << std::endl;
        }
        if (discarded_cards.size() == 0) {
            std::cout << "You don't have any " << foediscardnumber << " in your hand." << std::endl;
        }

        const std::vector<Card>& opponent_discarded_cards = m_game.getBotPlayerRef().getHandRef().discardAllByNumber(discardnumber, true);
        for (const Card& card : opponent_discarded_cards) {
            std::cout << "Your opponent discarded " << card << "." << std::endl;
        }
        if (opponent_discarded_cards.size() == 0) {
            std::cout << "Your opponent doesn't have any " << discardnumber << " in his hand." << std::endl;
        }
    }
}

int GameUI::inputNumberInRange(int lower, int upper)
{
    int input = -1;
    while (true) {
        std::cin >> input;
        if (input >= lower && input <= upper) {
            return input;
        } else {
            std::cin.clear();
            std::cin.ignore(10000000, '\n');
            std::cout << "Please enter a valid number (numbers between " << lower << " and " << upper << ")." << std::endl;
        }
    }
}