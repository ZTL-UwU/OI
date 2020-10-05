#include <iostream>

auto abs(auto num)
{
    return num < 0 ? -num : num;
}

auto main() -> int
{
    int a;
    long long b;
    float c;
    double d;

    std::cin >> a >> b >> c >> d;

    std::cout << abs(a) << " " << abs(b) << " " << abs(c) << " " << abs(d);
}