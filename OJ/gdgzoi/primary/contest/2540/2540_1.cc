#include <iostream>
#include <climits>

const int MAX_N = 5e5 + 10;
int a[MAX_N];
int g[MAX_N];

int max = -INT_MAX;
int max_len = INT_MAX;
int max_l = INT_MAX;

void flip(int l, int r)
{
    if (l > r)
        std::swap(l, r);

    int res = 0;
    for (int i = l; i <= (l + r) / 2; i++)
    {
        if (i == r + l - i)
            res++;
        else
        {
            if (a[i] == r + l - i && a[r + l - 1] != r + l - 1)
                res++;
            if (a[r + l - 1] == i && a[i] != i)
                res++;
        }
    }

    if (res > max)
    {
        max = res;
        max_len = r - l + 1;
        max_l = l;
    }
    else if (res == max)
    {
        if (max_len > r - l + 1)
        {
            max_len = r - l + 1;
            max_l = l;
        }
        else if (max_len == r - l + 1)
            max_l = std::min(max_l, l);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> a[i];
        g[i] = a[i];
    }

    for (int i = 1; i <= n; i++)
        flip(i, g[i]);

    std::cout << a[max_l] << " " << a[max_l + max_len - 1];
    return 0;
}
