#include <iostream>
#include <cstring>

int main()
{
    int n, k;
    std::cin >> n >> k;

    int num = 1;
    while (num <= n)
        num *= 2;

    num /= 2;
    for (int i = 0; i < k - 1; i++)
    {
        while (num > n)
            num /= 2;
        n -= num;
    }

    num = 1;
    while (num <= n)
        num *= 2;
    std::cout << num - n;
    return 0;
}