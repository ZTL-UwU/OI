#include <algorithm>
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
struct data
{
    long long x, t;
};
const int MAXN = 1e5 + 10;
priority_queue<int> pq;
data a[MAXN];
inline bool cmp(data x, data y) { return x.x < y.x; }
int main()
{
    long long n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x >> a[i].t;
    sort(a + 1, a + n + 1, cmp);
    int ans = -1;
    for (int i = 1; i <= n; i++)
    {
        m -= (a[i].x - a[i - 1].x);
        while (m < 0 && !pq.empty())
        {
            m += pq.top();
            pq.pop();
        }
        if (m < 0)
            break;
        if (m >= a[i].t)
        {
            m -= a[i].t;
            pq.push(a[i].t);
        }
        else if (!pq.empty() && a[i].t < pq.top())
        {
            m += pq.top();
            pq.pop();
            m -= a[i].t;
            pq.push(a[i].t);
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans;
    return 0;
}