#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w, f; };
const int INF = 0x7fffffff;
const int MAXN = 110;
vector<data> g[MAXN];
string name[MAXN];
int n, m, s, t;
inline int get_num(string s)
{
    for (int i = 1; i <= n; i++)
        if (name[i] == s)
            return i;
    return -1;
}
int main()
{
    cin >> n >> m;
    s = 0;
    t = n * 2;
    for (int i = 1; i <= n; i++)
        cin >> name[i];
    g[n].push_back((data){n * 2, });
    for (int i = 0; i < m; i++)
    {
        string su, sv;
        cin >> su >> sv;
        int u, v;
        u = get_num(su);
        v = get_num(sv);
        
    }
    return 0;
}