#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

struct node
{
    int ls;
    int rs;

    node()
    {
        this->ls = -1;
        this->rs = -1;
    }
    node(int ls, int rs)
    {
        this->ls = ls;
        this->rs = rs;
    }
};

node tree[MAX_N];
bool flag = false;
int res = 0;

inline void insert(int u, int tar)
{
    if (flag)
        return;

    if (tree[tar].ls == -1 or tree[tar].rs == -1)
    {
        flag = true;
        res = tar;
        if (u < tar)
            tree[tar].ls = u;
        else
            tree[tar].rs = u;

        return;
    }

    if (u < tar and tree[tar].ls != -1)
        insert(u, tree[tar].ls);
    if (u > tar and tree[tar].rs != -1)
        insert(u, tree[tar].rs);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    int tmp;
    for (int _t = 0; _t < t; _t++)
    {
        for (int i = 0; i < MAX_N; i++)
            tree[i] = (node){-1, -1};

        int n;
        std::cin >> n;
        if (n % 2 == 0)
        {
            for (int _i = 0; _i < n; _i++)
                std::cin >> tmp;

            std::cout << "NO\n";
            continue;
        }

        int root;
        std::cin >> root;
        bool flag1 = false;
        for (int i = 0; i < n / 2; i++)
        {
            if (flag1)
            {
                std::cin >> tmp >> tmp;
                continue;
            }

            int u;
            std::cin >> u;
            flag = false;
            res = 0;
            insert(u, root);
            int res1 = res;

            std::cin >> u;
            flag = false;
            res = 0;
            insert(u, root);
            if (res1 != res)
            {
                std::cout << "NO\n";
                flag1 = true;
            }
        }

        if (not flag1)
            std::cout << "YES\n";
    }
    return 0;
}