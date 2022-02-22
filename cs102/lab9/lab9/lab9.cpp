//  Casey Mackinnon
//  lab8
//
//  Black Jack: For this lab the dealer and the player will be dealt 2 cards.
//  No duplicate cards should be dealt. If they wish to have more cards, they can hit.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;

int GetRandom (int min, int max);
// This function takes the maximum and minumum value and comes up with a random number between them
string DealCard (int deck[52], int playerindex);
// This function takes the array of 52 crads and the player number and return the card that is dealt
int ScoreHand(int deck[52], int playerindex);
// This function takes the cards that were dealt and returns the sum of them
int wholedeck(int deck[52]);
//assigns all the values in the deck array to be -1 so that it will not overlap with any index numbers


int main() {
    const int decksize = 52;
    int allcards[decksize];
    wholedeck (allcards);
    // array of 52 where the player number will be stored
    // assigns all the values in the deck array to be -1 so that it will not overlap with any index numbers
    
    int j = 0;
    
    srand(time(0));
    
    vector<string> carddealer(2);
    //vector where the card for the dealer will be stored
    vector<string> cardplayer(2);
    // vector where the card for the player will be stored
    string twocards[2];
    
        carddealer.at(0) = DealCard(allcards, 0);
        carddealer.at(1) = DealCard(allcards, 0);
        // comes up with two randomly dealt cards for the dealer
        
        twocards[0] = carddealer.at(0) + " " + carddealer.at(1);
        // adds the two strings with two cards into one string
    
    cout << setw(17) << left << "Dealer has cards: " << setw(20) << twocards[0]
         << "(" << ScoreHand(allcards, 0) << ")" << endl;
    // prints out the cards the dealer is dealt and its total
    
        cardplayer.at(0) = DealCard(allcards, 1);
        cardplayer.at(1) = DealCard(allcards, 1);
        // comes up with two randomly dealt cards for the player
    
        twocards[1] = cardplayer.at(0) + " " + cardplayer.at(1);
        // adds the two strings with two cards into one string
    
    cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1]
    << "(" << ScoreHand(allcards, 1) << ")" << endl;
    // prints out the cards the player is dealt and its total
    
    cout << setw(16) << left << "Hit or stand" << "? ";
    string decision;
    cin >> decision;
    while (!(decision == "hit" || decision == "stand")) {
        cout << setw(16) << left << "Hit or stand" << "? ";
        cin >> decision;
    }
    // gives an option to the dealer if they want to hit or not
   
    for (j = 0; decision == "hit"; ++j) {
       
        cout << endl << setw(17) << left << "Dealer has cards: " << setw(20) << twocards[0]
        << "(" << ScoreHand(allcards, 0) << ")" << endl;
        // prints out the player's cards if they decide to hit and its total
        
        cardplayer.push_back(DealCard(allcards, 1));
        twocards[1] = twocards[1] + " " + cardplayer.at(j+2);
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        if (ScoreHand(allcards, 1) > 21) {
            cout << "Player busts, dealer wins!\n";
            return 0;
        }
        // if the player's total is over 21 here, the player loses and returns 0
        
        cout << setw(16) << left << "Hit or stand" << "? ";
        cin >> decision;
        while (!(decision == "hit" || decision == "stand")) {
            cout << setw(16) << left << "Hit or stand" << "? ";
            cin >> decision;
        }
        // asks the player if they want to hit
        if (decision == "stand") {
            break;
        }
        // if they decide to stand, it will exit the loop
    }
    // the loop will continue as long as the player decides to keep on hitting or the total is over 21
    
    cout << endl;
    
    if (ScoreHand(allcards, 0) > 17) {
        cout << setw(16) << left << "Dealer has cards" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
    }
    // if the dealer's total is 18 and above, he will not hit
    
    for (j = 0; ScoreHand(allcards, 0) < 18; ++j) {
        
        cardplayer.push_back(DealCard(allcards, 0));
        twocards[0] = twocards[0] + " " + cardplayer.at(j+2);
        cout << setw(16) << left << "Dealer hits" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
        // if the total is below 18, the dealer will hit
        
        if (ScoreHand(allcards, 0) > 21) {
            cout << "Dealer busts, player wins!\n";
            return 0;
        }
        // if the total is over 21, the dealer busts and the player wins. returns 0
        
        if (ScoreHand(allcards,0) > 18) {
            cout << setw(16) << left << "Dealer stands" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl << endl;
            cout << setw(16) << left << "Dealer has cards" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
            //prints out what the dealer is doing and what cards he has after he hits
        }
    }
    
    if (ScoreHand(allcards,0) == ScoreHand(allcards,1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Player and dealer draw.\n";
        return 0;
    }
    //if the total of the dealer and the player is equal, they tie
    
    if (ScoreHand(allcards,0) > ScoreHand(allcards, 1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Dealer wins!\n";
        return 0;
    }
    // if the total of the dealer is greater than the one of player, the dealer wins
    
    if (ScoreHand(allcards, 0) < ScoreHand(allcards, 1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Player wins!\n";
        return 0;
    }
    // of the total of the dealer is less than the one of player, the player wins
    
    return 0;
}

int wholedeck (int deck[]) {
    for (int i = 0; i < 52; ++i) {
        deck[i] = -1;
    }
    return deck[52];
}

int GetRandom (int min, int max) {
    int random;
    random = min + rand() % (max);
    // Comes up with a random number
    return random;
}

string DealCard (int deck[], int playerindex) {
    
    const string cardsuits[4] = {"S", "H", "C", "D"};
    const string cardnumbers[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    
    int randomnumber;
    int pass = 0;
    while (pass == 0) {
        randomnumber = GetRandom(1, 52);
        // comes up with a number between 1 and 52 inclusive
        
        if (!(deck[randomnumber] == -1)) {
            pass = 0;
        }
        else {
            deck[randomnumber] = playerindex;
            pass = 1;
        }
        // This sees whether the random number that was generated was already used. If yes, it goes to the next step. Other wise it will come up with another random number. It does this until the number is unique.
    }
    
    string card;
    string suit;
    string number;
    
    suit = cardsuits[(randomnumber-1)/13];
    // takes the random number and comes up with suit the card will have
    
    number = cardnumbers[(randomnumber-1)%13];
    
    // takes the random number and comes up with the value of the card
    
    card = number+suit;
    // adds the value and suit together
    
    return card;
}

int ScoreHand(int deck[], int playerindex) {
    int score = 0;
    
    for (int k = 0; k < 52; ++k) {
        if (deck[k] == playerindex) {
            int remainder = k%13;
            switch (remainder) {
                case 0:
                    score = score + 10;
                    break;
                case 11:
                    score = score + 10;
                    break;
                case 12:
                    score = score + 10;
                    break;
                default:
                    score = score + remainder;
                    break;
            }
            // This takes the two cards of the player and adds up them together to come up with the sum of it
            
        }
    }
    
    return score;
}


