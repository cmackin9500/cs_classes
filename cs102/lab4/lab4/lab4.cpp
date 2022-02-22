//
//  main.cpp
//  lab4
//
//  Created by Casey Mackinnon on 12/9/18.
//

#include <iostream>
#include <limits>
#include <string>
using namespace std;

int main() {
    string vehicle;
    double carmiles;
    double truckmiles;
    double cartotalmiles = 0;
    double trucktotalmiles = 0;
    double cargallons;
    double cartotalgallons = 0;
    double truckgallons;
    double trucktotalgallons = 0;
    double carcount = 0;
    double truckcount = 0;
    
    
    cout << "Enter command: ";
     cin >> vehicle;
    
    while (!(vehicle == "car" || vehicle == "truck" || vehicle == "done")) {   // if the user does not type the right command, it will ask them do so until they do
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter command: ";
        cin >> vehicle;
    }
    
 while (vehicle == "car" || vehicle == "truck") {  // as long as the command they type is car or truck, they will be in this loop
    if (vehicle == "car") {
        cout << "Enter car's miles: ";
    while (!(cin >> carmiles) || carmiles < 0) {     // if the user does not type the right command, it will ask them do so until they do
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter car's miles: ";
    }
        cartotalmiles = cartotalmiles + carmiles;
        
        cout << "Enter car's gallons: ";
    while (!(cin >> cargallons) || cargallons < 0) {    // if the user does not type the right command, it will ask them do so until they do
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter car's gallons: ";
    }
        
        cartotalgallons = cartotalgallons + cargallons;
        carcount = carcount + 1;
        
        cout << "Enter command: ";
        
}
    else if (vehicle == "truck") {
        cout << "Enter truck's miles: ";
    while (!(cin >> truckmiles) || truckmiles < 0) {    // if the user does not type the right command, it will ask them do so until they do
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter truck's miles: ";
    }
        trucktotalmiles = trucktotalmiles + truckmiles;
        
        cout << "Enter truck's gallons: ";
        while (!(cin >> truckgallons) || truckgallons < 0) {     // if the user does not type the right command, it will ask them do so until they do
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Enter truck's gallons: ";
        }
        
        trucktotalgallons = trucktotalgallons + truckgallons;
        truckcount = truckcount + 1;
        
        cout << "Enter command: ";

}
     cin >> vehicle;
     while (!(vehicle == "car" || vehicle == "truck" || vehicle == "done")) {    // if the user does not type the right command, it will ask them do so until they do
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         cout << "Enter command: ";
         cin >> vehicle;
     }
 }
    
    if (vehicle == "done") {
    if (carcount != 0) {  //the calculation is only done if the user types in at least one command, miles, and gallons
    cout << "Average car MPG = " << cartotalmiles / cartotalgallons << endl;
    }
    else {
        cout << "Fleet has no cars.\n";
    }
    if (truckcount != 0) {
        cout << "Average truck MPG = " << trucktotalmiles / trucktotalgallons << endl;
    }
    else {
        cout << "Fleet has no trucks.\n";
    }
    return 0;
}
}
    

    
    
    
    

