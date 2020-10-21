#include <iostream>
#include <stdio.h>
int main()
{
    int r, b, c, d, e;
    std::cin >> r >> b >> c >> d >> e;
    if (c + d >= 2 * e)
    {
        std::cout << r * c + b * d;
    }
    else
    {
        if (r <= b)
        {
            std::cout << r * 2 * e + (b - r) * d;
        }
        else
        {
            std::cout << b * 2 * e + (r - b) * c;
        }
    }
    return 0;
}