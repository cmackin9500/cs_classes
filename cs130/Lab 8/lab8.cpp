#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <fstream>

using namespace std;

struct PERSON {
     char name[51];
     int age;
     char gender;
};

extern "C"
{
	PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
	int Median(const int array[], int array_size, int *buffer);
}

//int Median(const int array[], int array_size, int *buffer);

int main() 
{
	PERSON names[4] = {{"Bailey Limb", 60, 'M'}, {"Natalie Band", 20, 'F'}, {"Evan Gnomoic", 66, 'F'}, {"Jayden Clothesbrush", 9, 'M'}};

	PERSON *p;
//	const char *name = "Bailey Limb";
//	const char *name = "Evan Gnomoic";
//	const char *name = "Natalie Band";
	const char *name = "Jayden Clothesbrush";
	p = Search(names, 4, name, 9, 'M');

	printf("%s %d %c\n", p->name, p->age, p->gender);

printf("%p %p\n", (names+180), p);

	

	//const int numbers[10] = {4,10,3,1,5,7,8,7,2,9};
	
//const int numbers[14] = {123, 44, -12, 334, 122, -334, 54, 0, -1, 3, 45, -103204, -1, 0};

const int numbers[6] = {20, 40, -3, 41, -234343, 45};

	int array_size = 6;
//	int arr[10];
	int *buff = (int*)malloc(4*array_size);

	cout << "Median value: " << Median(numbers, array_size, buff) << endl;
	for(int i = 0; i < array_size; ++i)
	{
		cout << buff[i] << endl;
	}

	return 0;
/*
	cout << "Hello\n";
	cout << Median(numbers, array_size, buff) << endl;
*/
}

/*int Median(const int array[], int array_size, int *buffer) 
{
	int i = 0;
	int temp;
	while(i < array_size) 
	{
		buffer[i] = array[i];
		++i;
	}
	for(int i = 0; i < array_size-1; ++i) 
	{
		for(int j = 0; j < array_size - i-1; ++j) 
		{
			if(buffer[j] > buffer[j+1]) 
			{
				temp = buffer[j];
				buffer[j] = buffer[j+1];
				buffer[j+1] = temp;
			}
		}
	}
	
	int med;

	if((array_size % 2) == 0)
	{
		med = (buffer[array_size/2] + buffer[(array_size/2)-1])/2;
	}
	else 
	{
		med = (buffer[array_size/2]);
	}

	for(int i = 0; i < array_size; ++i) 
	{
		cout << buffer[i] << " ";
	}
	cout << endl;

	return med;
}*/
