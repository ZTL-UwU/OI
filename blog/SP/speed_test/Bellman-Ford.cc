#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
struct edge { long long u, v, w; };
const long long INF = 0x7fffffff;
const long long MAXN = 1e4 + 10;
vector<edge> e;
long long dis[MAXN];
long long n, m, s;
void Bellman_Ford()
{
    for (long long i = 0; i < MAXN; i++)
        dis[i] = INF;
    dis[s] = 0;
    while (1)
    {
        bool flag = true;
        for (long long i = 0; i < e.size(); i++)
        {
            if (dis[e[i].v] > dis[e[i].u] + e[i].w)
            {
                dis[e[i].v] = dis[e[i].u]  + e[i].w;
                flag = false;
            }
        }
        if (flag)
            break;
    }
}
int main()
{
    scanf("%lld%lld%lld", &n, &m, &s);
    for (long long i = 0; i < m; i++)
    {
        long long u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        e.push_back((edge){u, v, w});
    }
    Bellman_Ford();
    for (long long i = 1; i <= n; i++)
        printf("%lld ", dis[i]);
    return 0;
}