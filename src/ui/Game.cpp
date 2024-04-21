#include "../../include/ui/Game.hpp"
#include <iostream>

Game::Game()
    : m_turn_number(0)
    , m_player("Player")
{
    srand(time(NULL));
    while (m_player.getHandRef().getSize() < MAX_HAND_SIZE - 1) {
        Card card_drawn = m_player.getHandRef().draw();
        std::cout << "Drew " << card_drawn << "." << std::endl;
    }
    while (m_opponent.getHandRef().getSize() < MAX_HAND_SIZE - 1) {
        m_opponent.getHandRef().draw();
        std::cout << "Your opponent drew a card." << std::endl;
    }
    std::cout << "Start!" << std::endl;
}

std::pair<bool, int> Game::checkWinningConditions() const
{
    bool player_win = m_player.getConstHandRef().isStraight();
    bool foe_win = m_opponent.getConstHandRef().isStraight();
    if (player_win && foe_win) {
        return { true, 0 };
    } else if (player_win) {
        return { true, 1 };
    } else if (foe_win) {
        return { true, -1 };
    }
    return { false, 0 };
}

void Game::nextTurn()
{
    m_turn_number++;
    std::cout << std::endl
              << std::endl;
    std::cout << "Turn " << m_turn_number << "." << std::endl;
    while (m_player.getHandRef().getSize() < MAX_HAND_SIZE) {
        Card card_drawn = m_player.getHandRef().draw();
        std::cout << "Drew " << card_drawn.getNumber() << " of " << card_drawn.getPale() << "." << std::endl;
    }
    while (m_opponent.getHandRef().getSize() < MAX_HAND_SIZE) {
        m_opponent.getHandRef().draw();
        std::cout << "Your opponent drew a card." << std::endl;
    }
    std::cout << m_player.getHandRef() << std::flush;
}

void Game::executeTurn()
{
    std::cout << "Discard 1 card." << std::endl;
    int decision = inputNumberInRange(1, MAX_HAND_SIZE);

    // Delete card
    Card discarded_card = m_player.getHandRef().discard(decision - 1);
    std::cout << "Discarded " << discarded_card << "." << std::endl;

    // Store discarded card to foe's memory
    m_opponent.rememberOpponentChoice(discarded_card.getNumber());

    int foedecision = m_opponent.chooseCardToDiscard(m_opponent.getHandRef().getArray());
    Card opponent_discarded_card = m_opponent.getHandRef().discard(foedecision - 1, true);
    std::cout << "Your opponent discarded a " << opponent_discarded_card << "." << std::endl;
}

bool Game::isGameOver()
{
    std::pair<bool, int> game_outcome = checkWinningConditions();
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

bool Game::isDiscardRound()
{
    return m_turn_number % 3 == 0 && m_turn_number > 0;
}

void Game::checkDiscardRound()
{
    if (isDiscardRound()) {
        std::cout << "Time to discard!" << std::endl;
        int discardnumber = inputNumberInRange(1, 13);

        int foediscardnumber = m_opponent.chooseNumberToDeclare();
        std::cout << "Your opponent has chosen the number " << foediscardnumber << "." << std::endl;

        const std::vector<Card>& discarded_cards = m_player.getHandRef().discardAllByNumber(foediscardnumber);
        for (const Card& card : discarded_cards) {
            std::cout << "Discarded " << card << "." << std::endl;
        }
        if (discarded_cards.size() == 0) {
            std::cout << "You don't have any " << foediscardnumber << " in your hand." << std::endl;
        }

        const std::vector<Card>& opponent_discarded_cards = m_opponent.getHandRef().discardAllByNumber(discardnumber, true);
        for (const Card& card : opponent_discarded_cards) {
            std::cout << "Your opponent discarded " << card << "." << std::endl;
        }
        if (opponent_discarded_cards.size() == 0) {
            std::cout << "Your opponent doesn't have any " << discardnumber << " in his hand." << std::endl;
        }
    }
}

int Game::inputNumberInRange(int lower, int upper)
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