// Lab 3
// COSC130
// This program will calculate the multiple, sum, and differences of two numbers using only bitwise operator. The second and forth argument in the command line will be the two numbers that will be calculated together. The third command line will be the operation of the calculation.
// Casey Mackinnon
// February 1st 2019
// TA Leroy helped me out

#include <cstdlib>
#include <cstdio>

int sign(int value);
int twos(int value);
int add(int left, int right);
int sub(int left, int right);
int mul(int left, int right);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf("Usage: %s <num> <op> <num>\n", argv[0]);
		return -1;
	}

	int left;
	int right;
	char op;
	int result;

	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);

	switch (op)
	{
		case '+':
			result = add(left, right);
			break;
		case '-':
			result = sub(left, right);
			break;
		case 'x':
			result = mul(left, right);
			break;
		default:
			printf("Unknown operation '%c'\n", op);
			return -2;
	}

	printf("%d %c %d = %d\n", left, op, right, result);

	return 0;
}

int sign(int value) 
{
	return 1 & (value >> 31);
}
// This function takes the last bit of the integer and returns the value of it. If it is 1, it is negative and if it is 0, it is positive

int twos(int value)
{
	return ~value + 1;
}
// This function takes an integer and returns the two's complement of that value

int add(int left, int right) 
{
	int sum = left^right;
	int carry = left&right;
	int holder = sum;

	while(carry != 0) {
		sum = sum ^ (carry << 1);
		carry = holder & (carry << 1);
		holder = sum;
	}
	return sum;
}
// This function adds two integers together using only bitwise operations. It takes the "sum" of the two integers without the carry, the carry is left shifted by one. This will repeat until there is no more carry anymore.

int sub(int left, int right)
{
	right = twos(right);
	return add(left, right);
}
// This function subtracts two integers together. It uses the add function but the only difference is that it takes the two's complement of the right side integer so that the two numbers can be calculated using addition instead of subtraction.

int mul(int left, int right)
{
	int product = 0;
	bool negative = false;

	if (sign(left) ^ sign(right)) {
		negative = true;
	}
	if (sign(left)) {
		left = twos(left);
	}
	if (sign(right)) {
		right = twos(right);
	}

	for (int i = 0; i < right; ++i) {
		product = add(product, left);
	}

	if(negative == true) {
		product = twos(product);
	}
	return product;
}
// This function multiplies two integers togther. First it sees if the left and right integers are positive or negative. If negative, it will take the two's complement of the value. Once both integers are positive, it will add the left integers with itself right number of times. At the end, if the value is supposed to be negative, it will convert it into negative using the twos function.

