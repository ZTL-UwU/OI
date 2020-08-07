#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>
#define in(a) a = read()
#define REP(i, k, n) for (long long i = k; i <= n; i++)
#define MAXN 100010
using namespace std;
typedef pair<long long, long long> P;
inline long long read()
{
    long long x = 0, t = 1, c;
    while (!isdigit(c = getchar()))
        if (c == '-')
            t = -1;
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    return x * t;
}
long long n, m, s;
long long total = 0, head[MAXN], nxt[MAXN * 2], to[MAXN * 2], val[MAXN * 2];
long long dis[MAXN], vis[MAXN];
priority_queue<P, vector<P>, greater<P>> Q; //优先队列优化
inline void adl(long long a, long long b, long long c)
{
    total++;
    to[total] = b;
    val[total] = c;
    nxt[total] = head[a];
    head[a] = total;
    return;
}
inline void Dijkstra()
{
    REP(i, 1, n)
    dis[i] = 2147483647;
    dis[s] = 0;
    Q.push(P(0, s));
    while (!Q.empty())
    {
        long long u = Q.top().second; //取出dis最小的点
        Q.pop();                      //弹出
        if (vis[u])
            continue;
        vis[u] = 1;
        for (long long e = head[u]; e; e = nxt[e])
            if (dis[to[e]] > dis[u] + val[e])
            {
                dis[to[e]] = dis[u] + val[e];
                Q.push(P(dis[to[e]], to[e])); //插入
            }
    }
    return;
}
int main()
{
    in(n), in(m), in(s);
    long long a, b, c;
    REP(i, 1, m)
    in(a), in(b), in(c), adl(a, b, c);
    Dijkstra();
    REP(i, 1, n)
    printf("%lld ", dis[i]);
}