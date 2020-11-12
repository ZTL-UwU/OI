#include <iostream>
#include <cstdio>
#include <vector>

long long power(int a, int b)
{
    long long ans = 1;
    for (int i = 0; i < b; i++)
        ans *= a;

    return ans;
}

int main()
{
    long long n, k;
    std::cin >> n >> k;

    for (int i = n; i >= 1; i--)
    {
        long long mid = (power(2, i) - 1) / 2;

        if (k <= mid)
            std::cout << '0';
        else
        {
            std::cout << '1';
            k = power(2, i) - 1 - k;
        }
    }
    return 0;
}