#include <iostream>

int main()
{
    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        unsigned long long int n, k, s;
        std::cin >> n >> k >> s;

        if (s < (1 + k) * k / 2 || s > (2 * n - k + 1) * k / 2)
            std::cout << "No\n";
        else
            std::cout << "Yes\n";
    }

    return 0;
}
