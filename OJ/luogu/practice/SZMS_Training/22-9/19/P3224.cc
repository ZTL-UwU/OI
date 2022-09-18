#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;
int importance[MAX_N];

template <typename T>
class vvt
{
    struct data
    {
        T val;
        int no;

        bool operator<(const int x) const { return this->val < x; }
    };

public:
    std::vector<data> base;

    vvt() {}
    vvt(std::size_t size) { this->base.reserve(size); }

    T operator[](std::size_t rank)
    {
        if (rank > this->base.size())
            return -1;
        return this->base[rank - 1].no;
    }
    void insert(T val, int no)
    {
        this->base.insert(this->base.empty() ? this->base.begin() :
                                               std::lower_bound(this->base.begin(), this->base.end(), val),
                          {val, no});
    }
    void merge(vvt<T> &x)
    {
        for (auto i : x.base)
            this->insert(i.val, i.no);
    }
};

vvt<int> t[MAX_N];

class ufind
{
private:
    int *fa;

public:
    ufind(int n)
    {
        fa = new int[MAX_N];
        for (int i = 0; i <= n; i++)
            fa[i] = i;
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = this->find(fa[x]);
    }

    void merge(int x, int y)
    {
        const int fx = this->find(x);
        const int fy = this->find(y);

        if (fx != fy)
        {
            fa[fx] = fy;
            t[fy].merge(t[fx]);
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> importance[i];
        t[i].insert(importance[i], i);
    }

    ufind uf(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        uf.merge(u, v);
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        char op;
        int x, y;
        std::cin >> op >> x >> y;

        if (op == 'Q')
            std::cout << t[uf.find(x)][y] << "\n";
        if (op == 'B')
            uf.merge(x, y);
    }
    return 0;
}