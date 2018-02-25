#include <iostream>
#include <fstream>
#include "la/vector.hh"
#include "la/matrix.hh"

void print()
{}

template<class T, class... Tail>
void print(T head, Tail... tail)
{
    std::cout << head << std::endl;
    print(tail...);
}

int main()
{
    Vector v(5);
    std::cout << v << std::endl;   
    return 0;
}
