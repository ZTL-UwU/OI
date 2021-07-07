#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

#define MAX_N 2000005
using namespace std;

vector<int> G[MAX_N];
stack<int> s;

int low[MAX_N], dfn[MAX_N], color[MAX_N];
int depth, sum;

void tarjan(int x)
{
    low[x] = dfn[x] = ++depth;
    s.push(x);

    for (unsigned i = 0; i < G[x].size(); ++i)
    {
        int y = G[x][i];
        if (!dfn[y])
        {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if (!color[y])
        {
            low[x] = min(low[x], dfn[y]);
        }
    }

    if (low[x] == dfn[x])
    {
        ++sum;
        int y;
        do
        {
            y = s.top();
            s.pop();
            color[y] = sum;
        } while (y != x);
        color[x] = sum;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, a, b;
        scanf("%d %d %d %d", &x, &a, &y, &b);

        if (!a && !b)
        { // aS
            G[x + n].push_back(y);
            G[y + n].push_back(x);
        }
        else if (a && !b)
        { // aAAAA
            G[x].push_back(y);
            G[y + n].push_back(x + n);
        }
        else if (!a && b)
        { // a =ss
            G[x + n].push_back(y + n);
            G[y].push_back(x);
        }
        else
        { // a == 1 && b == 1
            G[x].push_back(y + n);
            G[y].push_back(x + n);
        }
    }

    for (int i = 1; i <= n * 2; ++i)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (color[i] == color[i + n])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }

    printf("POSSIBLE\n");
    for (int i = 1; i <= n; ++i)
    {
        printf("%d ", color[i] > color[i + n]);
    }
    printf("\n");
    return 0;
}