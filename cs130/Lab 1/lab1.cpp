// lab 1
// COSC130
// This lab requires to complete 4 functions which converts a char into int, int to char, int to string, and string to int. The user will type in a calculation they want and will shoot out the answer to that.
// Casey Mackinnon
// January 18th 2019
// Worked with TA Tasmia and got a little bit of help from Karan Patel


#include <iostream>
#include <string>
using namespace std;

//Prototypes for the functions that you will write
int  CharToInt(char v);
char IntToChar(int v);
int StringToInt(string val);
string IntToString(int val);

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());

        return 0;
}

int CharToInt(char v) {

	int integer = v - '0';
	return integer;
}
// This function takes the a number that is as a char and converts it into a integer by subtracting '0' which is 48 in decimal

char IntToChar(int v) {

	char character = v + '0';
	return character;
}
// This function takes the integer and converts it into a character as a number by adding '0' which is 48 in decimal.


int StringToInt(string val) {

	bool negative = false;
	if (val.at(0) == '-') {
		negative = true;
	}
	// This sees if the number in the form of a string is negative

	int number = 0;

	if (negative == false) { 
		for (unsigned int i = 0; i < val.length(); ++i) {
			number = number*10 + CharToInt(val[i]);
		}
	}
	// If the number in the form of a string is positive, it takes everything and converts them into a integer

	else {
		for (unsigned int i = 1; i < val.length(); ++i) {
			number = number*10 + CharToInt(val[i]);
		}
	}
	// If the number in the form of a string is negative, it ignores '-' and takes the rest of the numbers and converts them into a integer

	if (negative == true) {
		number = number - 2*number;
	}
	// If the string was negative, it takes the number (which is positive at this point) and makes the integer negative

	return number;
}
// This function as a whole takes the number in the form of a string and converts them into an integer


string IntToString(int val) {

	bool negative = false;
	if (val < 0) {
		negative = true;
		val = val - 2*val;
	}
	// This takes the integer and if it is negative, it sets it postive

	string numbers = "";

	while(val >= 1 || val <= -1) {

	numbers = IntToChar(val%10) + numbers;
	val /= 10;
	}
	// This will convert each integer into string one by one

	if (negative == true) {
		numbers = '-' + numbers;
	}
	// If the integer was originally negative, it adds the negative sign in front of the number in a form of string

	return numbers;
}
// This function as a whole takes the integer and converts it in a form of a string


