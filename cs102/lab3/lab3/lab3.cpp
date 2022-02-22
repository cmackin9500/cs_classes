//
//  lab3.cpp
//  lab3
//
//  Created by Casey Mackinnon on 5/9/18.
//
//

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    
    double left, right;
    char operand;
    
    cout << "Enter left operand: ";
   
    if (!(cin >> left))    // this finds out if the user typed in a real number. If it's not a real number, it will exit the program
    {
        cout << "invalid left operand" << endl;
        return 1;
    }
    
    else {  //The rest of the program will only execute if the above statement is false
    cout << "Enter operation: ";
    cin >> operand;
    if (operand == '|' || operand == 'b' || operand == 'B')  //right operand will not be asked if we are looking for the absolute value
    {
        cout << "Result = " << abs(left) << endl;
        return 0;
    }
  
    switch (operand) {
        case '+':
        case 'a':
        case 'A':
            cout << "Enter right operand: ";
            if (!(cin >> right))   // this finds out if the user typed in a real number. If it's not a real number, it will exit the program
            {
                cout << "invalid right operand" << endl;
                return 1;
            }
            cout << "Result = " << left+right << endl;
            break;
        
        case '-':
        case 's':
        case 'S':
            cout << "Enter right operand: ";
            if (!(cin >> right))   // this finds out if the user typed in a real number. If it's not a real number, it will exit the program
            {
                cout << "invalid right operand" << endl;
                return 1;
            }
            cout << "Result = " << left-right << endl;
            break;
       
        case '*':
        case 'm':
        case 'M':
        case 'x':
            cout << "Enter right operand: ";
            if (!(cin >> right))   // this finds out if the user typed in a real number. If it's not a real number, it will exit the program
            {
                cout << "invalid right operand" << endl;
                return 1;
            }
            cout << "Result = " << left*right << endl;
            break;
       
        case '/':
        case 'd':
        case 'D':
            cout << "Enter right operand: ";
            if (!(cin >> right))   // this finds out if the user typed in a real number. If it's not a real number, it will exit the program
            {
                cout << "invalid right operand" << endl;
                return 1;
            }
            cout << "Result = " << left/right << endl;
            break;
        
        default:
            cout << "Unknown Operator" << endl;
            return 1;
    }
    }
  
    return 0;
    
}
