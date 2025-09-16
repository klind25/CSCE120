#include<iostream>
#include<sstream>
#include "Player.h"
using std::vector, std::string, std::size_t, std::cin, std::cout, std::endl;

Player::Player(bool isAI) : isAI(isAI), hand{} {

}

void Player::addToHand(Card* c){
    // TODO: Add the card c to the player's hand
    hand.push_back(c); // Push card

}

size_t Player::getHandSize(){
    // TODO: Implement getter
    return hand.size();
}

std::string Player::getHandString(){
    // TODO: Implement getter
    string cards;

    for (long unsigned int i = 0; i < hand.size(); ++i) {
        cards.append(hand.at(i)->getRank()); // Appends rank
        cards.append(" "); // Adds space
        cards.append(hand.at(i)->getSuit()); // Appends suit

        if (i != hand.size() - 1) {
            cards.append(", "); // Comma separated list
        }
    }
    return cards;
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
    // TODO: Choose a card to play and return the chosen card
    Card* card;
    string rank;
    string suit;
    bool valid = false;
    bool inHand = false;
    bool playable = false;
    int index;
    bool aicard = false;
    string chosen;

    if(!isAI) { // Person
        cout << "Your hand contains: " << getHandString() << endl;
        cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;
        cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;
        while (!valid) {
            
            cin >> rank;
            cin >> suit;

            if (rank == "draw") { // Not playing anything
                return nullptr;
            }

            for (long unsigned int i = 0; i < hand.size(); ++i) { // Checks if in hand
                if ((hand.at(i)->getRank() == rank) && (hand.at(i)->getSuit() == suit)) {
                    inHand = true;
                    index = i;
                    break;
                }
            }
            
            if (inHand) { // Checks if it can be played
                if (hand.at(index)->canBePlayed(currentRank, currentSuit)) {
                    card = hand.at(index);
                    valid = true;
                    
                    hand.erase(hand.begin() + index);
                    break;
                }
            }

            if (!inHand) {
                cout << "That's not a card you have. Try again." << endl;
            }
            else if (!playable) {
                cout << "You can't play that card. Try again." << endl;
            }

            inHand = false;
            playable = false;

        }

    }
    else { // AI
        for (long unsigned int i = 0; i < hand.size(); ++i) {
            if (hand.at(i)->canBePlayed(currentRank, currentSuit)) { // First valid card
                card = hand.at(i);
                hand.erase(hand.begin() + i);
                aicard = true;
                break;
            }
        }
        if (!aicard) {
            return nullptr;
        }
    }

    card->play(); // Update times played

    valid = false;

    if (card->getRank() == "8") { // Picking suit
        if (!isAI) { // Person chooses suit, AI doesn't

            cout << "What suit would you like to declare?" << endl;

            while(!valid) {
                cin >> chosen;
                for (long unsigned int i = 0; i < suits.size(); ++i) { // Check if valid
                    if (suits.at(i) == chosen) {
                        valid = true;
                        currentSuit = chosen;
                        break;
                    }
                }
                if (!valid) {
                    cout << "That's not a suit in this deck. Try again." << endl;
                }
            }
        }
        else {
            currentSuit = card->getSuit(); // update current
        }
    }

    else {
        currentSuit = card->getSuit(); // update current
    }
    
    currentRank = card->getRank(); // update current
    return card;

}
