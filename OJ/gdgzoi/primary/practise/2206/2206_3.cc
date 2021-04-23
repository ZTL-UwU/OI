// Nim Game

#include <iostream>

int main()
{
    int n;
    std::cin >> n;

    int sum = 0;
    for (int _i = 0; _i < n; _i++)
    {
        int a;
        std::cin >> a;

        sum = sum ^ a;
    }

    std::cout << (sum != 0 ? "win" : "lose");
    return 0;
}
