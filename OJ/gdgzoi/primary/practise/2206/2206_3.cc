// Bash Game

#include <iostream>

int main()
{
    int n, k;
    std::cin >> n >> k;

    std::cout << (n % (k + 1) == 0 ? 2 : 1);
    return 0;
}