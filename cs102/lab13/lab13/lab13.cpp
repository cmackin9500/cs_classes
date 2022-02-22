//  lab13.cpp
//
//  Name: Casey Mackinnon
//  Due date: November 21st 2018
//
// This lab will asks the user to either push_back a value, resize, print, set a value to a specific element, get the value of a specific element, or quit the program using using pointers and dynamic memories.
// TA Austin helped out me out in this lab

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class doublevector {
    static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
    double *mValues;
    int mNumValues;
public:
    doublevector();
    ~doublevector();
    void resize(int new_size, double initial_value=DOUBLE_DEFAULT_VALUE);
    void push_back(double value);
    double &at(int index);
    const double &at(int index) const;
    unsigned long size() const;
};
void print_all(const doublevector &v)
{
    if (v.size() == 0) {
        cout << "Vector is empty.\n";
    }
    else {
        unsigned long i;
        for (i = 0;i < v.size();i++) {
            cout << "[" << setfill('0') << right << setw(3) << i
            << "] = " << fixed << setprecision(4) << v.at(i)
            << '\n';
        }
    }
}
int main()
{
    doublevector v;
    do {
        string command;
        cout << "Enter a command ('quit' to quit): ";
        if (!(cin >> command) || command == "quit") {
            break;
        }
        else if (command == "push_back") {
            double value;
            cin >> value;
            v.push_back(value);
            cout << "Pushed back "
            << fixed << setprecision(4)
            << value << '\n';
        }
        else if (command == "resize") {
            string line;
            int new_size;
            double initial;
            cin >> new_size;
            getline(cin, line);
            istringstream sin(line);
            
            if (sin >> initial)
                v.resize(new_size, initial);
            else
                v.resize(new_size);
        }
        else if (command == "size") {
            cout << v.size() << '\n';
        }
        else if (command == "print") {
            print_all(v);
        }
        else if (command == "get") {
            int index;
            cin >> index;
            try {
                cout << "Value at " << index << " = "
                << setprecision(4) << fixed
                << v.at(index) << '\n';;
            }
            catch(out_of_range &err) {
                cout << err.what() << '\n';
            }
        }
        else if (command == "set") {
            double d;
            int index;
            cin >> index >> d;
            try {
                v.at(index) = d;
                cout << "SET: " << index << " = "
                << setprecision(4) << fixed
                << v.at(index) << '\n';;
            }
            catch(out_of_range &err) {
                cout << err.what() << '\n';
            }
        }
        else if (command == "clear") {
            v.resize(0);
        }
        else {
            cout << "Invalid command '" << command << "'\n";
        }
    } while(true);
    cout << endl;
    return 0;
}

doublevector::doublevector() {
    
    mNumValues = 0;
    mValues = nullptr;
}
// This assigns 0 to nNumValues and nullptr to mValues each time a doublevector class is created

doublevector::~doublevector() {
    
    if (mValues != nullptr) {
        delete mValues;
    }
}
// This deletes the mValues if it is not equal to nullptr and will be called when an object is destroyed

void doublevector::resize(int new_size, double initial_value) {
    
    if (new_size == 0) {
        if (mValues != nullptr) {
            delete mValues;
            mNumValues = 0;
            mValues = nullptr;
        }
    }
    // if mValues is not equal to nullptr when new_size is equal to 0, it will delete mValues, assigns 0 to mNumValues to 0 and mValues to nullptr
    
    else if (new_size > mNumValues) {
        double *temp = new double[new_size];
        for (int i = 0; i < mNumValues; ++i) {
            temp[i] = mValues[i];
        }
    // if new_size is greater that mNumValues, create a temporary holder and assign the values in mValues into the temp.
        delete mValues;
        // delete the mValues
        for (int i = mNumValues; i < new_size; ++i) {
            temp[i] = initial_value;
        }
     // then, from nNumValues's element to the new_size's element, assign the initial values into the temp
        mValues = new double[new_size];
        // create a new mValues since it was deleted but with a size of new_size this time
        mValues = temp;
        // assign the values in temp into mValues
        mNumValues = new_size;
        // set the new size of mNumValues to new_size
    }
    
    else if (new_size < mNumValues) {
        double *temp = new double[mNumValues];
        for (int i = 0; i < new_size; ++i) {
            temp[i] = mValues[i];
        }
    // if new_size is smaller that mNumValues, create a temporary holder and assign the values in mValues into the temp.
        delete mValues;
        // delete the mValues
        mValues = new double[mNumValues];
         // create a new mValues since it was deleted but with a size of new_size this time
        mValues = temp;
        // assign the values in temp into mValues
        mNumValues = new_size;
        // set the new size of mNumValues to new_size
    }
}

void doublevector::push_back(double value) {
    
    resize(mNumValues + 1, value);
}
// This increases the size of the vector with its new value

double &doublevector::at(int index) {
    
    if (index >= mNumValues) {
        ostringstream sout;
        sout << "Invalid index #" << index;
        throw out_of_range(sout.str());
    }
    return mValues[index];
}
// This takes the index and returns the value stored in it

const double &doublevector::at(int index) const {
    if (index >= mNumValues) {
        ostringstream sout;
        sout << "Invalid index #" << index;
        throw out_of_range(sout.str());
    }
    return mValues[index];
}
// This takes the index and returns the value stored in it

unsigned long doublevector::size() const {
    
    return ((unsigned long) mNumValues);
}
// This takes the mNumValues and returns an unsigned long of it
