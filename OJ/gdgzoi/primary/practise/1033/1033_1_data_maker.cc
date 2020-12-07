#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>
#include <cmath>

inline int get_rand_range(int l, int r)
{
    long long int rand_tmp = (long long int)std::pow(std::rand(), 2) % r;

    while (rand_tmp < l)
        rand_tmp = (long long int)std::pow(std::rand(), 2) % r;

    return rand_tmp;
}

int main()
{
    std::srand(std::time(0));
    std::freopen("test.in", "w", stdout);

    for (int t = 0; t < get_rand_range(1, 1000) - 1; t++)
    {
        int n = get_rand_range(10, 5000);

        std::cout << "  \n" << n << "  \n\n\n ";

        for (int i = 0; i < n; i++)
        {
            std::cout << (std::rand() % 2 == 0 ? " c " : "  q ");

            std::cout << get_rand_range(1, n) << "     " << get_rand_range(1, n) << " \n \n";
        }
    }

    int n = get_rand_range(10, 5000);

    std::cout << "  " << n << "  \n  ";

    for (int i = 0; i < n - 1; i++)
    {
        std::cout << (std::rand() % 2 == 0 ? " c " : "  q ");

        std::cout << get_rand_range(1, n) << "     " << get_rand_range(1, n) << " \n\n \n";
    }
    std::cout << (std::rand() % 2 == 0 ? " c " : "  q ");

    std::cout << get_rand_range(1, n) << "     " << get_rand_range(1, n);

    return 0;
}