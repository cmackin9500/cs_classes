// Lab 5
// COSC130
// This lab works as a single player version of the Multy Player Dungeon that was popular in the 90s and the 00s. The user will press 'l' to see what is in the room and s,e,w, or n to move directions. The goal is to get to the end.
// Casey Mackinnon
// Due Date: February 15th 2019
// Recieved help from TA Daniel, Leroy, Jacob, and Chris.

#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

struct roominfo 
{
	string desc;
	int roomnum;
	int w;
	int s;
	int n;
	int e;
};
// structure of room information

int main (int argc, char *argv[]) 
{
	int count = 0;
	char *buf = nullptr;

	if (argc != 2) {
		printf("Usage: %s <file>\n", argv[0]);
		return -1;
	}
    // if the number of command argument is not 2, it will print out an error message and returns -1.

	FILE *room = fopen(argv[1], "rb");
    // opens the file the user specified

	buf = (char*)malloc(256* sizeof(char));
	// dynamically allocates memory

	if (room == nullptr) {
		perror(argv[1]);
		return -1;
	}
    // if the file the user specified cannot be opened, it will print out an error message and returns -1.

	while(fgets(buf, 256, room)) {
		if(buf[0] == '~') {   // gets the first character of the string
			++count;
		}
	}
	count /= 3;
    // this will count the number of rooms that the game has
    
	roominfo* arr = (roominfo*) malloc(count*sizeof(roominfo));
    // this creates an dynamically allocated array that stores all the room information in an structure

	fseek(room, 0, SEEK_SET);

	for(int i = 0; i < count; i++) {  // loops the number of rooms
		int num;

		fgets(buf, 256, room);  // gets the room number
		sscanf(buf,"Room #%d", &num);
		arr[num].roomnum = num;
		fgets(buf, 256, room);   // gets the ~
	
		do {
			fgets(buf, 256, room); // gets the description
			if(buf[0] != '~') {
				arr[num].desc += buf;
			}
		}
		while(buf[0] != '~');
		
		arr[num].n = -1;
		arr[num].e = -1;
		arr[num].s = -1;
		arr[num].w = -1;
// assigns each room with -1 so that if in the room, the direction does not exist, it will remain -1
        
		do {
			fgets(buf, 256, room);
			
			char v;
			int r;
			sscanf(buf, "%c %d", &v, &r);
			switch(v) {
				case 'n':
					arr[num].n = r;
					break;
				case 'e':
					arr[num].e = r;
					break;
				case 's':
					arr[num].s = r;
					break;
				case 'w':
					arr[num].w = r;
					break;
				default:
					break;
			}
            // this switch statement figures out which direction the room number that will lead to will be stored
		}
		while(buf[0] != '~');
	}
    // gets the room directions until it hits '~'

	fclose(room);
	free(buf);
    // closes the room file and frees the buffer

	int rn = 0;
	char d;

	while(scanf(" %c", &d) != EOF)  // this makes sure if the user types in control+d, the program will end
	{
		if(d == 'q') { //this makes sure if the user types in 'q' or control+d, the program will end
			break;
		}

		if(d == 'l') {
			printf("Room #%d\n", rn);
	
			printf("%s\n", arr[rn].desc.c_str());

			printf("Exits: ");
			if(arr[rn].n != -1) {
				printf("n ");;
			}
			if(arr[rn].e != -1) {
				printf("e ");
			}
			if(arr[rn].s != -1) {
				printf("s ");
			}
			if(arr[rn].w != -1) {
				printf("w ");
			}
			printf("\n");
		}
        // if the user types in l, it will print out the description of the room and the directions the user can go to
	
		if(d == 'n') {
			if(arr[rn].n != -1) {
				rn = arr[rn].n;
				printf("You moved NORTH.\n");
			}
			else {
				printf("You can't go NORTH!\n");
			}
		}
        // if user types in 'n', the user will go north. If you cannot go north, it will print out a message saying you cannot do that.
		
		if(d == 'e') {
			if(arr[rn].e != -1) {
				rn = arr[rn].e;
				printf("You moved EAST.\n");
			}
			else {
				printf("You can't go EAST.\n");
			}
		}
        // if user types in 'e', the user will go east. If you cannot go east, it will print out a message saying you cannot do that.

		if(d == 's') {
			if(arr[rn].s != -1) {
				rn = arr[rn].s;
				printf("You moved SOUTH.\n");
			}
			else {
				printf("You can't go SOUTH\n");
			}
		}
        // if user types in 's', the user will go south. If you cannot go south, it will print out a message saying you cannot do that.

		if(d == 'w') {
			if(arr[rn].w != -1) {
				rn = arr[rn].w;
				printf("You moved WEST.\n");
			}
			else {
				printf("You can't go WEST!\n");
			}
		}
        // if user types in 'w', the user will go west. If you cannot go west, it will print out a message saying you cannot do that.
	}
	free(arr);
    // this frees the dynamically allocated array
    
	return 0;
}
