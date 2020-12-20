#include <iostream>
#include <cmath>

int main()
{
    std::cout << '{';
    for (int i = 0; i <= 18; i++)
        std::cout << std::pow(2, i) << ", ";
    return 0;
}