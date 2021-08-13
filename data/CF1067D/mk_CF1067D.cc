#include <iostream>
#include "libxl.hpp"

const std::string SAMPLE[2] = {"3 2\n"
                               "3 1000 0.5\n"
                               "1 2 0.48\n"
                               "3 20 0.3",

                               "2 2\n"
                               "1 1000 0.1\n"
                               "2 3 0.2\n"};

int main()
{
    int type;
    std::cin >> type;

    if (type == 0 || type == 1)
    {
        std::cout << SAMPLE[type];
        return 0;
    }

    int n = 1e5;
    long long t = 1e10;
    int max_ab = 1e8;
    int max_decimal = 9;
    if (type == 2) // Plain DP
    {
        n = lxl::mk_rand<int>(10, 1e2);
        t = lxl::mk_rand<int>(1e2, 1e3);
        max_ab = 1e4;
        max_decimal = 5;
    }
    else if (type == 3)
    {
        n = lxl::mk_rand<int>(1e2, 1e3);
        t = lxl::mk_rand<int>(1e4, 1e5);
        max_ab = 1e5;
        max_decimal = 6;
    }
    else if (type == 4)
    {
        n = lxl::mk_rand<int>(1e3, 1e4);
        t = lxl::mk_rand<int>(1e6, 1e7);
        max_ab = 1e6;
        max_decimal = 7;
    }
    else if (type == 5)
    {
        n = lxl::mk_rand<int>(1e4, 1e5);
        t = lxl::mk_rand<unsigned long long>(1e8, 1e10);
        max_ab = 1e7;
        max_decimal = 8;
    }
    else if (type == 6)
    {
        n = 1e5;
        t = 1e10;
        max_ab = 1e8;
        max_decimal = 9;
    }

    std::cout << n << " " << t << "\n";
    for (int i = 0; i < n; i++)
    {
        int a = lxl::mk_rand(1, max_ab);
        int b = lxl::mk_rand(1, max_ab);
        while (b == a)
            b = lxl::mk_rand(1, max_ab);
        if (a > b)
            std::swap(a, b);

        double p = lxl::mk_double(lxl::mk_rand<int>(1, max_decimal));

        std::cout << a << " " << b << " " << p << "\n";
    }
    return 0;
}
