#include <algorithm>
#include <functional>
#include <vector>
#include <cmath>
#include <cstdio>

#define MAXN 50005
#define SQRTMAXN 5000
using namespace std;

struct swap_t {
    int x, y;
    swap_t(int xi, int yi) {
        x = xi;
        y = yi;
    }
};

int n, m;
int cnt;
int block;
int bl[MAXN];
int css[SQRTMAXN][20];
vector<swap_t> tag[SQRTMAXN];
int dfn[MAXN], dfnS[MAXN], top[MAXN];
int depth[MAXN], father[MAXN];
int son[MAXN], siz[MAXN];
int c[MAXN], v[MAXN];
vector<int> G[MAXN];

void do_swap(int l, int r, swap_t k) {
    const int pending = 15;
    int x = k.x;
    int y = k.y;

    for (int i = l; i <= r; ++i) {
        if (c[dfnS[i]] == x)
            c[dfnS[i]] = pending;
    }

    for (int i = l; i <= r; ++i) {
        if (c[dfnS[i]] == y)
            c[dfnS[i]] = x;
    }

    for (int i = l; i <= r; ++i) {
        if (c[dfnS[i]] == pending)
            c[dfnS[i]] = y;
    }
}

void update_tags(int x) {
    for (size_t i = 0; i < tag[x].size(); ++i) {
        do_swap((x - 1) * block + 1, x * block, tag[x][i]);
    }
    tag[x].clear();
}

void commit(int x) {
    for (int i = 0; i < 10; ++i)
        css[x][i] = 0;

    for (int i = (x - 1) * block + 1; i <= x * block; ++i) {
        css[x][c[dfnS[i]]] += v[dfnS[i]];
    }
}

void modify(int l, int r, int x, int y) {
    update_tags(bl[l]);
    do_swap(l, min(r, bl[l] * block), swap_t(x, y));
    commit(bl[l]);

    if (bl[l] != bl[r]) {
        update_tags(bl[r]);
        do_swap((bl[r] - 1) * block + 1, r, swap_t(x, y));
        commit(bl[r]);
    }

    for (int i = bl[l] + 1; i <= bl[r] - 1; ++i) {
        tag[i].push_back(swap_t(x, y));
        swap(css[i][x], css[i][y]);
    }
}

void modify2(int k, int cc, int vv) {
    update_tags(bl[k]);
    c[dfnS[k]] = cc;
    v[dfnS[k]] = vv;
    commit(bl[k]);
}

int query(int l, int r, int x) {
    int res = 0;

    update_tags(bl[l]);
    for (int i = l; i <= min(r, bl[l] * block); ++i) {
        if (c[dfnS[i]] == x)
            res += v[dfnS[i]];
    }

    if (bl[l] != bl[r]) {
        update_tags(bl[r]);
        for (int i = (bl[r] - 1) * block + 1; i <= r; ++i) {
            if (c[dfnS[i]] == x)
                res += v[dfnS[i]];
        }
    }

    for (int i = bl[l] + 1; i <= bl[r] - 1; ++i) {
        res += css[i][x];
    }

    return res;
}

void dfs(int x, int f) {
    if (f != -1)
        depth[x] = depth[f] + 1;
    else
        depth[x] = 1;

    father[x] = f;

    siz[x] = 1;
    int sonsize = 0;
    for (size_t i = 0; i < G[x].size(); ++i) {
        int y = G[x][i];
        if (y == f)
            continue;

        dfs(y, x);
        siz[x] += siz[y];
        if (siz[y] > sonsize) {
            sonsize = siz[y];
            son[x] = y;
        }
    }
}

void dfs2(int x, int topf) {
    dfn[x] = cnt;
    dfnS[cnt] = x;
    cnt += 1;
    top[x] = topf;
    if (siz[x] == 1)
        return;

    dfs2(son[x], topf);
    for (size_t i = 0; i < G[x].size(); ++i) {
        int y = G[x][i];
        if (y == father[x])
            continue;

        if (y == son[x])
            continue;

        dfs2(y, y);
    }
}

void Smodify(int k, int x, int y) {
    modify(dfn[k], dfn[k] + siz[k] - 1, x, y);
}

int Lquery(int x, int y, int cc) {
    int res = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]])
            swap(x, y);

        res += query(dfn[top[x]], dfn[x], cc);
        x = father[top[x]];
    }

    if (depth[x] > depth[y])
        swap(x, y);
    res += query(dfn[x], dfn[y], cc);
    return res;
}

int main() {
    freopen("data.in","r",stdin);
    freopen("data.ans","w",stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", c + i);
    for (int i = 1; i <= n; ++i)
        scanf("%d", v + i);

    for (int i = 1; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        x += 1;
        y += 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    cnt = 1;
    dfs(1, -1);
    dfs2(1, 1);

    block = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        bl[i] = (i - 1) / block + 1;
    }

    for (int i = 1; i <= block; ++i) {
        commit(i);
    }

    scanf("%d", &m);
    for (int cid = 1; cid <= m; ++cid) {
        char* cmd = new char[64];
        int a;
        int b;
        int c;
        scanf("%s %d %d %d", cmd, &a, &b, &c);
        if (cmd[0] == 'A') { // Ask
            a += 1;
            b += 1;
            printf("%d\n", Lquery(a, b, c));
        } else if (cmd[0] == 'C') { // Change
            a += 1;
            Smodify(a, b, c);
        } else if (cmd[0] == 'S') { // Set
            a += 1;
            modify2(dfn[a], b, c);
        }

        delete[] cmd;
    }
    return 0;
}