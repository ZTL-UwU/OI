#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;
const int ROOT = 1;

std::vector<int> g[MAX_N];

int heavy_son[MAX_N];
int father[MAX_N];
int size[MAX_N];
int top[MAX_N];
int dfn[MAX_N];

long long st[4 * MAX_N];
short tag[MAX_N];
int n;

void push_down(int k, int l, int r)
{
    if (tag[k])
    {
        const int mid = (l + r) / 2;
        const int ls = k * 2;
        const int rs = k * 2 + 1;

        if (tag[k] == 2)
        {
            st[ls] = mid - l + 1;
            st[rs] = r - mid;
        }
        else
            st[ls] = st[rs] = 0;

        tag[ls] = tag[k];
        tag[rs] = tag[k];
        tag[k] = 0;
    }
}

void push_up(int k)
{
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    st[k] = st[ls] + st[rs];
}

void update(int l_tar, int r_tar, short val, int l = 1, int r = n, int k = 1)
{
    if (l_tar > r_tar)
        std::swap(l_tar, r_tar);

    if (l_tar <= l && r <= r_tar)
    {
        tag[k] = val;
        if (val == 2)
            st[k] = r - l + 1;
        else
            st[k] = 0;
        return;
    }

    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    push_down(k, l, r);
    if (l_tar <= mid)
        update(l_tar, r_tar, val, l, mid, ls);
    if (r_tar > mid)
        update(l_tar, r_tar, val, mid + 1, r, rs);
    push_up(k);
}

void dfs1(int u)
{
    size[u] = 1;
    for (auto v : g[u])
    {
        dfs1(v);
        size[u] += size[v];

        if (size[v] >= size[heavy_son[u]])
            heavy_son[u] = v;
    }
}

int time_stamp = 1;
void dfs2(int u)
{
    if (heavy_son[u] != 0)
    {
        dfn[heavy_son[u]] = ++time_stamp;
        top[heavy_son[u]] = top[u];
        dfs2(heavy_son[u]);
    }

    for (auto v : g[u])
    {
        if (top[v] == 0)
        {
            dfn[v] = ++time_stamp;
            top[v] = v;
            dfs2(v);
        }
    }
}

void route(int x, short val)
{
    int fx = top[x];
    while (fx != ROOT)
    {
        update(dfn[fx], dfn[x], val);
        x = father[top[x]];
        fx = top[x];
    }
    update(ROOT, dfn[x], val);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    for (int i = ROOT + 1; i <= n; i++)
    {
        std::cin >> father[i];
        father[i]++;
        g[father[i]].push_back(i);
    }

    dfs1(ROOT);
    dfn[ROOT] = 1;
    top[ROOT] = ROOT;
    dfs2(ROOT);

    int q;
    std::cin >> q;

    for (int _i = 0; _i < q; _i++)
    {
        std::string op;
        int x;
        std::cin >> op >> x;
        x++;

        if (op == "install")
        {
            const auto before = st[dfn[ROOT]];
            route(x, 2);
            std::cout << st[dfn[ROOT]] - before << "\n";
        }
        else
        {
            const auto before = st[dfn[ROOT]];
            update(dfn[x], dfn[x] + size[x], 1);
            std::cout << before - st[dfn[ROOT]] << "\n";
        }
    }
    return 0;
}
