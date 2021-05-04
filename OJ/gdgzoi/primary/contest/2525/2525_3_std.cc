#include <iostream>

const int MAX_N = 2.1e3;

int t1[MAX_N][MAX_N];
int t2[MAX_N][MAX_N];
int t3[MAX_N][MAX_N];
int t4[MAX_N][MAX_N];
int n, m;

inline int lowbit(int x) { return x & (-x); }

void update(int x, int y, int val)
{
    for (int i = x; i <= n; i += lowbit(i))
    {
        for (int j = y; j <= m; j += lowbit(j))
        {
            t1[i][j] += val;
            t2[i][j] += x * val;
            t3[i][j] += y * val;
            t4[i][j] += x * y * val;
        }
    }
}

int query(int x, int y)
{
    int res = 0;

    for (int i = x; i > 0; i -= lowbit(i))
    {
        for (int j = y; j > 0; j -= lowbit(j))
        {
            res += t1[i][j] * (x + 1) * (y + 1);
            res -= t2[i][j] * (y + 1);
            res -= t3[i][j] * (x + 1);
            res += t4[i][j];
        }
    }

    return res;
}
void diff_update(int a, int b, int c, int d, int val)
{
    update(a, c, val);
    update(a, d + 1, -val);
    update(b + 1, c, -val);
    update(b + 1, d + 1, val);
}

int diff_query(int a, int b, int c, int d)
{
    return query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    char ch;
    std::cin >> ch >> n >> m;
    while (std::cin >> ch)
    {
        if (ch == 'L')
        {
            int a, b, c, d, val;
            std::cin >> a >> c >> b >> d >> val;
            diff_update(a, b, c, d, val);
        }
        if (ch == 'k')
        {
            int a, b, c, d;
            std::cin >> a >> b >> c >> d;
            std::cout << diff_query(a, b, c, d) << "\n";
        }
    }

    return 0;
}