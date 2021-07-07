#include <iostream>
#include <stdio.h>
#include <vector>
struct data
{
    int v, w;
};
const int MAXN = 10000;
vector<data> g[MAXN];
int n, m;
using namespace std;
int main()
{
    while (1)
    {
        cin >> n >> m;
        if (!n && !m)
            return 0;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].push_back((data){v, w});
            g[v].push_back((data){u, w});
        }
    }
    return 0;
}