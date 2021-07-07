#include <iostream>

const int MAX_N = 1e6 + 10;
int sum[MAX_N];
int n, t;

bool check(int key)
{
    for (int i = 0; i < n - key; i++)
        if (sum[i + key] - sum[i] >= t)
            return true;
    return false;
}

int main()
{
    std::cin >> n >> t;

    std::cin >> sum[0];
    for (int i = 1; i < n; i++)
    {
        int tmp;
        std::cin >> tmp;
        sum[i] = sum[i - 1] + tmp;
    }

    int l = 0;
    int r = n;

    bool flag = false;
    while (r - l > 1)
    {
        int mid = (l + r) / 2;

        if (check(mid))
        {
            r = mid;
            flag = true;
        }
        else
            l = mid;
    }

    if (not flag)
        std::cout << "Angry";
    else
        std::cout << r;
    return 0;
}