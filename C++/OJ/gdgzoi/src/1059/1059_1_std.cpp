#include <algorithm>
#include <cstdio>
using namespace std;

int vil[100];
int f[105][100][100];
int mp[105];

int hbitn(int n)
{
    int res = 0;
    while (n > 0)
    {
        if (n & 1)
            ++res;
        n >>= 1;
    }
    return res;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        char *line = new char[15];
        scanf("%s", line);
        for (int j = 0; line[j] != '\0'; ++j)
        {
            if (line[j] == 'P')
                mp[i] = (mp[i] << 1);
            else if (line[j] == 'H')
                mp[i] = (mp[i] << 1) + 1;
        }
        delete[] line;
    }
    int M = 1 << m, cnt = 0;
    for (int i = 0; i < M; ++i)
        if ((i & (i << 1)) == 0 && (i & (i << 2)) == 0)
            vil[++cnt] = i;
    for (int i = 1; i <= cnt; ++i)
        if ((mp[1] & vil[i]) == 0)
            f[1][i][1] = hbitn(vil[i]);
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= cnt; ++j)
        {
            for (int lst = 1; lst <= cnt; ++lst)
            {
                for (int llst = 1; llst <= cnt; ++llst)
                {
                    if ((vil[lst] & vil[llst]) != 0)
                        continue;
                    if ((vil[lst] & vil[j]) != 0)
                        continue;
                    if ((vil[llst] & vil[j]) != 0)
                        continue;
                    if ((vil[j] & mp[i]) != 0)
                        continue;
                    f[i][j][lst] = max(f[i][j][lst], f[i - 1][lst][llst] + hbitn(vil[j]));
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; ++i)
        for (int j = 1; j <= cnt; ++j)
            ans = max(ans, f[n][i][j]);
    printf("%d\n", ans);
    return 0;
}