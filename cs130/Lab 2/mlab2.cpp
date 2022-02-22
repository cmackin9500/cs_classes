// Mini lab 2
// COSC130
// Three functions. Set function sets the given bit index to 1 whether if it is already 1 or 0. Clear function sets the given bit index to 0 whether if it is already 0 or 1. Finally, Test function tells if the bit at the given index is a 1 or 0.
// Casey Mackinnon
// January 18th 2019
// TA Tasmia and TA Adnan helped me out

#include <cstdlib>
#include <cstdio>

int Set(int original_number, int bit_index);
int Clear(int original_number, int bit_index);
int Test(int number, int bit_index);

int main () {

	return 0;
}

int Set(int original_number, int bit_index) {

	int new_number = original_number | (1 << bit_index);
	return new_number;
}
// This function sets the bit index that was specified to 1

int Clear(int original_number, int bit_index) {

	int new_number = original_number & ~(1 << bit_index);
	return new_number;
}
// This function sets the bit index that was specified to 0

int Test(int number, int bit_index) {
	
	int index = 1 & (number >> bit_index);
	return index;
}
// This function outputs if the whether the value in the specified bit index is a 1 or 0
