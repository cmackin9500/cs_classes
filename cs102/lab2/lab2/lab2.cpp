//
//  lab2.cpp
//  lab2
//
//  Created by Casey Mackinnon on 9/5/18.
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string firstname, middlename;
    cout << "Enter your first and middle names: ";
    cin >> firstname >> middlename;
    
    int age;
    cout << "Enter your age: ";
    cin >> age;
    
    int streetnumber;
    string streetname, streettype;
    cout << "Enter your street number, name, and type: ";
    cin >> streetnumber >> streetname >> streettype;
    
    cout << endl;
    
    cout << "Your movie star name is " << streetname << " " << middlename << "." << endl;        // creating the new movie star name
    cout << "You will play a " << (streetnumber % age) * 3 << " year old." << endl;        // calculating and printing the new age
    cout << "Your address is " << (age * 700) / streetnumber << " " << firstname << " " << streettype << ".";      // calculating new street number and printing out the new address
    cout << endl;
    
    return 0;
    
}


