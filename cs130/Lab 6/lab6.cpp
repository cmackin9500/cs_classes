// Lab 6
// COSC130
// This program will read an encypted file and displays the decrypted data. The user will type in the file that they want to be decrypted in the second command line argument, the data key in the third command line argument, and the index key in the fourth command line argument. If the user makes any error using the program, it will exit automatically
// Casey Mackinnon
// Due Date: February 22th 2019
// Recieved help from TA Adnan and Jacob.

#include <cstdio>
#include <cstdlib>

struct S 
{
	char d;
	int n;
};
// structure where the character and the order will be strored

int main (int argc, char *argv[]) 
{
	if(argc != 4) {
		printf("Usage: ./lab6 <file> <dkey> <nkey>\n");
		return -1;
	}
// if the number of command line argument is not 4, the program will tell the user the correct way of using and returns -1.

	char dkey;
	sscanf(argv[2], "%c", &dkey);
// stores the third command line argument as dkey
	int nkey;
	sscanf(argv[3], "%d", &nkey);
// stores the fourth command line argument as nkey

	const char *file = argv[1];
	FILE *f = fopen(file, "rb");
// opens the file that the user specified in the the second command line argument

	if(f == nullptr) {
		perror(file);
		return -1;
	}
// if the file cannot be opened, it prints out an error message and returns -1

	fseek(f, 0, SEEK_END);
	int count = ftell(f)/8;
// find the number of bytes in the file. Since ftell will tell the number bits, divide by 8 to get the number of bytes

	fseek(f, 0, SEEK_SET);
// sets it to the first bit
	
	S* data = (S*) malloc(count*sizeof(S));
// creates a dynamically allocated array that will store the sturcture	
	
	char buffchar;
	int buffint;

	for(int i = 0; i < count; ++i) 
	{
		fread(&buffchar, sizeof(char), 1, f);
		data[i].d = buffchar;
// each encrypted data byte is stored into the array

		fseek(f, 3, SEEK_CUR);
// skips through 3 to get to the encrypted index
		
		fread(&buffint, sizeof(char), 4, f);
		data[i].n = buffint;
// each encrypted index is stored into the array
	}

	fclose(f);
// closes the file 

	char *all_data;
	all_data = (char*)malloc(sizeof(char)*count);	
// creates a dynamically allocated array where the decrypted data will be stroed

	
	for(int i = 0; i < count; ++i) {
		if((data[i].n ^ nkey) >= count || (data[i].n ^ nkey) < 0) {
			printf("Error decoding chunk %d, decoded index %d, but max chunks is %d.\n", i, nkey , count);
			return -1;
// if the decode index is invalid, it tells the user and returns -1
		}
			all_data[data[i].n ^ nkey] = data[i].d ^ dkey;
	}
// stores the decrypted data into the array in the correct order by doing xor for the encrypted data and the dkey and the nkey

	for(int i = 0; i < count; ++i) {
		printf("%c",all_data[i]);
	}
// prints out the decrypted data in order

	free(data);
	free(all_data);
// frees the dynamically allocated arrays

	return 0;
}
