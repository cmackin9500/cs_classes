#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

class Magic {
public:
Magic(int a) : a(a) { }
int &getSome() { return a; }
private:
int a;
};
int main()
{
int a = 5;
int* b = &a;
b = &a + 16;
    cout << &b << endl;

}

