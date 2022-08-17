#include <iostream>

unsigned long long fib[10000];

int main()
{
    fib[1] = 1;
    fib[2] = 1;

    for (int i = 3; i < 100; i++)
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        std::cout << fib[i] << " ";
    }
    return 0;
}