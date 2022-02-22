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
string DealCard (int deck[], int playerindex);
// This function takes the array of 52 crads and the player number and return the card that is dealt
int ScoreHand(int deck[], int playerindex);
// This function takes the cards that were dealt and returns the sum of them
int wholedeck(int deck[]);
//assigns all the values in the deck array to be -1 so that it will not overlap with any index numbers
bool split(int deck[], int playerindex);

bool AceDecision(int deck[], int playerindex);

int main() {
    const int decksize = 52;
    int allcards[decksize];
    wholedeck (allcards);
    // array of 52 where the player number will be stored
    // assigns all the values in the deck array to be -1 so that it will not overlap with any index numbers
    
    int j = 0;
    
    srand(time(0));
    
    vector<string> carddealer(2);
    vector<string> cardplayer(2);
    string twocards[2];
    
    carddealer.at(0) = DealCard(allcards, 0);
    carddealer.at(1) = DealCard(allcards, 0);
    // comes up with two randomly dealt cards for the dealer
    
    twocards[0] = carddealer.at(0) + " " + carddealer.at(1);
    // adds the two strings with two cards into one string
    

    
    cout << setw(17) << left << "Dealer has cards: " << setw(20) << twocards[0]
    << "(" << ScoreHand(allcards, 0) << ")" << endl;
    
    cardplayer.at(0) = DealCard(allcards, 1);
    cardplayer.at(1) = DealCard(allcards, 1);
    // comes up with two randomly dealt cards for the player
    
    twocards[1] = cardplayer.at(0) + " " + cardplayer.at(1);
    // adds the two strings with two cards into one string
    
    if (AceDecision(allcards, 1) == true) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1]
        << "(" << ScoreHand(allcards, 1) << ")" << " or " << "(" << ScoreHand(allcards, 1)+10 << ")" << endl;
        
        cout << "Ace = 1 or Ace = 11" << "? ";
        int ace;
        cin >> ace;
        if (ace == 11) {
            ScoreHand(allcards, 1) + 10;
            cout << ScoreHand(allcards,1);
        }
    }
    
    else {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1]
        << "(" << ScoreHand(allcards, 1) << ")" << endl;
    }
    
  
    
    
    
    
    /*if (split(allcards, 1) == true) {
        string splitdecision;
        cout << setw(16) << "Would you like to split" << "? ";
        cin >> splitdecision;
        while (!(splitdecision == "yes" || splitdecision == "no"))
        
        
        {
            cout << setw(16) << left << "Would you like to split" << "? ";
            cin >> splitdecision;
        }
        
        if (splitdecision == "yes") {
            
        }

    }*/
    
    
    
    cout << setw(16) << left << "Hit or stand" << "? ";
    string decision;
    cin >> decision;
    while (!(decision == "hit" || decision == "stand")) {
        cout << setw(16) << left << "Hit or stand" << "? ";
        cin >> decision;
    }
    
    for (j = 0; decision == "hit"; ++j) {
        
        cout << endl << setw(17) << left << "Dealer has cards: " << setw(20) << twocards[0]
        << "(" << ScoreHand(allcards, 0) << ")" << endl;
        
        cardplayer.push_back(DealCard(allcards, 1));
        twocards[1] = twocards[1] + " " + cardplayer.at(j+2);
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        if (ScoreHand(allcards, 1) > 21) {
            cout << "Player busts, dealer wins!\n";
            return 0;
        }
        
        cout << setw(16) << left << "Hit or stand" << "? ";
        cin >> decision;
        while (!(decision == "hit" || decision == "stand")) {
            cout << setw(16) << left << "Hit or stand" << "? ";
            cin >> decision;
        }
        if (decision == "stand") {
            break;
        }
    }
    
    cout << endl;
    
    if (ScoreHand(allcards, 0) > 17) {
        cout << setw(16) << left << "Dealer has cards" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
    }
    
    for (j = 0; ScoreHand(allcards, 0) < 18; ++j) {
        
        cardplayer.push_back(DealCard(allcards, 0));
        twocards[0] = twocards[0] + " " + cardplayer.at(j+2);
        cout << setw(16) << left << "Dealer hits" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
        
        if (ScoreHand(allcards, 0) > 21) {
            cout << "Dealer busts, player wins!\n";
            return 0;
        }
        if (ScoreHand(allcards,0) > 18) {
            cout << setw(16) << left << "Dealer stands" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl << endl;
            cout << setw(16) << left << "Dealer has cards" << ": " << setw(20) << twocards[0] << "(" << ScoreHand(allcards,0) << ")" << endl;
        }
    }
    
    if (ScoreHand(allcards,0) == ScoreHand(allcards,1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Player and dealer draw.\n";
        return 0;
    }
    
    if (ScoreHand(allcards,0) > ScoreHand(allcards, 1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Dealer wins!\n";
        return 0;
    }
    
    if (ScoreHand(allcards, 0) < ScoreHand(allcards, 1)) {
        cout << setw(16) << left << "You have cards" << ": " << setw(20) << twocards[1] << "(" << ScoreHand(allcards,1) << ")" << endl;
        cout << "Player wins!\n";
        return 0;
    }
    
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

bool split(int deck[], int playerindex) {
    int score = 0;
    bool possible = false;
    vector<int> cardvalue(2, 0);
    string number;
    
    for (int k = 0; k < 52; ++k) {
        if (deck[k] == playerindex) {
            int remainder = k%13;
            
            if (cardvalue.at(0) == 0) {
                cardvalue.at(0) = remainder;
        }
            else {
                cardvalue.at(1) = remainder
                ;
            }
        }
        if (cardvalue.at(0) == cardvalue.at(1)) {
            possible = true;
        }
        else {
            possible = false;
        }
}
    return possible;
}

bool AceDecision(int deck[], int playerindex) {
    bool ace = false;
    for (int k = 0; k < 52; ++k) {
        if (deck[k] == playerindex) {
            int remainder = k%13;
            if (remainder == 1) {
                ace = true;
                break;
            }
        }
    }
    return ace;
}
