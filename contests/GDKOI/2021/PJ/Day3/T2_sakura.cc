#include <iostream>

int main()
{
    long long n, k;
    std::cin >> n >> k;

    long long rk_sum = 0;
    for (int i = 1; i <= k; i++)
    {
        int rk;
        std::cin >> rk;
        rk_sum += rk - 1;

        if (rk_sum <= (n - 1) * (i - 1))
            std::cout << "1";
        else
            std::cout << rk_sum - (n - 1) * (i - 1) + 1;
        std::cout << " ";
        if (rk_sum >= n - 1)
            std::cout << n;
        else
            std::cout << rk_sum + 1;
        std::cout << "\n";
    }
    return 0;
}
