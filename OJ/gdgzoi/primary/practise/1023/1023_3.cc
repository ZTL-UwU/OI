#include <iostream>

const int MAX_N = 3e4 + 10;

int length[MAX_N];
int n;

bool check(int key)
{
    for (int i = 0; i < n; i++)
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> length[i];

    long long l = 0;
    long long r = 1e16;

    while (r - l > 1)
    {
        long long mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }
    return 0;
}