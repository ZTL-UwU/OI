#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        unsigned n;
        std::cin >> n;
        std::cout << n + 1 << "\n";
    }
    return 0;
}