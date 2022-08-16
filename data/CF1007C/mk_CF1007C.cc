#include "../libxl.hpp"
#include <iostream>

int main()
{
    int type;
    std::cin >> type;

    unsigned long long n = 1e18, a, b;

    if (type == 0)
        n = lxl::mk_rand<unsigned long long>(5, 10);
    else if (type == 1)
        n = lxl::mk_rand<unsigned long long>(1e4, 1e6);
    else if (type == 2)
        n = lxl::mk_rand<unsigned long long>(1e6, 1e9);
    else if (type == 3)
        n = lxl::mk_rand<unsigned long long>(1e12, 1e18);
    else if (type == 4)
        n = 1e18;

    a = lxl::mk_rand<unsigned long long>(1, n);
    b = lxl::mk_rand<unsigned long long>(1, n);

    std::cout << n << "\n" << a << " " << b;
    return 0;
}