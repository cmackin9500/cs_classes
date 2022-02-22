// Lab 4
// COSC130
// This lab will take two decimal numbers and adds it using floating point. This calculator also has the muliply function. You are also able to add and multiply negative numbers as well.
// Casey Mackinnon
// February 11th 2019
// Recieved help from TA Daniel, Tasmia, Jacob, Chris, and Adnan. Also received help from Jared Cox on the normalize function.

#include <cstdio>

using namespace std;

struct Real
{
     //sign bit
     int sign;
     //UNBIASED exponent
     long exponent;
     //Fraction including implied 1 at bit index 23
     unsigned long fraction;
};

Real Decode(int float_value);
int Encode(Real real_value);
Real Normalize(Real value);
Real Multiply(Real left, Real right);
Real Add(Real left, Real right);
// required functions

long addition(long, long);
long twos(long value);
long mul(long left, long right);
//my functions

int main(int argc, char *argv[])
{
     int left, right;
     char op;
     int value;
     Real rLeft, rRight, result;
     if (argc < 4) {
          printf("Usage: %s <left> <op> <right>\n", argv[0]);
          return -1;
     }
     sscanf(argv[1], "%f", (float *)&left);
     sscanf(argv[2], "%c", &op);
     sscanf(argv[3], "%f", (float *)&right);
     rLeft = Decode(left);
     rRight = Decode(right);
     if (op == 'x') {
		 result = Multiply(rLeft, rRight);
     }
     else if (op == '+') {
          result = Add(rLeft, rRight);
     }
     else {
          printf("Unknown operator '%c'\n", op);
          return -2;
     }
     value = Encode(result);
     printf("%.3f %c %.3f = %.3f (0x%08x)\n",
            *((float*)&left),
            op,
            *((float*)&right),
            *((float*)&value),
            value
            );
     return 0;
}

long twos(long value)
{
	return (~value) + 1;
}
// this function takes the twos complement of a number

long addition(long left, long right) {
	long sum = left^right;
	long carry = left&right;
	long holder = sum;

	while(carry != 0) {
		sum = sum ^ (carry << 1);
		carry = holder & (carry << 1);
		holder = sum;
	}
	return sum;
}
// this function adds two numbers using only bitwise operators

long mul(long left,long right)
{
	long product = 0;
	for (long i = 0; i < right; ++i) {
		product = addition(product, left);
	}
	return (product >> 23);
}
// this function multiplies two numbers. It will keep on adding a number to itself using the addition() function however number of times it is being multiplied by.

Real Decode(int float_value)
{
	Real real;

	real.sign = (float_value >> 31) & 1;
// gets the sign bit

	real.exponent = (float_value >> 23) & 0xff;
	real.exponent -= 127;
// gets the exponent bit

	real.fraction = float_value & 0x7fffff;;
	real.fraction |= (1 << 23);
// gets the fraction and adds the implied 1
	
	return real;
}
// This takes the number that the user types in and separate it into sign, fraction and exponent. 

int Encode(Real real_value)
{
	int integer = 0;
	integer |= (real_value.sign << 31);
	integer |= ((real_value.exponent + 127) << 23);
	integer |= (real_value.fraction & ~(1 << 23));
	
	return integer;
}
// This takes the sum or product of two numbers and converts it back to IEEE format

Real Normalize(Real value)
{
	long norm = 0;
	long d = 0;

	for(long i = 63; i >= 0; --i) {
		norm = value.fraction >> i;
	
		if(norm & 1) {
			if(i > 23) {
				d = i - 23;
				value.fraction >>= d;
				value.exponent += d;
				break;
			}
			else if (i == 23) {
				return value;
			}
			else {
				d = 23 - i;
				value.fraction <<= d;
				value.exponent -= d;
				break;
			}
		}
	}
	return value;
}
// This function takes a Real strcuture and changes its fraction and exponent until it is in the form 1._______. This function loops from the 63rd bit to the 0th bit and until we find the left most bit that is 1, we loop through.

Real Multiply(Real left, Real right)
{
	Real product;
	
	if((left.exponent == -127) && (left.fraction == 8388608) && (right.exponent == -127) && (left.fraction == 8388608)) {
		product.sign = 0;
		product.exponent = -127;
		product.fraction = 0;
		return product;
	}
// hardcode for the instance when the user types in 0 x 0

	product.exponent = addition(left.exponent, right.exponent);
	product.fraction = mul(left.fraction, right.fraction);
	product.sign = left.sign ^ right.sign;

	return Normalize(product);
}
// this function takes two numbers and adds takes the product of it. It will determine the exponent, the fraction and the sign. 

Real Add(Real left, Real right)
{
	Real sum;

	if(left.sign !=right.sign) {
		if(left.exponent == right.exponent) {
			if(left.fraction == right.fraction) {
				sum.sign = 0;
				sum.fraction = 0;
				sum.exponent = -127;
				return sum;
			}
		}
	}
// hardcode for when the user adds a number with another number with the same magnitude but negative

	sum.sign = 0;

	if(left.sign == 1 && right.sign == 1) {
		sum.sign = 1;
	}

	else if(left.sign == 0 && right.sign == 1) {
		if(left.exponent < right.exponent) {
			sum.sign = 1;
		}
		else if(left.exponent == right.exponent) {
			if(left.fraction < right.fraction) {
				sum.sign = 1;
			}
		}
	}

	else if(left.sign == 1 && right.sign == 0) {
		if(left.exponent > right.exponent) {
			sum.sign = 1;
		}
		else if(left.exponent == right.exponent) {
			if(left.fraction > right.fraction) {
				sum.sign = 1;
			}
		}
	}
// finds the sign of the sum

	if(left.sign == 1) {
		left.fraction = twos(left.fraction);
	}
	if(right.sign == 1) {
		right.fraction = twos(right.fraction);
	}
// takes the twos complement of the fraction if the sign is negative
	
	if (left.exponent > right.exponent) {
		while(left.exponent != right.exponent) {
			left.fraction <<= 1;
			left.exponent = addition(left.exponent,-1);
			}
		}
	else {
		while(left.exponent != right.exponent) {
			right.fraction <<= 1;
			right.exponent = addition(right.exponent,-1);
		}
	}
// matches the exponent and adds the fraction

	sum.exponent = right.exponent;


	sum.fraction = addition(left.fraction, right.fraction);

	if(sum.sign == 1) {
		sum.fraction = twos(sum.fraction);
	}
// if the sum is negative, take the twos complement of it

	return Normalize(sum);
}
// This function takes two numbers and spits out the sum of it.



