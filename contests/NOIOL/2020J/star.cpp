#include <iostream>
using namespace std;
const int MAXN = 2e3;
char a[MAXN][MAXN];
int dir[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
bool vis[MAXN][MAXN];
int ha[MAXN];
int dfs(int x, int y)
{
    int num = 1;
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (xx >= 0 && yy >= 0 && a[xx][yy] == '*' && !vis[xx][yy])
        {
            vis[xx][yy] = true;
            num += dfs(xx, yy);
        }
    }
    return num;
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '*' && !vis[i][j])
            {
                int tmp = dfs(i, j);
                if (tmp > 1)
                    tmp--;
                ha[tmp]++;
            }
    int ans = 0;
    int maxn = -0x7fffffff;
    for (int i = 0; i < MAXN; i++)
    {
        if (ha[i] > 0)
        {
            maxn = max(maxn, i * ha[i]);
            ans++;
        }
    }
    cout << ans << " " << maxn;
    return 0;
}