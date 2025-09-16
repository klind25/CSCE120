#include<cctype>
#include<stdexcept>
#include "Card.h"
using std::string;

Card::Card(string rank, string suit) : rank(rank), suit(suit), timesPlayed(0) { // Initialize classes with inputs
    // TODO: implement constructor checks
    if (suit == "\0" || rank == "\0") { // Check if empty
        throw std::invalid_argument("Invalid");
    }
    for (long unsigned int i = 0; i < rank.size(); ++i) {
        if (!(std::isalpha(rank.at(i)) || std::isdigit(rank.at(i)))) { // Check is not number or letter
            throw std::invalid_argument("Invalid");
        }
    }
    for (long unsigned int i = 0; i < suit.size(); ++i) {
        if (!(std::isalpha(suit.at(i)) || std::isdigit(suit.at(i)))) { // Check is not number or letter
            throw std::invalid_argument("Invalid");
        }
    }

}

string Card::getRank(){
    // TODO: implement getter
    return rank;
}

string Card::getSuit(){
    // TODO: implement getter
    return suit;
}

int Card::getTimesPlayed(){
    // TODO: implement getter
    return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit){
    // TODO: return whether or not the card can legally be played
    if (rank == "8" || rank == currentRank || suit == currentSuit) {
        return true;
    }

    return false;
}

void Card::play(){
    timesPlayed++;
}
