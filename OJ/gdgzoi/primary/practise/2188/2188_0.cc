#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const size_t MAX_N = 2e6;
const size_t SUPER_ROOT = 0;

struct sub_t
{
    long long int sum;
    int left_dfn;
    int right_dfn;
};

struct tree_node
{
    long long int value;
    int heavy_son;
    int depth;
    int size;
    int top;
    int fa;

    sub_t sub_tree;
};

std::vector<int> tree[MAX_N];
tree_node node[MAX_N];
int n;

class sit
{
public:
    inline void update(int x, long long int delta);
    inline long long int query(int l, int r);
    sit(int size);

private:
    static inline int low_bit(int x);
    inline long long int query_base(int x);
    std::vector<long long int> t;
};

sit::sit(int size) { this->t.resize(size); }
inline int sit::low_bit(int x) { return x & (-x); }

inline void sit::update(int x, long long int delta)
{
    for (int i = x; i <= n; i += this->low_bit(i))
        this->t[i] += delta;
}

inline long long int sit::query(int l, int r) { return this->query_base(r) - this->query_base(l - 1); }

inline long long int sit::query_base(int x)
{
    long long int res = 0;
    for (int i = x; i > 0; i -= this->low_bit(i))
        res += this->t[i];

    return res;
}

int time_stamp = 0;
inline void get_dfn(int u)
{
    node[u].depth = node[node[u].fa].depth + 1;
    node[u].size = 1;
    node[u].sub_tree.sum = node[u].value;
    time_stamp++;
    node[u].sub_tree.left_dfn = time_stamp;

    for (auto v : tree[u])
    {
        if (v != node[u].fa)
        {
            node[v].fa = u;
            get_dfn(v);

            node[u].sub_tree.sum += node[v].sub_tree.sum;
            node[u].size += node[v].size;
            if (node[v].size > node[node[u].heavy_son].size)
                node[u].heavy_son = v;
        }
    }

    node[u].sub_tree.right_dfn = time_stamp;
}

inline void get_top(int u, int top)
{
    node[u].top = top;
    if (node[u].heavy_son != 0)
        get_top(node[u].heavy_son, top);

    for (auto v : tree[u])
        if (v != node[u].fa and v != node[u].heavy_son)
            get_top(v, v);
}

inline int lca(int u, int v)
{
    while (node[u].top != node[v].top)
    {
        if (node[node[u].top].depth < node[node[v].top].depth)
            std::swap(u, v);
        u = node[node[u].top].fa;
    }

    return node[u].depth < node[v].depth ? u : v;
}

inline void diff_update(sit &diff, sit &val, int a, long long int delta)
{
    diff.update(node[a].sub_tree.left_dfn, delta);
    val.update(node[a].sub_tree.left_dfn, delta * node[a].depth);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t, root;
    std::cin >> n >> t >> root;

    for (int i = 1; i <= n; i++)
        std::cin >> node[i].value;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    sit difference(n);
    sit value(n);

    node[root].fa = SUPER_ROOT;
    get_dfn(root);
    get_top(root, root);

    for (int i = 0; i < t; i++)
    {
        int op, a, b, c, val;
        std::cin >> op;

        switch (op)
        {
            case 1:
                std::cin >> a >> b >> val;

                c = lca(a, b);
                diff_update(difference, value, a, val);
                diff_update(difference, value, b, val);
                diff_update(difference, value, c, -val);
                if (node[c].fa != SUPER_ROOT)
                    diff_update(difference, value, node[c].fa, -val);
                break;

            case 2:
                std::cin >> a;
                std::cout << difference.query(node[a].sub_tree.left_dfn, node[a].sub_tree.right_dfn) + node[a].value
                          << "\n";
                break;

            case 3:
                std::cin >> a;
                std::cout << value.query(node[a].sub_tree.left_dfn, node[a].sub_tree.right_dfn)
                                 + difference.query(node[a].sub_tree.left_dfn, node[a].sub_tree.right_dfn)
                                       * (1 - node[a].depth)
                                 + node[a].sub_tree.sum
                          << "\n";
                break;
        }
    }

    return 0;
}