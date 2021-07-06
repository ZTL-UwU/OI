#include <algorithm>
#include <iostream>

const int MAX_N = 1e6 + 10;
int r[MAX_N];

int main()
{
    int n, l, k;
    std::cin >> n >> l >> k;
    for (int i = 0; i < n; i++)
        std::cin >> r[i];
    std::sort(r, r + n);

    int cnt = 0;
    while (cnt < n)
    {
        if (r[cnt] <= l)
        {
            l += k;
            cnt++;
        }
        else
            break;
    }

    std::cout << cnt;
    return 0;
}