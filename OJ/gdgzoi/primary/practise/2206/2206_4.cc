// SG Function

#include <unordered_set>
#include <iostream>
#include <vector>

const int MAX_N = 2e3 + 10;

class SG
{
private:
    int base[MAX_N];
    std::vector<std::vector<int>> g;
    void init_base();

public:
    explicit SG(const std::vector<std::vector<int>> &g);
    int operator[](const std::size_t state);
};

SG::SG(const std::vector<std::vector<int>> &g)
{
    this->g = g;
    this->init_base();
}

void SG::init_base()
{
    for (int i = 0; i < MAX_N; i++)
        this->base[i] = -1;
}

int SG::operator[](const std::size_t state)
{
    if (this->base[state] != -1)
        return this->base[state];

    std::unordered_set<int> set;

    for (auto sub_state : this->g[state])
        set.insert((*this)[sub_state]);

    for (int i = 0; ; i++)
    {
        if (set.count(i) == 0)
        {
            this->base[state] = i;
            return i;
        }
    }
}

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<int>> g;
    g.resize(n + 1);
    for (int _i = 0; _i < m; _i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
    }

    auto sg = SG(g);

    int ans = 0;
    for (int _i = 0; _i < k; _i++)
    {
        int x;
        std::cin >> x;

        ans ^= sg[x];
    }

    std::cout << (ans != 0 ? "win" : "lose");
    return 0;
}
