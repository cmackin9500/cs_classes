//  lab.cpp
//  lab6
//
//  Created by Casey Mackinnon
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

string ticket, report;
// where the output and the input file is stored

const string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
// declaring all the months into an array with a size of 12

const double interstate = 5.2252;
const double highway = 9.4412;
const double residential = 17.1525;
const double none = 12.152;
// declaring all the constant fine multiple

int main() {
    
    cout << "Enter a ticket file: ";
    cin >> ticket;
    ticket = ticket + ".txt";
    // This gets the filename of the input file
    
    cout << "Enter a report file: ";
    cin >> report;
    report = report + ".txt.";
    // This gets the filename of the output file
    
    int startdate, startmonth, startyear;
    cout << "Enter report start date (mm dd yyyy): ";
    cin >> startmonth >> startdate >> startyear;
    // stores all the starting dates
  
    int enddate, endmonth, endyear;
    cout << "Enter report end date   (mm dd yyyy): ";
    cin >> endmonth >> enddate >> endyear;
    // stores all the ending dates
    
    string citation;
    int month, day, year, clockedspeed, speedlimit, speed;
    char road;
    double fine = 0;
    // This is where all the information of the data in the input file is going to be stored
    
    for (int i = 0; i < 4; ++i) {
    // This ensures it goes through the four lines in input file
    
    ifstream in(ticket);
    
    if (!in) {
        cout << "Unable to open " << ticket << ".\n";
        return 1;
    }
    // error checking for if the input file is opened
    
    in >> citation >> month >> day >> year >> clockedspeed >> speedlimit >> road;
    // reads all the data in the input file in a line and stores them

    in.close();
    // closes the input file
    
    if (year < 100) {
        year = 2000 + year;
    }
    // makes sure the year will be four digits if the year in the input file is only 2 digits
    
    if ((year <= endyear && year >= startyear) && (day <= enddate && day >= startdate)) {
    // This makes sure the information will be outputted into a file if it is within the start and end date
    
        speed = clockedspeed - speedlimit;
        if (speed < 0) {
            speed = 0;
        }
        
        switch (road) {
            case 'I':
            case 'i':
                fine = speed * interstate;
                break;
            case 'R':
            case 'r':
                fine = speed * residential;
                break;
            case 'H':
            case 'h':
                fine = speed * highway;
                break;
            default:
                fine = speed * none;
                break;
        }
    // This is where the fines are calculated. The fine multiple is different depending on where you are at
        
    ofstream ofs(report);
    // opens the output file
    
    if (!ofs) {
        cout << "Unable to open " << report << "\n";
        return 1;
    }
    // error checks if the output file is opened

        if (day < 10) {
            ofs << setw(2) << setfill('0') << left << day;
        }
        // if the day is under 10, it puts a 0 in front
        else {
            ofs << day;
        }
        
        ofs << "-" << setw(3) << months[month-1] << "-";
        // Since month is going to be 3 letter, set the width to 3
        ofs << setw(4) << year;
        // since year is going to be 4 numbers, set the width to 4
        ofs << "$" << setw(9) << setprecision(2) << fixed << right << fine;
        // Sets the decimal place to 2 and ensures the fine is printed on the right side
       
        
    ofs.close();
    // closes the output file
    }
    }

return 0;
}
