#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
using namespace std;
const int MAXN = 1e3 + 10, INF = 1e9 + 10;
inline int read()
{
    char c = getchar();
    int x = 0, f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}
int N, M;
vector<int> v[MAXN];
int link[MAXN], vis[MAXN], cnt = 1, Ans[MAXN];
bool Aug(int x)
{
    for (int i = 0; i < v[x].size(); i++)
    {
        int to = v[x][i];
        if (vis[to] == cnt)
            continue;
        vis[to] = cnt;
        if (link[to] == -1 || Aug(link[to]))
        {
            link[to] = x;
            return 1;
        }
    }
    return 0;
}
main()
{
    memset(link, -1, sizeof(link));
    memset(Ans, -1, sizeof(Ans));
    N = read();
    M = read();
    for (int i = 0; i < M; i++)
    {
        int x = read(), y = read();
        v[i].push_back(x);
        if (x != y)
            v[i].push_back(y);
    }
    int ans = 0;
    for (int i = 0; i < M; i++, cnt++)
        if (Aug(i))
            ans++;
        else
            break;
    for (int i = 0; i < N; i++)
        Ans[link[i]] = i;
    printf("%d\n", ans);
    return 0;
}