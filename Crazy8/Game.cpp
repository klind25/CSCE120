#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include "Game.h"
using std::string, std::vector, std::cout, std::endl;

Game::Game(): players({}), suits({}), ranks({}), 
    deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename){
    // TODO: initialize suits, ranks, deck, and drawPile from the given file
    string suit_line;
    string rank_line;
    string suit;
    string rank;
    Card* card = nullptr;
    bool inSuit = false;
    bool inRank = false;

    std::ifstream file;

    file.open(filename); //open

    if (!file.is_open()) { // Check if open
        throw std::runtime_error("File did not open");
    }

    getline(file, suit_line); // Read first two lines
    getline(file, rank_line); 

    std::istringstream readSuit(suit_line); // Create new area for line
    std::istringstream readRank(rank_line);

    if (suit_line.empty() || rank_line.empty() || file.fail()) {
        std::runtime_error("Blank line");
    }

    while (readSuit >> suit) { // Separates line by space
        suits.push_back(suit);
    }
    while (readRank >> rank) {
        ranks.push_back(rank);
    }

    string line;
    string more;

    while (getline(file, line)) {// Get line

        inSuit = false;
        inRank = false;

        std::istringstream cardLine(line); // Make line string stream
        rank.clear(); // Initialize
        suit.clear();
        
        if (!(cardLine >> rank >> suit)) { // Not rank then suit
            throw std::runtime_error("Bad format");
        }

        if (suit.empty()) {
            throw std::runtime_error("Too few inputs");
        }

        if (cardLine >> more) {
            throw std::runtime_error("Too many inputs");
        }

        for (long unsigned int i = 0; i < suits.size(); ++i) { // Valid suit
            if (suits.at(i) == suit) {
                inSuit = true;
                break;
            }
        }

        if (!inSuit) {
            throw std::runtime_error("Invalid suit");
        }

        for (long unsigned int i = 0; i < ranks.size(); ++i) { // Valid rank
            if (ranks.at(i) == rank) {
                inRank = true;
                break;
            }
        }

        if (!inRank) {
            throw std::runtime_error("Invalid rank");
        }

        try { // If it can be a card
            card = new Card(rank, suit);
        }
        catch (const std::invalid_argument&) {
            throw std::runtime_error("Invalid argument");
        }

        deck.push_back(card); // Update decks
        drawPile.insert(drawPile.begin(), card);

    }

    file.close();
}

void Game::addPlayer(bool isAI){
    // TODO: add a new player to the game
    Player* player = new Player(isAI);
    players.push_back(player);
}

void Game::drawCard(Player* p){
    // TODO: Move the top card of the draw pile to Player p's hand
    // If the draw pile is empty, flip the discard pile to create a new one
    Card* card;
    Card* top;

    if (!drawPile.empty()) {
        card = drawPile.back(); // Get back card
        p->addToHand(card); // Add to hand
        drawPile.pop_back(); // Remove from draw
    }

    else if (drawPile.empty() && (discardPile.size() <= 1)) { // no cards
        throw std::runtime_error("No cards");
    }

    else { // No draw pile
        cout << "Draw pile, empty, flipping the discard pile." << endl;
        top = discardPile.back();

        discardPile.pop_back();
        while (discardPile.size() != 0) { // Until empty
            card = discardPile.back(); // get top
            drawPile.push_back(card); // put in draw
            discardPile.pop_back(); // get rid of top
        } 

        discardPile.push_back(top); // Get top card back

        card = drawPile.back(); // Then draw card
        p->addToHand(card);
        drawPile.pop_back(); 

    }

}

//deals numCards cards to each player
Card* Game::deal(int numCards){
    // TODO: Flip the top card of the draw pile to be the initial discard
    // then deal numCards many cards to each player
    Card* card;

    card = drawPile.back(); // get top
    discardPile.push_back(card); // put in draw
    drawPile.pop_back(); // get rid of top

    for (int i = 0; i < numCards; ++i) {
        for (long unsigned int j = 0; j < players.size(); ++j) {
            drawCard(players.at(j));
        }
    }

    return card;

}

string Game::mostPlayedSuit(){
    // TODO: Return the suit which has been played the most times
    // if there is a tie, choose any of the tied suits
    string suit;
    vector <int> values(suits.size(), 0);

    for (long unsigned int i = 0; i < deck.size(); ++i) { // All cards
        for (long unsigned int j = 0; j < suits.size(); ++j) { // Each suit
            if (deck.at(i)->getSuit() == suits.at(j)) { // If current suit
                values.at(j) += deck.at(i)->getTimesPlayed(); // Increase times played
            }    
        }
    }
    int high = values.at(0);
    int index = 0;
    for (long unsigned int i = 1; i < suits.size(); ++i) { // Checks highest
        if (high < values.at(i)) {
            index = i; // Index of highest suit
            high = values.at(i);
        }
    }
    suit = suits.at(index);
    return suit;
}

int Game::runGame(){
    // TODO: Run the game and return the number of the winning player
    bool winner = false;
    Card* card;

    if (discardPile.empty()) {
        throw std::runtime_error("Empty discard pile");
    }

    string currentRank = discardPile.back()->getRank();
    string currentSuit = discardPile.back()->getSuit();

    while (!winner) {
        for (long unsigned int i = 0; i < players.size(); ++i) {
            cout << "Player " << i << "'s turn!" << endl;
            card = players.at(i)->playCard(suits, currentRank, currentSuit); // Get card

            if (card == nullptr) { // Drawing
                try {
                    drawCard(players.at(i));
                    /*cout << endl;
                    cout << drawPile.size() << endl;
                    cout << discardPile.size() << endl;
                    cout << endl;*/
                    cout << "Player " << i << " draws a card." << endl;
                }
                catch (const std::runtime_error&) {
                    cout << "Player " << i << " cannot draw a card." << endl;
                    return -1;
                }
            }

            else if (card->getRank() == "8") { // 8
                cout << "Player " << i << " plays " << card->getRank() << " " << card->getSuit() << " and changes the suit to " << currentSuit << "." << endl;
                discardPile.push_back(card);
            }

            else {
                cout << "Player " << i << " plays " << card->getRank() << " " << card->getSuit() << "." << endl;
                discardPile.push_back(card);

            }

            if (players.at(i)->getHandSize() == 0) {
                return i;
            }

        }

    }
    return -1;
}

//Destructor--Deallocates all the dynamic memory we allocated
Game::~Game(){
    for (unsigned int i = 0; i < deck.size(); i++){
        delete deck.at(i);
    }
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players.at(i);
    }
}
