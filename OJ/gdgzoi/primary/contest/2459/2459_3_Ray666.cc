#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> id;

struct node
{
    int state;
    int next;
} a[4000001];

int f[201], m[201], tot = 0, n, ans = 0;
bool check[20000001];

// x: strength
// y: state
// tot: id -> head
void add(int x, int y)
{
    a[++tot].state = y;  // New node y
    a[tot].next = id[x]; // y.next = x.id
    id[x] = tot;         // x.id = y.id (tot)
}

// x: counter
// y: power of group A
// z: bin state
void dfs(int x, int y, int z)
{
    if (x > n / 2 - 2) // Done choosing
    {
        if (y >= 0)
            add(y, z);
        return;
    }
    dfs(x + 1, y + m[x], z + f[x]); // Choose to group A
    dfs(x + 1, y - m[x], z + f[x]); // Choose to group B
    dfs(x + 1, y, z);               // Choose nothing
}

void work(int x, int y, int z)
{
    for (int i = id[y]; i; i = a[i].next)
    {
        if (!check[a[i].state + z])
        {
            check[a[i].state + z] = true;
            ans++;
        }
    }
    if (x > n)
        return;
    work(x + 1, y + m[x], z + f[x]);
    work(x + 1, y - m[x], z + f[x]);
    work(x + 1, y, z);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &m[i]);

    f[1] = 1;
    for (int i = 2; i <= n; i++)
        f[i] = f[i - 1] * 2;

    dfs(1, 0, 0);          // Left half
    work(n / 2 - 1, 0, 0); // Right half

    ans--;
    printf("%d", ans);
}