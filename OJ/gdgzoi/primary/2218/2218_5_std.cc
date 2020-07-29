#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>

#define MAX_N (100000 + 5)

using namespace std;

struct Node
{
    long long x;
    int t;
    friend inline bool operator<(Node a, Node b)
    {
        return a.x < b.x;
    }
};

int n;
long long m;
Node a[MAX_N];
priority_queue<int> q;
int ans;

int main()
{
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%d", &a[i].x, &a[i].t);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i)
    {
        m -= a[i].x - a[i - 1].x;
        while (m < 0 && !q.empty())
        {
            m += q.top();
            q.pop();
        }
        if (m < 0)
            break;
        if (m >= a[i].t)
        {
            m -= a[i].t;
            q.push(a[i].t);
        }
        else if (!q.empty() && a[i].t < q.top())
        {
            m += q.top();
            q.pop();
            m -= a[i].t;
            q.push(a[i].t);
        }
        ans = max(ans, (int)q.size());
    }
    printf("%d", ans);
    return 0;
}