// mini lab 3
// COSC130
// This lab takes two integers and adds them without using arithmetic operators
// Casey Mackinnon
// January 25th 2019
// Got help from TA Adnan

#include <cstdlib>
#include <cstdio>

int add (int left, int right);

int main()
{
    
    int left, right;
    
    printf("Enter two numbers to add: ");
    scanf("%d" "%d", &left, &right);
    printf("Result = " "%d\n", add(left, right));
    
    
    return 0;
}

int add(int left, int right) {
    
    int sum = left^right;;
    int carry = left&right;
    int holder = sum;
    
    while (carry != 0) {
        sum = sum ^ (carry << 1);
        carry = holder & (carry << 1);
        holder = sum;
    }
    // This while loop keeps on taking the carry value and the sum value and takes the ^ of sum and carry that is left shifted by 1 each time. The loop will continue until the carry value is 0 from being shifted to the left.
    
    return sum;
}
