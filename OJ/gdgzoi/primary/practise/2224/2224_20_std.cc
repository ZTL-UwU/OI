#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
#define MP(x, y) make_pair(x, y)
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;

struct Node
{
    int to, nx;
} E[N * 2];
int head[N], tot;
void add(int fr, int to)
{
    E[tot].to = to;
    E[tot].nx = head[fr];
    head[fr] = tot++;
}
int vis[N];
int nw;
int divisor;

int val[N];
int Prime[N];
int Isprime[N];
int cnt;
int dis[N];
int ans;

map<int, vector<int>> mp;
map<int, vector<int>>::iterator it;

void dfs(int x)
{
    dis[x] = 1;
    int maxx = 0, Maxx = 0;
    for (int i = head[x]; ~i; i = E[i].nx)
    {
        int y = E[i].to;
        if (vis[y] == nw || val[y] % divisor)
            continue;
        vis[y] = nw;
        dfs(y);
        if (dis[y] > Maxx)
            maxx = Maxx, Maxx = dis[y];
        else if (dis[y] > maxx)
            maxx = dis[y];
    }
    ans = max(maxx + Maxx + 1, ans);
    dis[x] = Maxx + 1;
}
void solve(int x)
{
    divisor = x;

    //  printf("%d: ",x); for(int i = 0; i < mp[x].size(); ++i) printf("%d ", mp[x][i]); printf("\n");
    ++nw;
    for (int i = 0; i < mp[x].size(); ++i)
    {
        int y = mp[x][i];
        if (vis[y] != nw)
        {
            vis[y] = nw;
            dfs(y);
            //          printf("hh\n");
        }
    }
}
int main()
{
    int n;
    cnt = 0;
    for (int i = 2; i < N; ++i)
    {
        if (!Prime[i])
        {
            Isprime[++cnt] = i;
            for (int j = 2 * i; j < N; j += i)
            {
                Prime[j]++;
            }
        }
    }
    //  for(int i = 1; i <= 10; ++i) printf("%d ", Isprime[i]); printf("\n");
    std::cin >> n;
        mp.clear();
        nw = 0;
        memset(vis, 0, sizeof(vis));
        memset(head, -1, sizeof(head));
        tot = 0;

        for (int i = 1; i < n; ++i)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            add(a, b);
            add(b, a);
        }
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &val[i]);
            int tt = val[i];
            //  printf("%d ", val[i]);
            for (int j = 1; 1ll * Isprime[j] * Isprime[j] <= tt; ++j)
            {
                if (tt % Isprime[j] == 0)
                {
                    mp[Isprime[j]].push_back(i);
                    while (tt % Isprime[j] == 0)
                    {
                        tt /= Isprime[j];
                    }
                }
            }
            if (tt != 1)
            {
                mp[tt].push_back(i);
            }
        }
        //  printf("hh\n");

        ans = -1;
        for (it = mp.begin(); it != mp.end(); ++it)
        {
            solve(it->first);
        }

        printf("%d\n", ans);
    return 0;
}