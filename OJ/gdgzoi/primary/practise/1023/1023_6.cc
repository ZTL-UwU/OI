#include <iostream>
#include <iomanip>

const int MAX_N = 2e5 + 10;

int x[MAX_N];
int y[MAX_N];
int s[MAX_N];
int n;

bool check(long long key)
{
    long double time = 0;
    for (int i = 0; i < n; i++)
    {
        time += s[i] * 10000.0 / key;
        if (time < x[i])
            time = x[i];
        else if (time > y[i])
            return false;
    }

    return true;
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> x[i] >> y[i] >> s[i];

    long double l = 0;
    long double r = 1e12;

    while (r - l > 1)
    {
        long double mid = (l + r) / 2;

        if (check(mid))
            r = mid;
        else
            l = mid;
    }

    std::cout << std::fixed << std::setprecision(2) << (long double)r / 10000.0;
    return 0;
}