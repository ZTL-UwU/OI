#include <cstdio>
#include <iostream>
#include <algorithm>
#define d(i, j) ((i - 1) * n + j)
#define esp 1e-12
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
using namespace std;
int n, m, k, ans = 1, cnt, un, wn, lasttop;
struct yyy
{
    int x, y;
    double z;
} s[2000039];
int a[2039][2039], b[2039][2039];
inline bool cmp(yyy x, yyy y) { return x.z < y.z; }
inline void swap(int &x, int &y) { x ^= y ^= x ^= y; }
struct ques
{
    int x, y, flag;
};
struct dsu
{
    int fa[600039], w[600039], siz[600039], sh;
    ques st[600039], tmp;
    inline int find(int x) { return fa[x] == x ? x : find(fa[x]); }
    inline void merge(int x, int y)
    {
        int un = find(x), wn = find(y);
        if (un != wn)
        {
            if (w[un] < w[wn])
                swap(un, wn);
            st[++sh] = (ques){un, wn, w[un] == w[wn]};
            siz[un] += siz[wn];
            fa[wn] = un;
            w[un] += (w[un] == w[wn]);
        }
    }
    inline void del()
    {
        tmp = st[sh--];
        fa[tmp.y] = tmp.y;
        w[tmp.x] -= tmp.flag;
        siz[tmp.x] -= siz[tmp.y];
    }
} f;
int main()
{
    // freopen("1.in", "r", stdin);
    //	freopen("suma.out","w",stdout);
    int i, j, h;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    }
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            scanf("%d", &b[i][j]);
    }
    for (i = 1; i <= n * n; i++)
        f.fa[i] = i, f.siz[i] = f.w[i] = 1;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (i != 1)
            {
                if (b[i][j] == b[i - 1][j])
                {
                    if (a[i][j] == a[i - 1][j])
                        f.merge(d(i, j), d(i - 1, j));
                }
                else
                    s[++cnt] = (yyy){d(i, j), d(i - 1, j), ((double)(a[i - 1][j] - a[i][j])) / (b[i][j] - b[i - 1][j])};
            }
            if (s[cnt].z < -esp)
                cnt--;
            if (j != 1)
            {
                if (b[i][j] == b[i][j - 1])
                {
                    if (a[i][j] == a[i][j - 1])
                        f.merge(d(i, j), d(i, j - 1));
                }
                else
                    s[++cnt] = (yyy){d(i, j), d(i, j - 1), ((double)(a[i][j - 1] - a[i][j])) / (b[i][j] - b[i][j - 1])};
            }
            if (s[cnt].z < -esp)
                cnt--;
        }
    }
    for (int i = 1; i <= n * n; i++)
        std::cout << f.fa[i] << " ";
    sort(s + 1, s + cnt + 1, cmp);
    // for (int i = 1; i <= cnt; i++)
    //     std::cout << s[i].x << " " << s[i].y << " " << s[i].z << "\n";
    lasttop = f.sh;
    for (i = 1; i <= n * n; i++)
        ans = max(ans, f.siz[i]);
    // std::cout << ans << "\n";

    for (i = 1; i <= cnt; i++)
    {
        for (j = i; j <= cnt; j++)
        {
            if (abs(s[i].z - s[j].z) > esp)
                break;
            f.merge(s[j].x, s[j].y);
            ans = max(ans, f.siz[f.find(s[j].x)]);
        }
        while (f.sh != lasttop)
            f.del();
        i = j - 1;
        std::cout << "\n";
    }
    printf("%d\n", ans);
}