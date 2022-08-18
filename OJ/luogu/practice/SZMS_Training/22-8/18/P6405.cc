#include <algorithm>
#include <iostream>
#include <vector>

const double EPS = 1e-12;
const int MAX_NN = 7e5;
const int MAX_N = 1e3;

int h[MAX_N][MAX_N];
int v[MAX_N][MAX_N];
int n;

class union_find
{
public:
    int *size = new int[MAX_NN]();
    int *fa = new int[MAX_NN]();

    union_find()
    {
        for (int i = 0; i <= n * n; i++)
        {
            fa[i] = i;
            size[i] = 1;
        }
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
        {
            size[fx] += size[fy];
            fa[fy] = fx;
        }
    }
};

struct edge
{
    int u, v;
    double time;

    edge(int u, int v, double time)
    {
        this->u = u;
        this->v = v;
        this->time = time;
    }
};

int no(int x, int y) { return x * n + y; }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> h[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> v[i][j];

    std::vector<edge> e;
    union_find universal;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != 0)
            {
                if (h[i][j] == h[i - 1][j] && v[i][j] == v[i - 1][j])
                    universal.merge(no(i, j), no(i - 1, j));
                else if (v[i][j] != v[i - 1][j])
                    e.push_back(
                        edge(no(i, j), no(i - 1, j), (double)(h[i - 1][j] - h[i][j]) / (v[i][j] - v[i - 1][j])));

                if (e.back().time < -EPS)
                    e.pop_back();
            }
            if (j != 0)
            {
                if (h[i][j] == h[i][j - 1] && v[i][j] == v[i][j - 1])
                    universal.merge(no(i, j), no(i, j - 1));
                else if (v[i][j] != v[i][j - 1])
                    e.push_back(
                        edge(no(i, j), no(i, j - 1), (double)(h[i][j - 1] - h[i][j]) / (v[i][j] - v[i][j - 1])));

                if (e.back().time < -EPS)
                    e.pop_back();
            }
        }
    }

    std::sort(e.begin(), e.end(), [](edge e1, edge e2) -> bool { return e1.time < e2.time; });

    int ans = -1;
    for (int i = 0; i < n * n; i++)
        ans = std::max(ans, universal.size[universal.find(i)]);

    for (std::size_t i = 0; i < e.size(); i++)
    {
        union_find now = universal;
        std::size_t j;

        for (j = i; j < e.size(); j++)
        {
            if (std::abs(e[i].time - e[j].time) > EPS)
                break;
            now.merge(e[j].u, e[j].v);
            ans = std::max(ans, now.size[now.find(e[j].u)]);
        }

        i = j - 1;
    }

    std::cout << ans;
    return 0;
}