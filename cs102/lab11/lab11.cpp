 m
// Created by Casey Mackinnon
// Due Date: November 7th 2018
//
// Speeding ticket fee calculator
//
// This program will take the start date and end date of a time period. It will read in a data that cointains citation number, month, day, year, clocked speed, speed limit, and type of road.
// If the date is between the start and end date, it will calulate the fine due depending on the type of road and how much the user went pass the speed limit.
// It will then output into a file or it will report to the console using cout.
//


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const double interstate = 5.2252;
const double highway = 9.4412;
const double residential = 17.1525;
const double none = 12.152;
// Global constants for the fine multiplier
const string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
// Array of strings of months for later to convert integer months into string months

struct Date {
	int month;
	int day;
	int year;
};
// structure called Date that contains month, day, and year in int

struct Ticket {
	string citation;
	int clockedspeed;
	int speedlimit;
	char roadtype;
	Date date;
};
// structure called Ticket that contains string for citation number, int for clocked speed and speed limit, char for the road type, and a structure Date called date

class Database {
	private: 
		vector<Ticket> tickets;
	public:
		void add_ticket(const Ticket &ticketinfo);
		vector<Ticket> gen_report(const Date &startdate, const Date &enddate) const;
};
// class with private vector called tickets and public void function called add_ticket and vector

bool Read(Database &d, istream &in);
// This reads in all the ticket information from an input file and returns a boolean value
bool Write(const vector<Ticket> &tickets, ostream &out);
// This reads in the vector of tickets that are within the start date and end date and an ostream, and returns a boolean value
int Encode(const Date &d);
// This reads in the structure consisting the dates and converts them the dates into on integer and returns it

int main(int argc, char *argv[]) {

Database data;
Ticket T;
// naming the Database and Ticket structure 

if (argc != 5) {
	cout << "Usage: ./lab11 <input file> <start: year-month-day> <end: year-month-day> <output or '-'>\n";
	return 1;
}
// This makes sure that if argc is not 5, it will ask the user to enter the command line argument in the right form and returns 1

Date start, end;
// This makes two Date structure one for the start date and one for end date
char rubbish;
stringstream ss;
// stringstream to read in the start and end date

string startdate = argv[2];
ss << startdate;
ss >> start.year >> rubbish >> start.month >> rubbish >> start.day;

string enddate = argv[3];
ss.clear();
ss << enddate;
ss >> end.year >> rubbish >> end.month >> rubbish >> end.day;

ifstream filein;
filein.open(argv[1]);
// opens the file that is the second element in the command line argument

if (filein.fail()) {
	cout << "The file '" << argv[1] << "' cannot be read.\n";
	return 1;
}
// returns 1 if it fails to open the specified input file

if(Read(data, filein) == false) {
	cout << "The file '" << argv[1] << "' cannot be read.\n";
	return 1;
}
// returns 1 if it fails to read in the specified input file or not in the right format

filein.close();
// closes the input file

vector<Ticket> finaltickets = data.gen_report(start, end);
// creates a vector that consists of the tickets that were issued within the start and end date

string outputfile = argv[4];

if (outputfile == "-") {
	Write(finaltickets, cout);
}
// if the final command line argument is a dash, the ticket information will be printed as cout

else { 
// if the final command line argument is a file name, the ticket information will be printed into an output file
	ofstream fileout;
	fileout.open(argv[4]);

	if (fileout.fail()) {
		cout << " The file '" << argv[4] << "' cannot be opened.\n";
			return 1;
	}
// returns 1 if the output file fails to open

	Write(finaltickets, fileout);
	fileout.close();
}
// prints out the ticket information into the output file and closes the output file
	return 0;
}

void Database::add_ticket(const Ticket &ticketinfo) {
	tickets.push_back(ticketinfo);
}
// This function takes in structure called Ticket and adds it into the vector within the class Database

bool Read(Database &d, istream &in) {
	Ticket t;
	bool readin = false;

	while (in >> t.citation >> t.date.month >> t.date.day>> t.date.year >> t.clockedspeed >> t.speedlimit >> t.roadtype) {
			if (t.date.year < 100) {
				t.date.year = 2000 + t.date.year;
			}
			d.add_ticket(t);
			readin = true;
	}
// Reads in ticket infotmation from the input file and stores them into a vector using add_ticket function. Returns a boolean value; true if succesfully read
	return readin;
}

bool Write(const vector<Ticket> &tickets, ostream &out) {

	for (int i = 0; i < tickets.size(); ++i) {
		
		string finalmonth = months [tickets.at(i).date.month - 1];
		// converts the month in integer form in letters

		double fine;
		switch (tickets.at(i).roadtype) {
			case 'i':
			case 'I':
				fine = (tickets.at(i).clockedspeed - tickets.at(i).speedlimit) * interstate;
				break;
			case 'h':
			case 'H':
				fine = (tickets.at(i).clockedspeed - tickets.at(i).speedlimit) * highway;
				break;
			case 'r':
			case 'R':
				fine = (tickets.at(i).clockedspeed - tickets.at(i).speedlimit) * residential;
				break;
			default:
				fine = (tickets.at(i).clockedspeed - tickets.at(i).speedlimit) * none;
				break;
		}
		if (fine < 0) {
			fine = 0;
		}
		// This switch statement takes in what the road type is and calculates the fine depending on it. Fine is $0.00 if the clocked speed is less than the speed limit

		out << setw(2) << setfill('0') << tickets.at(i).date.day << "-" << finalmonth << "-" << tickets.at(i).date.year << " " << setw(10) << setfill(' ') << left << tickets.at(i).citation << " $"
			<< setw(9) << right << setprecision(2) << fixed << fine << endl;
	}
	// This prints out the ticket information in the order of day, month, year, citation number, and the fine that is due

	return true;
}

int Encode(const Date &d) {
	int num = (d.year*10000)+(d.month*100)+(d.day*1);
	return num;
}
// This function takes in the month, day, and year in the Date structure and returns the date in an integer form


vector<Ticket> Database::gen_report(const Date &startdate, const Date &enddate) const{

	vector<Ticket> validtickets;

	for (int k = 0; k < tickets.size(); ++k) {
		if ((Encode(tickets.at(k).date) > Encode(startdate) && Encode(tickets.at(k).date) < Encode(enddate)) || Encode(tickets.at(k).date) == Encode(startdate) || Encode(tickets.at(k).date) == Encode(enddate)) {
			validtickets.push_back(tickets.at(k));
		}
		// This takes in the vector that all the ticket infotmation are stores and returns the vector which consists of ticket information that are between the start and end date
	}
		return validtickets;
}

