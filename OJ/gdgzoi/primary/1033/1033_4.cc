#include <iostream>
using namespace std;
const int MAXN = 5e4;
int fa[MAXN];
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    fa[fx] = fy;
}
int main()
{
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int k;
        cin >> k;
        int s;
        cin >> s;
        for (int j = 1; j < k; j++)
        {
            int a;
            cin >> a;
            merge(a, s);
        }
    }
    int ans = 1;
    int father = find(0);
    for (int i = 1; i <= n; i++)
        if (find(i) == father)
            ans++;
    cout << ans;
    return 0;
}