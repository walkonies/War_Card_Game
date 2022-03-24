#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Functions completed:
    Make deck
    Start
    Shuffle deck
    Deal deck
    Compare
    Game loop
 Class functions completed:
    Set id
    Get id
    Add card to hand
    Remove card from hand
    Number of cards
    Get card
    Remove top card
    Get top card
    Show hand
 Functions needed:
    Fix shuffler
 */

class Player{
private:
    int hand[52];    //Allocating memory to hold up to 52 cards
    int id;
    int numCards = 0;
public:
    
    // Set player id number
    void setId(int num){
        id = num;
    }
    
    // Return id number
    int getId(){
        return id;
    }
    
    // Add card to hand
    void addCard(int card){
        hand[numCards] = card;
        numCards ++;
    }
    
    // Remove card from hand
    void removeCard(int index){
        hand[index] = hand[numCards -1];
        hand[numCards -1] = 0;
        numCards --;
    }
    
    // Return number of cards
    int getNumCards(){
        return numCards;
    }
    
    // Return card at index
    int getCard(int index){
        return hand[index];
    }
     
    // Remove top card from deck
    void removeTopCard(){
        if (numCards > 1){
            for (int i = 0 ; i < numCards -1; i++){
                hand[i] = hand[i+1];
            }
            hand[numCards] = 0;
            numCards --;
        }
        else{
            hand[0] = 0;
            numCards = 0;
        }
    }
    
    // Return top card
    int getTopCard(){
        return hand[0];
    }
    
    // Show cards in hand
    void showHand(){
        for (int i = 0 ; i < numCards ; i ++){
            // Switch statement to replace numbers to face cards
            switch (hand[i]) {
                case 11:
                    cout << "Jack";
                    break;
                case 12:
                    cout << "Queen";
                    break;
                case 13:
                    cout << "King";
                    break;
                case 1:
                    cout << "Ace";
                    break;
                default:
                    cout << hand[i];
                    break;
            }
            if (i != numCards - 1){
                cout << ", ";
            }
        }
        cout << endl;
    }
};

// Random array print function
void print(int arr[], int size){
    for (int i = 0; i < size ; i ++){
        cout << arr[i] << endl;
    }
}

// Make deck with x number of decks
void makeDeck(int num, int deck[]){;
    
    int cards[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    for (int i = 0 ; i < num * 4 ; i ++){
        for (int j = 0 ; j < 13 ; j++){
            deck[(i *13) + j] = cards[j];
        }
    }
}

// Get number of decks and players
void start(int *decks, int *players){
    
    cout << "Number of players: ";
    cin >> (*players);
    
    cout << "Number of decks: ";
    cin >> (*decks);
    
    
}

// Shuffle deck
void shuffleDeck(int deck[], int numCards){
    int temp, randIndex;
    
    for (int i = 0 ; i < numCards ; i++){
        randIndex = rand() % numCards;
        temp = deck[i];
        deck[i] = deck[randIndex];
        deck[randIndex] = temp;
    }
}

// Deal all cards to players (may need to make function to
// deal specefic number of cards to each player, depending on game)
void dealCards(Player players[], int numCards, int deck[], int numPlayers){
    for (int i = 0 ; i < numCards/numPlayers ; i ++){
        for (int j = 0 ; j < numPlayers ; j++){
            players[j].addCard(deck[(i* numPlayers)+j]);
        }
    }
}

// Compare values of two cards and return player with highest
// return 0 if same value
int compare(int card1, int card2){
    if (card1 > card2){
        return 1;
    }
    else if (card2 > card1){
        return 2;
    }
    else{
        return 0;
    }
}


// Main game loop
void war_game(Player players[], int player1, int player2){
    int roundWinner, rounds = 0;      // Variables for round winner and round counter
    int winner;
    
    
    // While players still have cards
    while (players[player1].getNumCards() > 0 & players[player2].getNumCards() > 0){
        rounds ++;                                 // Increment round
        int card1 = players[player1].getTopCard();       // Top card of player 1
        int card2 = players[player2].getTopCard();       // Top card of player 2
        
        players[player1].showHand();                     // Show current hand of player 1
        players[player2].showHand();                     // Show current hand of player 2
        cout << endl;
        cout << card1 << " vs " << card2 << endl;  // Print card matchup
        cout << endl;
        
        roundWinner = compare(card1, card2);       // Compare cards and store winner in winner variable
        
        // If player 1 wins
        if (roundWinner == 1){
            players[player1].removeTopCard();     // Remove top card from player 1 deck
            players[player2].removeTopCard();     // Remove top card from player 2 deck
            players[player1].addCard(card1);      // Add card 1 back to bottom of deck
            players[player1].addCard(card2);      // Add card 2 card to bottom of deck
        }
        
        // If player 2 wins
        else if (roundWinner == 2){
            players[player1].removeTopCard();     // Remove top card from player 1 deck
            players[player2].removeTopCard();     // Remove top card from player 2 deck
            players[player2].addCard(card1);      // Add card 1 back to bottom of deck
            players[player2].addCard(card2);      // Add card 2 card to bottom of deck
        }
        
        // If draw
        else{
            roundWinner = compare(players[player1].getCard(3), players[player2].getCard(3));
            
            if (roundWinner == 1 & players[player1].getNumCards() > 4 & players[player2].getNumCards() > 4){
                // Take 4 cards
                for (int i = 0 ; i < 5 ; i++){
                    players[player1].removeTopCard();     // Remove top card from player 1 deck
                    players[player2].removeTopCard();     // Remove top card from player 2 deck
                    players[player1].addCard(card1);      // Add card 1 back to bottom of deck
                    players[player1].addCard(card2);      // Add card 2 card to bottom of deck
                }
            }
            else if (roundWinner == 2 & players[player1].getNumCards() > 4 & players[player2].getNumCards() > 4){
                // Take 4 cards
                for (int i = 0 ; i < 5 ; i++){
                    players[player1].removeTopCard();     // Remove top card from player 1 deck
                    players[player2].removeTopCard();     // Remove top card from player 2 deck
                    players[player2].addCard(card1);      // Add card 1 back to bottom of deck
                    players[player2].addCard(card2);      // Add card 2 card to bottom of deck
                }
            }
            // Not enough cards
            else{
                players[player1].removeTopCard();     // Remove top card from deck
                players[player2].removeTopCard();     // Remove top card from deck
                players[player1].addCard(card1);      // Put card back on bottom of deck
                players[player2].addCard(card2);      // Put card back on bottom of deck
            }
        }
    }
    
    // Get winner
    if (players[player1].getNumCards() > 0){
        winner = players[player1].getId();
    }
    else{
        winner = players[player2].getId();
    }
    
    // Print winner and number of rounds
    cout << "Winner: Player " << winner << "!" << endl;
    cout << "Rounds: " << rounds << endl;
}

    
int main(){
    int numDecks, numPlayers;
    int *numDecksptr = &numDecks;
    int *numPlayersptr = &numPlayers;
    const int CARDS_IN_DECK = 52;
    int numCards;
    
    start(numDecksptr, numPlayersptr);       // Get number of decks and number of players
    numCards = numDecks * CARDS_IN_DECK;     // Number of cards is 52 times number of decks
    
    int deck[numCards];             // Create deck array to hold all cards
    
    makeDeck(numDecks, deck);       // Initialize deck array
    
    shuffleDeck(deck, numCards);    // Shuffle deck
    
    Player players[numPlayers];     // Create array of players
    
    for (int i = 0 ; i < numPlayers ; i ++){
        players[i].setId(i + 1);    // Set id of players starting at 1
    }
    
    dealCards(players, numCards, deck, numPlayers);   // Deal all cards to players
    
    war_game(players, players[0].getId()-1, players[1].getId()-1);  // Start main game loop
    
    return 0;
}
