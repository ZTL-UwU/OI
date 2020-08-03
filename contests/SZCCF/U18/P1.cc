#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 1000;
char mp[MAXN][MAXN];
int sx, sy;
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> mp[i][j];
            if (mp[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
        }
    }
    int ans = 0x7fffffff;
    bool flag = false;
    // Up
    for (int i = 0; i < sx; i++)
        if (mp[i][sy] == '#')
            flag = true;
    ans = min(ans, sx / k + flag);
    // Left
    flag = false;
    for (int i = 0; i < sy; i++)
        if (mp[sx][i] == '#')
            flag = true;
    ans = min(ans, sy / k + flag);
    // Down
    flag = false;
    for (int i = n - 1; i >= sx; i--)
        if (mp[i][sy] == '#')
            flag = true;
    ans = min(ans, (n - sx - 1) / k + flag);
    // Right
    flag = false;
    for (int i = m - 1; i >= sy; i--)
        if (mp[sx][i] == '#')
            flag = true;
    ans = min(ans, (m - sy - 1) / k + flag);
    cout << ans;
    return 0;
}