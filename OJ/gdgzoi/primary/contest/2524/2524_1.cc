#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>

int main()
{
    std::srand(std::time(0));

    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++)
        std::cout << (std::rand() % 2 == 0 ? "Yes" : "No") << "\n";
    return 0;
}
