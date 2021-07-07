#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 15;

int f[N][N]; // f[i][j] 一共有i位，且最高位是j的方案数
int l, r;

void init()
{
    for (int i = 0; i <= 9; i++)
        f[1][i] = 1;
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = j; k <= 9; k++)
                f[i][j] += f[i - 1][k];
}

int dfs(int x)
{
    if (!x)
        return 1;
    vector<int> num;
    while (x)
        num.push_back(x % 10), x /= 10;

    int ans = 0;
    int last = 0;
    for (int i = num.size() - 1; i >= 0; i--)
    {
        int n = num[i];
        for (int j = last; j < n; j++)
            ans += f[i + 1][j];
        if (n < last)
            break;
        last = n;
        if (!i)
            ans++; //代表 x 就是这么一个满足要求的数字
    }
    return ans;
}

int main()
{
    init();
    while (scanf("%d%d", &l, &r) == 2)
        cout << dfs(r) - dfs(l - 1) << endl;
    return 0;
}