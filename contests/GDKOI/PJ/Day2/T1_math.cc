#include <iostream>
#include <vector>

#include <dbg.h>

const int MAX_N = 10;

std::vector<int> e[MAX_N + 10];
int a[MAX_N + 10];
int p[MAX_N + 10];

int main()
{
    for (int i = 1; i <= MAX_N; i++)
        std::cin >> a[i];

    p[2] = a[2] + 2 * a[4] + a[6] + 3 * a[8] + a[10];
    p[3] = a[3] + a[6] + 2 * a[9];
    p[5] = a[5] + a[10];
    p[7] = a[7];

    e[2] = {6, 2, 4, 8};
    e[3] = {1, 3, 9, 7};
    e[5] = {5};
    e[7] = {1, 7, 9, 3};

    int min25 = std::min(p[2], p[5]);
    p[2] -= min25;
    p[5] -= min25;

    int ans = (p[2] > 0 ? e[2][p[2] % e[2].size()] : 1) * (p[3] > 0 ? e[3][p[3] % e[3].size()] : 1)
              * (p[5] > 0 ? e[5][p[5] % e[5].size()] : 1) * (p[7] > 0 ? e[7][p[7] % e[7].size()] : 1) % 10;
    std::cout << ans;
    return 0;
}