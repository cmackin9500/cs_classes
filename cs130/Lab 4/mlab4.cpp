// Mini lab 4
// COSC130
// This program will taje integer and basically converts it into a float
// Casey Mackinnon
// February 1st 2019
// TA Chris helped me out

#include <cstdlib>
#include <cstdio>

struct Real {
	int sign;
	long exponent;
	unsigned long fraction;
};
//structure that contains the information of the float

Real Decode(int float_value);
int Encode(Real real_value);

int main ()
{
	Real value;

	int someinteger;
	scanf("%f",(float*)(&someinteger));
	value = Decode(someinteger);
	someinteger = Encode(value);
	printf("%f\n",*(float*)(&someinteger));

	return 0;
}
// asks the user to enter a decimal number and prints out a float

Real Decode(int float_value)
{
	Real real;

	real.sign = float_value & 0x80000000;
	real.sign >>= 31;

	real.exponent = float_value & 0x7F800000;
	real.exponent >>= 23;

	real.fraction = float_value & 0x007FFFFF;
	
	return real;
}
// this function will convert a 32-bit floating point into its components

int Encode(Real real_values)
{
	int integer = 0;
	real_values.sign <<= 31;
	real_values.exponent <<= 23;

	integer = real_values.sign | real_values.exponent | real_values.fraction;
	
	return integer;
}
// this function will convert the components of a floating point into its 32-bit value
