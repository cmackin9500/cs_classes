//  COSC102
//  lab5.cpp
//  lab5
//
//  Created by Casey Mackinnon
//
//  Bowling game: multiplayer bowling game, calculates their scores

#include <iostream>
#include <vector>
#include <string>


using namespace std;

vector<string> player(1);
vector<int> totalscore(1,0);
string name;
int minscore;
int maxscore;
string winner;
string loser;

int main() {
    
    cout << "Enter player's name (done for no more players): ";
    cin >> player.at(0);
   
    for (int j = 0; j < totalscore.size(); ++j) {    // this loop continues until the user types done
        name = "0";
        if (player.at(j) == "done") {   // if user types in done, it breaks the loop
            break;
        }
        
        // asks the user tp type in all the scores first
        
        int scores[21];
        for (int i = 0; i < 21; ++i) {
            scores[i] = 0;
        }
        for (int i = 0; i < 18; i = i+2) {   // asks the user to type in the score for the first 9 frames
            cout << "Enter score for frame " << i/2 + 1 << ", roll 1: ";
            cin >> scores[i];
            if (scores[i] == 10) {   // The second throw in the frame will not be asked to type if the user gets a strike
                continue;
            }
            cout << "Enter score for frame " << i/2 + 1 << ", roll 2: ";
            cin >> scores[i+1];
        }
        cout << "Enter score for frame 10, roll 1: ";   // asks the user to type the score for the last frame
        cin >> scores[18];
        cout << "Enter score for frame 10, roll 2: ";
        cin >> scores[19];
        if (scores[18] + scores[19] == 10 || scores[18] == 10) {
            cout << "Enter score for frame 10, roll 3: ";
            cin >> scores[20];
        }
            
        for (int i = 0; i < 18; ++i) {  //calculates the score for the first 9 frames
            if (i%2 == 0) {
                if (scores[i] == 10 && scores[i+2] == 10) {
                    scores[i] = scores[i] + scores[i+2] + scores[i+4];
                }
                else if (scores[i] == 10) {
                    scores[i] = scores[i] + scores[i+2] + scores[i+3];
                }
                else if (scores[i] + scores[i+1] == 10) {
                    scores[i] = scores[i] + scores[i+1] + scores[i+2];
            }
                
                totalscore.at(j) = totalscore.at(j) + scores[i];
            }
        }
        for (int i = 18; i < 21; ++i) {   // calculates the score for the last frame
            if (scores[18] == 10 && scores [19] == 10) {
                scores[18] = scores[18] + scores[19] + scores[20];
                scores[19] = scores[19] + scores [20];
            }
            else if (scores[18] == 10) {
                scores[18] = scores[18] + scores[19] + scores[20];
            }
            else if (scores[18] + scores [19] == 10) {
                scores[18] = scores[18] + scores[20];
            }
            totalscore.at(j) = totalscore.at(j) + scores[i];
        }
        
        cout << "Enter player's name (done for no more players): ";  // if the user types in done, the loop will break. Otherwise, the loop continues.
        cin >> name;
        
        if (!(name == "done")) {
            player.push_back("");
            totalscore.push_back(0);
            player.at(j+1) = name;
        }
    }
    
    if (player.at(0) == "done") {  // if the user types in done the first time, it prints out this message
        cout << "No players were entered.\n";
    }
  else {
      cout << endl;
        for (int i = 0; i < totalscore.size(); ++i) {   // prints out all the players and with their scores
        cout << player.at(i) << " scored " << totalscore.at(i) << ".\n";
        }
    }
    
    minscore = totalscore.at(0);
    maxscore = totalscore.at(0);
    
    for (int i = 0; i < totalscore.size(); ++i) {  // determines the loser with the lowest score
        if (totalscore.at(i) < minscore) {
            minscore = totalscore.at(i);
            loser = player.at(i);
        }
    }
    for (int i = 0; i < totalscore.size(); ++i) {   // determines the winner with the highest score
        if (totalscore.at(i) > maxscore) {
            maxscore = totalscore.at(i);
            winner = player.at(i);
        }
    }
    
    cout << loser << " did the worst by scoring " << minscore << ".\n";    // prints out the loser with the lowest score
    cout << winner << " won the game by scoring " << maxscore << ".\n";    // prints out the winenr with the highest score
    
    return 0;
}

