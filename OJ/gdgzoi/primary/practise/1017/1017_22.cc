#include <algorithm>
#include <iostream>

const int MAX_N = 1e6 + 10;
int a[MAX_N];

int main()
{
    int w, n;
    std::cin >> w >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a, a + n);

    int i = 0;
    int j = n - 1;

    int ans = 0;
    while (i < j)
    {
        if (a[i] + a[j] <= w)
        {
            ans++;
            i++;
            j--;
        }
        else
        {
            j--;
            ans++;
        }
    }

    if (i == j)
        std::cout << ans + 1;
    else
        std::cout << ans;
    return 0;
}