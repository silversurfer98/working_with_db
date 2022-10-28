#include<iostream>
#include<sqlite.h>

template <typename t>
void print(const char* a, t x)
{
	std::cout << "\n the " << a << " : " << x << "\n\n";
}

int main()
{
    std::cout<<"testing build";
    //sqlite();
    test();
    return 0;
}