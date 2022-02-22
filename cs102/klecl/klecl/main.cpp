//  Casey Mackinnon
//  lab8
//
//  Black Jack: For this lab we enter the number of players and each player will be dealt 2 cards.
//  No duplicate cards should be dealt.

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

int GetRandom (int min, int max);
// This function takes the maximum and minumum value and comes up with a random number between them
string DealCard (int deck[52], int playerindex);
// This function takes the array of 52 crads and the player number and return the card that is dealt
int ScoreHand(int deck[52], int playerindex);
// This function takes the two cards that were dealt and returns the sum of them


int main() {
    
    int allcards[52];
    // array of 52 where the player number will be stored
    int j = 0;

    
    for (int i = 0; i < 52; ++i) {
        allcards[i] = -1;
    }
    // assigns all the values in the deck array to be -1 so that it will not overlap with any index numbers
    
    srand(time(0));
    int playernumber;
    cout << "How many players? ";
    cin >> playernumber;
    // takes the number of players that are going to participate in the game
    
    string card1[playernumber];
    string card2[playernumber];
    
    for (j = 0; playernumber > j; ++j) {
        card1[j] = DealCard(allcards, j);
        card2[j] = DealCard(allcards, j);
    // comes up with two randomly dealt cards for each player and does this for the number of players
        
        string twocards = card1[j] + " " + card2[j];
    // adds the two strings with two cards into one string
        
        cout << "Player " << j+1 << " has cards: " << setw(20) << left << twocards << " "
             << "(" << ScoreHand(allcards, j) << ")" << endl;
    // This prints out which player has which two cards. Also, starting from the first character of the first card, there are 20 spaces (not specifically a space, includes characters as well) until it prints out the total in the parenthesis. The setw(20) allows this and also "left" makes it a a left-justified field.
    }
    return 0;
}


int GetRandom (int min, int max) {
    int random;
    random = min + rand() % (max);
// Comes up with a random number
    return random;
}

string DealCard (int deck[52], int playerindex) {
    
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
    
    if (randomnumber < 14) {
        suit = 'S';
    }
    else if (randomnumber < 27) {
        suit = 'H';
    }
    else if (randomnumber < 40) {
        suit = 'C';
    }
    else {
        suit = 'D';
    }
    // takes the random number and comes up with suit the card will have
    
    int remainder = randomnumber % 13;
    
    switch (remainder) {
        case 11: number = "J";
            break;
        case 12: number = "Q";
            break;
        case 0: number = "K";
            break;
        case 1: number = "A";
            break;
        default: number = to_string(remainder);
            break;
    }
    // takes the random number and comes up with the value of the card
    
    card = number+suit;
    // adds the value and suit together
    
    return card;
}

int ScoreHand(int deck[52], int playerindex) {
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


