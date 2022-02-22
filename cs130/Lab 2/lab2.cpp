// Lab 2
// COSC130
// Three functions. Set function sets the given bit index to 1 whether if it is already 1 or 0. Clear function sets the given bit index to 0 whether if it is already 0 or 1. to_bianry function takes the integer in the vector and shows it in a binary form. Finally, Test function tells if the bit at the given index is a 1 or 0. The user is able to interact with the program and set, clear, test, and print out the integer or bit the way they want.
// Casey Mackinnon
// January 25th 2019
// TA Leroy, TA Chris, TA Daniel, and TA Adnan helped me out

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

class BITSET {
	private:
		vector<int> integers;

	public:
		BITSET();
		int test(unsigned int bit_index) const;
		void set(unsigned int bit_index);
		void clear(unsigned int bit_index);
		string to_binary(unsigned int a) const;
		bool existence(unsigned int bit_index);
};
// class that cointains all the functions and the vector of intgers


int main () {

	BITSET bs;

	char command;
	int bit;
	char rubbish;

	do {
		scanf("%c", &command);
		if (command == 'q') {
			return 0;
		}
		// see what command the user wants. If it is q, the program exits

		scanf("%d", &bit);

		switch(command)
		{
			case 't':
				printf("%d\n", bs.test(bit));
				break;
			case 's':
				bs.set(bit);
				break;
			case 'c':
				bs.clear(bit);
				break;
			case 'p':
				if(bs.existence(bit) == true) { 
					printf("%s\n", bs.to_binary(bit).c_str());	
				}
				else {
					printf("%s", "Set #");
					printf("%d", bit);
					printf("%s\n", " does not exist.");
				}
				break;
		}
		// depending on what the user specified, it does the work. t sees if the given bit is a 0 or a 1. s sets the given bit to 1. c sets the given bit to 0. p prints the integer in a binary form
		scanf("%c", &rubbish);
		// this prevents the program from reading something that is not needed. It prevents the program from exiting
	}
	while (command == 't' || command == 's' || command == 'c' || command == 'p');
	// the program continues as long as they enter a valid command

	return 0;
}

BITSET::BITSET() {

	integers.resize(1);
}
// takes the private vector and makes it into a size of 0 originally

void BITSET::set(unsigned int bit_index) {

	if (integers.size() <= ((bit_index)/32)) {

		integers.resize(((bit_index/32))+1,0);
	}
	// if the size of the vector is smaller than the integer where the specified bit is at, it resizes the vector to correspond to it
	
	integers[bit_index/32] = integers[bit_index/32] | (1 << (bit_index%32));
	// sets the given bit to 1
}


void BITSET::clear(unsigned int bit_index) {

	if (integers.size() > (bit_index/32)) {

		integers[bit_index/32] = integers[bit_index/32] & ~(1 << bit_index%32);
	}
	// sets the given bit to 0 only if it already exist
	
	if (integers[bit_index/32] == 0) {
		
		int k = bit_index/32;
		while (integers[k] == 0) {
			if (integers.size() == 1) {
				break;
			}
			integers.resize((bit_index/32)-1);
			--k;
		}
	// if the bit is cleared and the integer turns into 0, it gets rid of that vector only if there is no other vector that exist beyond it. It keeps on doing it until it hits a vector that contains something.
	}
}

int BITSET::test(unsigned int bit_index) const {
	
	if (integers.size() > (bit_index/32)) {
		int index = 1 & (integers[bit_index/32] >> bit_index%32);
	
		if (index == 1) {
			return 1;
		}
	}

	return 0;
}
// This function outputs if the whether the value in the specified bit index is a 1 or 0

string BITSET::to_binary(unsigned int a) const {

	string sequence = "";
	for (int i = 31; i > -1; --i) {

		int bit = test(a*32+i);
		sequence = sequence + static_cast<char>(('0'+bit));

		if (i==4 || i==8 || i== 12 || i==16 || i==20 || i==24|| i==28) {
	
			sequence = sequence + " ";
			// this adds a space for every 4 bits
		}
	// loops through the bits in the integer and converts into a string
	}
	return sequence;
}

bool BITSET::existence(unsigned int bit_index) {
	bool exist = false;
	if (integers.size() > bit_index) {
		exist = true;
	}
	return exist;
}
	// This function sees if the specified bit exists. If it does, it returns true. Otherwise it returns false

