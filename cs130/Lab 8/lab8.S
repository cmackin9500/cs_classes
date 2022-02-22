D// Lab 8
// COSC130
// This program has two functions. The first function is called Search which will go through an array that has strcutures of people's information. If the function finds a match, it will return a pointer to the beginning of the structure that contains the match's information. If there is no match, it will return nullptr. The second program is called Meidian which will basically take an array of intergers, sort them, and returns the median.
// Casey Mackinnon
// March 8th 2019
// Recieved help from TA Chris, TA Leroy, TA Adnan, TA Jacob, and TA Daniel

//	N.O.S. Table
//	---------------------------------
//	| name		    | offset | size	|
//	=================================
//	| char name[51] |   0    |	51	|
//	---------------------------------
//	| int age		|   52   |	4	|
//	---------------------------------
//	| char gender   |   56   |  1   |
//	---------------------------------
//	  Total size				60

.section .text
.global Search
//	PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
Search:
1:
	li		t0, 0				// int i = 0

name:
	li		t1, 60				// byte = 60
	mv		t2, a0				// t2 = people[]
	mv		t3, a2				// t3 = *name
	mul		t1, t1, t0			// byte *= i
	add		t2, t2, t1			// t2 = people[] + byte

//	if(i == num_people) { jump to none }
	beq		a1, t0, none
//	t4 == people[]
//	t5 == name[]
byte:
	lb		t4, 0(t2)			// t4 = *t2		
	lb		t5, 0(t3)			// t5 = *t3		
	bne		t4, t5, back		// if(people.at(i) != name.at(i)) { jump to back }
	addi	t2, t2, 1			// t2 = t2 + 1
	addi	t3, t3, 1			// t3 = t3 + 1

//	if(people.at(i) == '\0' && name.at(i) == '\0') { jump to age }
	mv		t6, zero
//	li		t6, 0
	bne		t4, t6, byte
	bne		t5, t6, byte
	j		age

age:
//	t2 == people[]
//	t3 == people[i].age
//	a3 == age
	mv		t2, a0
	add		t2, t2, t1			// t2 = people[] + 60*i
	addi	t2, t2, 52
	lw		t3, 0(t2)			// t3 = age
	bne		t3, a3, back		// if(people[i].age != age)
	addi	t2, t2, 4			// a0 = a0 + 4 

gender:

//	t2 == people[]
//	t3 == people[i].gender
//	a4 == gender
	lb		t3, 0(t2)			// t3 = gender
	bne		t3, a4, back		// if(people[i].gender != gender)
	j		found

back:
	addi	t0, t0, 1			// ++i
	j		name

//	This part will execute if a match is not found. It will return nullptr.
none:
	li		a0, 0				// a0 = nullptr
	j		end	

//	This part will execute if a match is found. It will return the pointer.
found:
	li		t1, 60
	mul		t0, t0, t1			// t0 = i*60
	add		a0, a0, t0			// a0 = a0 + t0
end:	
	ret
	
.global Median
//	int Median(const int array[], int array_size, int *buffer);
Median:
	li		t0, 0				// int i = 0
	li		t1, -4				// int byte = 60;
	mv		t2, a0				// t2 = array[]

// for loop to assign all the int in array into buffer
transfer:
	bge		t0, a1, backtrack
	lw		t3, 0(t2)			// t3 = *(array + 4i)
	sw		t3, 0(a2)			// *(buffer + 4i) = t3
	addi	t2, t2, 4			// array[] = array[] + 4
	addi	a2, a2, 4			// *buffer = *buffer + 4
	addi	t0, t0, 1			// ++i		
	j		transfer

backtrack:
	mul		t1, t1, a1			// t1 = -4*array_size	
	add		a2, a2, t1			// buffer = buffer - t1
	mv		t3, a1				// t3 = array_size
	addi	t3, t3, -1			// --array_size
	li		t0, 0				// int i = 0
	li		t1, 0				// int j = 0

sort:
//	for(int i = 0; i < array_size - 1; ++i)
	bge		t0, t3, calc
	mv		t2, t3				// t2 = array_size - 1
	sub		t2, t2, t0			// t2 = array_size - 1 - i
	li		t1, 0

sortin:
//	for(int j = 0; j < array_size - i -	1; ++j)
	bge		t1, t2, iterate_i
	mv		t4, a2				// t4 = a2
	li		t5, 4				// t5 = 4
	mul		t5, t5, t1
	add		t4, t4, t5
	lw		t6, 0(t4)			// t6 = buffer[j]
	addi	t4, t4, 4			
	lw		t5, 0(t4)			// t5 = buffer[j+1]	

//	if(buffer[j] > buffer[j+1]) { switch }
	ble		t6, t5, iterate_j
	mv		t4, t6
	mv		t6, t5				// t6 = pointer to buffer[j+1]
	mv		t5, t4				// t5 = pointer to buffer[j]
	li		t4, 4
	mul		t4, t4, t1			// t4 = 4*j
	add		a2, a2, t4
	sw		t6, 0(a2)			// buffer[j] = buffer[j+1]
	addi	a2, a2, 4			// buffer[j+1] = buffer[j]
	sw		t5, 0(a2)

//	bring a2 to its original position
	sub		a2, a2, t4			// a2 = a2 - 4*j
	addi	a2, a2, -4			// a2 = a2 - 4
	
iterate_j:
	addi	t1, t1, 1			// ++j
	j		sortin

iterate_i:
	addi	t0, t0, 1			// ++i
	j		sort
	
calc:
//	check if array_size is even odd first
	mv		t0, a1				// t0 = array_size
	li		t1, 2				// t1 = 2
	rem		t2, t0, t1			// t0 = array_size % 2
	li		t3, 0
//	This part applies for both even and odd
	div		t4, t0, t1
	li		t5, 4
	mul		t5, t5, t4
	mv		t0, a2
	add		t0, t0, t5
	lw		t6, 0(t0)			// t6 = buffer[array_size/2]

//	if(array_size % 2 == 0) { jump to even}
	beq		t2, t3, even

//	median calculation for odd
	mv		a0, t6
	j		return

//	median calculation for odd
even:
	addi	t0, t0, -4			// buffer[array_size/2 - 1]
	lw		t5, 0(t0)			// t5 = buffer[array_size/2 - 1]
	add		t5, t5, t6
	div		a0, t5, t1			// median = (buffer[array_size/2] + buffer[(array_size/2)-1])/2

return:
	ret
