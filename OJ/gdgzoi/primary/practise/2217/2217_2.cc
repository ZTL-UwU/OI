#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int s = 1, t = 26;
int g[100][100];
int minn[100];
int pre[100];
inline int transform(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A') + 1;
    return 27 + (c - 'a');
}
inline void compress()
{
    while (1)
    {
        bool flag = true;
        for (int i = 1; i <= 52; i++)
        {
            if (i == s || i == t)
                continue;
            int num = 0;
            int len = 0x7fffffff;
            int l, r;
            for (int j = 1; j <= 52; j++)
            {
                if (g[i][j])
                {
                    if (++num >= 3)
                        break;
                    if (num == 1)
                        l = j;
                    else
                        r = j;
                    len = min(len, g[i][j]);
                }
            }
            if (num == 2)
            {
                flag = false;
                g[l][i] = g[i][l] = g[r][i] = g[i][r] = 0;
                g[l][r] += len;
                g[r][l] += len;
            }
        }
        if (flag)
            break;
    }
}
int main()
{
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char u, v;
        int w;
        cin >> u >> v >> w;
        int x = transform(u);
        int y = transform(v);
        g[x][y] += w;
        g[y][x] += w;
    }
    compress();
    cout << g[s][t];
    return 0;
}