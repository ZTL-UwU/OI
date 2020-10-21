#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAXN_M = 2e5 + 10;
const int MAXN_N = 1e4 + 10;
vector<int> g1[MAXN_N];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g1[u].push_back(v);
    }
    
    return 0;
}