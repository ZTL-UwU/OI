#include <algorithm>
#include <iostream>

const int MAX_N = 1e5 + 10;

long long int x[MAX_N];
int n, c;

inline bool check(int key)
{
    int cnt = 1;
    int last = 0;
    for (int i = 1; i < n; i++)
    {
        if (x[last] + key <= x[i])
        {
            cnt++;
            last = i;
        }
    }

    return cnt >= c;
}

int main()
{
    std::cin >> n >> c;

    long long int max_diff = -1;
    for (int i = 0; i < n; i++)
        std::cin >> x[i];

    std::sort(x, x + n);

    int l = 0;
    int r = x[n - 1];
    while (l < r - 1)
    {
        int mid = (l + r) / 2;

        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    std::cout << l;
    return 0;
}