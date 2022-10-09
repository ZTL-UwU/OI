#include <iostream>
#include <cstring>

const int MAX_N = 1e5 + 10;

int rmq[MAX_N][21];
int lg[MAX_N];
int a[MAX_N];
int n, d;

void st_init()
{
    std::memset(rmq, 127, sizeof(rmq));
    lg[0] = -1;
    for (int i = 1; i <= MAX_N; i++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i++)
        rmq[i][0] = a[i];
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            rmq[j][i] = std::min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
}

int st(int l, int r)
{
    int k = lg[r - l + 1];
    int res = std::min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
    return res;
}

int main()
{
    std::cin >> n >> d;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    st_init();

    int ans = 0;
    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++)
            if (((a[l] ^ a[r]) ^ st(l, r)) == d)
                ans++;

    std::cout << ans;
    return 0;
}