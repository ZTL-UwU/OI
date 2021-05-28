#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>

const int MAXN = 1e5;
const int MAX_BLOCK_SIZE = 1e3;
const int COLOR_NUMBER = 20;

std::vector<std::pair<int, int>> swap_tag[MAX_BLOCK_SIZE]; // Swap color lazy tag
std::vector<int> tree[MAXN];
int block_color_value[MAXN][COLOR_NUMBER]; // [block][color] -> value
int color[MAXN];
int value[MAXN];

// Block
int block[MAXN]; // block[dfn]
int block_size;  // Size of one block

// Qtree
int depth[MAXN]; // Depth in tree
int size[MAXN];  // Size of subtree
int dfns[MAXN];  // Reverse of dfn
int son[MAXN];   // Heavy son
int dfn[MAXN];   // New id given after heavy son
int top[MAXN];   // Top father that is a heavy node
int fa[MAXN];    // Father node

// Function declear
inline void swap_color(int l, int r, std::pair<int, int> p);
inline void commit_value(int bl);
inline void commit_swap_tag(int bl);
inline void set(int u, int c, int val);
inline void solve_update(int u, int x, int y);
// Block
inline int query(int l, int r, int c);
inline void update(int l, int r, std::pair<int, int> p);
// Qtree
inline void dfs1(int u);
inline void dfs2(int u);
inline int route(int u, int v, int c);

inline void swap_color(int l, int r, std::pair<int, int> p) // Swap pair of color between [l, r]
{
    int x = p.first;
    int y = p.second;

    for (int i = l; i <= r; i++)
    {
        if (color[dfns[i]] == x)
            color[dfns[i]] = y;
        else if (color[dfns[i]] == y)
            color[dfns[i]] = x;
    }
}

inline void commit_value(int bl) // Commit value into block_color_value
{
    for (int i = 0; i < COLOR_NUMBER; i++) // Clear
        block_color_value[bl][i] = 0;

    for (int i = (bl - 1) * block_size + 1; i <= bl * block_size; i++) // Add into block_color_value
        block_color_value[bl][color[dfns[i]]] += value[dfns[i]];
}

inline void commit_swap_tag(int bl) // Commit swap_tag into color
{
    for (auto i : swap_tag[bl]) // Do all swap inside swap_tag
        swap_color((bl - 1) * block_size + 1, bl * block_size, i);

    swap_tag[bl].clear(); // Clear
}

inline void set(int u, int c, int val) // Set color and value
{
    commit_swap_tag(block[dfn[u]]); // Commit swap_tag
    color[u] = c;                   // Set color
    value[u] = val;                 // Set value
    commit_value(block[dfn[u]]);    // Commit value
}

inline void solve_update(int u, int x, int y) { update(dfn[u], dfn[u] + size[u] - 1, std::make_pair(x, y)); }

// Block
// Chunking template
inline int query(int l, int r, int c) // Sum up value in color c between [l, r]
{
    int res = 0;

    // Left part
    commit_swap_tag(block[l]);
    for (int i = l; i <= std::min(block[l] * block_size, r); i++)
        if (color[dfns[i]] == c)
            res += value[dfns[i]];

    // Right part
    if (block[l] != block[r])
    {
        commit_swap_tag(block[r]);
        for (int i = (block[r] - 1) * block_size + 1; i <= r; i++)
            if (color[dfns[i]] == c)
                res += value[dfns[i]];
    }

    // Block part
    for (int i = block[l] + 1; i <= block[r] - 1; i++)
        res += block_color_value[i][c];

    return res;
}

inline void update(int l, int r, std::pair<int, int> p) // Swap pair of color between [l, r]
{
    // Left part
    commit_swap_tag(block[l]);                            // Commit swap tag
    swap_color(l, std::min(block[l] * block_size, r), p); // Do swap
    commit_value(block[l]);                               // Commit value

    // Right part
    if (block[l] != block[r])
    {
        commit_swap_tag(block[r]);
        swap_color((block[r] - 1) * block_size + 1, r, p);
        commit_value(block[r]);
    }

    // Block part
    for (int i = block[l] + 1; i <= block[r] - 1; i++)
    {
        swap_tag[i].push_back(p);                                                 // Push into swap_tag
        std::swap(block_color_value[i][p.first], block_color_value[i][p.second]); // Swap block_color_value
    }
}

// Qtree
// Qtree template
inline void dfs1(int u)
{
    depth[u] = depth[fa[u]] + 1;
    size[u] = 1;

    for (auto v : tree[u])
    {
        if (v != fa[u])
        {
            fa[v] = u;
            dfs1(v);
            size[u] += size[v];

            if (size[son[u]] < size[v])
                son[u] = v;
        }
    }
}

int time_stamp = 1;
inline void dfs2(int u)
{
    if (son[u])
    {
        time_stamp++;
        top[son[u]] = top[u];
        dfn[son[u]] = time_stamp;
        dfns[time_stamp] = son[u];

        dfs2(son[u]);
    }

    for (auto v : tree[u])
    {
        if (v != fa[u] && top[v] == 0)
        {
            time_stamp++;
            top[v] = v;
            dfn[v] = time_stamp;
            dfns[time_stamp] = v;

            dfs2(v);
        }
    }
}

inline int route(int u, int v, int c) // Sum of value from u to v with color c
{
    int res = 0;
    int fu = top[u];
    int fv = top[v];
    while (fu != fv)
    {
        if (depth[fu] < depth[fv])
        {
            std::swap(fu, fv);
            std::swap(u, v);
        }
        res += query(dfn[fu], dfn[u], c);
        u = fa[fu];
        fu = top[u];
    }
    if (depth[u] > depth[v])
        std::swap(u, v);

    res += query(dfn[u], dfn[v], c);
    return res;
}

int main()
{
    // I/O optimize
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    // Input
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> color[i];
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];

    for (int i = 0; i < n - 1; i++) // Build tree
    {
        int u, v;
        std::cin >> u >> v;
        u++;
        v++;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Qtree
    dfs1(1);
    dfns[1] = 1;
    dfn[1] = 1;
    top[1] = 1;
    dfs2(1);

    // Block
    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / block_size + 1;

    for (int i = 1; i <= block_size + 1; i++)
        commit_value(i);

    // Query
    int m;
    std::cin >> m;
    for (int q = 0; q < m; q++)
    {
        std::string token;
        std::cin >> token;

        if (token == "Ask") // Ask u v c
        {
            int u, v, c;
            std::cin >> u >> v >> c;
            u++;
            v++;
            std::cout << route(u, v, c) << '\n';
        }
        if (token == "Set") // Set u c val
        {
            int u, c, val;
            std::cin >> u >> c >> val;
            u++;
            set(u, c, val);
        }
        if (token == "Change") // Change u x y
        {
            int u, x, y;
            std::cin >> u >> x >> y;
            u++;
            solve_update(u, x, y);
        }
    }
    return 0;
}