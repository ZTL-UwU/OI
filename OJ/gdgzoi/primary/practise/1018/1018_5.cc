#include <algorithm>
#include <iostream>
const int MAXN = 1e3 + 10;
int x[MAXN];
int main()
{
    int n, r;
    std::cin >> n >> r;
    for (int i = 0; i < n; i++)
        std::cin >> x[i];
    std::sort(x, x + n);

    int i = 0;
    int ans = 0;
    while (i < n)
    {
        int start1 = x[i++];
        while (i < n && start1 + r >= x[i])
            i++;

        int start2 = x[i - 1];
        while (i < n && start2 + r >= x[i])
            i++;

        ans++;
    }

    std::cout << ans;
    return 0;
}