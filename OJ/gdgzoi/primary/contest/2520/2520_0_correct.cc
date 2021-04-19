#include <iostream>

int main()
{
    int a, b;
    std::cin >> a >> b;

    std::cout << (long long int)a * b - a - b;
    return 0;
}