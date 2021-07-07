#include <iostream>
#include <queue>
#include <vector>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bool used[10000];
    for (int i = 0; i < 10000; i++)
        used[i] = false;
    used[0] = 1;
    queue<vector<int>> q;
    q.push({0, 0});
    while (!q.empty())
    {
        int v = q.front()[0];
        int step = q.front()[1];
        q.pop();
        for (int i = 0; i < n; i++)
        {
            int vv = v + a[i];
            if (vv == m)
            {
                cout << step + 1;
                return 0;
            }
            if (vv < m && !used[vv])
            {
                used[vv] = true;
                q.push({vv, step + 1});
            }
        }
    }
    cout << "Impossible";
    return 0;
}