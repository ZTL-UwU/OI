// luogu-judger-enable-o2
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
typedef double db;
const db eps = 1e-9;
int v[2 * N];
int x[2 * N];
int al[N];
int ct;
db val[2 * N];
int siz[N];
bool book[N];
bool cut[N];
db mxv[N];
int q[N];
int hd;
int tl;
int L;
int R;
int n;
struct data
{
    int dep;
    db v;
    friend bool operator<(data a, data b) { return a.dep > b.dep; }
};
struct chi //对每个联通块排序
{
    int mxdep;
    vector<data> ve;
    inline void push(const data &da)
    {
        mxdep = max(mxdep, da.dep);
        ve.push_back(da);
    }
    inline void srt() { sort(ve.begin(), ve.end()); }
};
vector<chi> s[N];
inline bool cmp(const chi &a, const chi &b) { return a.mxdep < b.mxdep; }
inline void add(int u, int V, db va)
{
    v[++ct] = V;
    x[ct] = al[u];
    al[u] = ct;
    val[ct] = va;
}
inline int dfs1(int u) // siz
{
    book[u] = true;
    siz[u] = 1;
    for (int i = al[u]; i; i = x[i])
        if (!book[v[i]] && !cut[v[i]])
            siz[u] += dfs1(v[i]);
    book[u] = false;
    return siz[u];
}
inline int find(int u, const int &tot) //重心
{
    book[u] = true;
    int ret = u;
    for (int i = al[u]; i; i = x[i])
        if (!book[v[i]] && !cut[v[i]] && 2 * siz[v[i]] >= tot)
        {
            ret = find(v[i], tot);
            break;
        }
    book[u] = false;
    return ret;
}
inline void dfs2(int u, vector<chi>::iterator ve, int dep, db dis)
{
    book[u] = true;
    ve->push((data){dep, dis});
    for (int i = al[u]; i; i = x[i])
        if (!book[v[i]] && !cut[v[i]])
            dfs2(v[i], ve, dep + 1, dis + val[i]);
    book[u] = false;
}
inline void solve(int u) //构建点分树
{
    dfs1(u);
    int g = find(u, siz[u]);
    cut[g] = true;
    for (int i = al[g]; i; i = x[i])
    {
        if (cut[v[i]])
            continue;
        s[g].push_back(chi());
        dfs2(v[i], --s[g].end(), 1, val[i]);
        (--s[g].end())->srt();
    }
    sort(s[g].begin(), s[g].end(), cmp);
    for (int i = al[g]; i; i = x[i])
    {
        if (!cut[v[i]])
            solve(v[i]);
    }
}
inline bool jud(db ans) //每次在点分树上拼合路径
{
    vector<chi>::iterator it1;
    vector<data>::iterator it2;
    for (int i = 1; i <= n; i++)
        mxv[i] = -0x7f7f7f7f;
    bool ret = false;
    for (int i = 1, nwdep; i <= n; i++)
    {
        for (it1 = s[i].begin(), nwdep = 0; it1 != s[i].end(); nwdep = it1->mxdep, ++it1)
        {
            int dr = 0;
            for (it2 = it1->ve.begin(), hd = 1, tl = 0; it2 != it1->ve.end(); ++it2) //单调队列
            {
                int nl = max(0, (int)(L - it2->dep));
                int nr = min(nwdep, (int)(R - it2->dep));
                if (nl > nr)
                {
                    continue;
                }
                for (int np = dr + 1; np <= nr; np++)
                {
                    while (hd <= tl && mxv[q[tl]] < mxv[np])
                        --tl;
                    q[++tl] = np;
                }
                while (hd <= tl && q[hd] < nl)
                {
                    ++hd;
                }
                dr = nr;
                if (mxv[q[hd]] + it2->v - ans * it2->dep > eps)
                {
                    ret = true;
                    goto skip;
                }
            }
            for (it2 = it1->ve.begin(); it2 != it1->ve.end(); ++it2) //特判到根的路径同时将路径插入到权值数组中
            {
                mxv[it2->dep] = max(mxv[it2->dep], it2->v - ans * it2->dep);
                if (L <= it2->dep && it2->dep <= R && mxv[it2->dep] > eps)
                {
                    ret = true;
                    goto skip;
                }
            }
        }
    skip:;
        for (it1 = s[i].begin(); it1 != s[i].end(); ++it1)
            for (it2 = it1->ve.begin(); it2 != it1->ve.end(); ++it2)
            {
                mxv[it2->dep] = -0x7f7f7f7f;
            }
        if (ret)
            return true;
    }
    return false;
}
int main()
{
    scanf("%d%d%d", &n, &L, &R);
    for (int i = 1, u, v, va; i < n; i++)
    {
        scanf("%d%d%d", &u, &v, &va);
        add(u, v, va);
        add(v, u, va);
    }
    solve(1);
    db l = 0;
    db r = 1e6; //无脑二分
    while (r - l > 1e-4)
    {
        db mid = (l + r) / 2;
        (jud(mid) ? l : r) = mid;
    }
    printf("%.3lf", l);
    return 0;
}
