#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
const int INF = 0x7fffffff;
const int MAXN = 2e5 + 10;
const float alpha = 0.7;
int n, q;
namespace sgt
{
    struct node
    {
        int val;
        int cnt = 0;
        int size = 0;
        node *left;
        node *right;
        bool deleted;
        void push_up();
        bool is_nagetive();
    };
    node *null;
    void node::push_up()
    {
        this->size = !this->deleted + this->left->size + this->right->size;
        this->cnt = 1 + this->left->cnt + this->right->cnt;
    }
    bool node::is_nagetive()
    {
        if (this->cnt * alpha < this->left->cnt
            || this->cnt * alpha < this->right->cnt)
            return true;
        return false;
    }
    void delete_tree(node *now)
    {
        if (now == null)
            return;
        delete_tree(now->left);
        delete_tree(now->right);
        delete now;
    }
    void get_tree(node *now, std::vector<node *> nodes)
    {
        if (now == null)
            return;
        get_tree(now->left, nodes);
        if (!now->deleted)
            nodes.push_back(now);
        get_tree(now->right, nodes);
        if (now->deleted)
            delete now;
    }
    node *build(int l, int r, std::vector<node *> nodes)
    {
        if (l >= r)
            return null;
        int mid = (l + r) / 2;
        node *tree = nodes[mid];
        tree->left = build(l, mid, nodes);
        tree->right = build(mid + 1, r, nodes);
        tree->push_up();
        return tree;
    }
    void rebuild(node *&tree)
    {
        std::vector<node *> nodes;
        get_tree(tree, nodes);
        tree = build(0, nodes.size(), nodes);
    }
    void insert(node *&tree, int val)
    {
        if (tree == null)
        {
            tree = new node;
            tree->cnt = 1;
            tree->size = 1;
            tree->val = val;
            tree->left = null;
            tree->right = null;
            tree->deleted = false;
            return;
        }
        tree->cnt++;
        tree->size++;
        if (val >= tree->val)
            insert(tree->right, val);
        else
            insert(tree->left, val);
        if (tree->is_nagetive())
            rebuild(tree);
    }
    void erase(node *&tree, int rk)
    {
        if (!tree->deleted && rk == tree->left->size + 1)
        {
            tree->deleted = true;
            tree->size--;
            return;
        }
        tree->size--;
        if (rk <= tree->left->size + !tree->deleted)
            erase(tree->left, rk);
        else
            erase(tree->right, rk - tree->left->size - !tree->deleted);
    }
    int rank(node *now, int val)
    {
        int ans = 1;
        while (now != null)
        {
            if (val <= now->val)
                now = now->left;
            else
            {
                ans += now->left->size + !now->deleted;
                now = now->right;
            }
        }
        return ans;
    }
    int find(node *now, int rk)
    {
        while (now != null)
        {
            if (!now->deleted && now->left->size + 1 == rk)
                return now->val;
            if (rk <= now->left->size)
                now = now->left;
            else
            {
                rk -= now->left->size + !now->deleted;
                now = now->right;
            }
        }
        return -1;
    }
};
sgt::node *root;
namespace uf
{
    int siz[MAXN];
    int fa[MAXN];
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
        if (fx == fy)
            return;
        sgt::erase(root, rank(root, siz[fx]));
        sgt::erase(root, rank(root, siz[fy]));
        fa[fx] = fy;
        siz[fy] += siz[fx];
        sgt::insert(root, siz[fy]);
    }
};
int main()
{
    sgt::null = new sgt::node;
    root = sgt::null;
    std::cin >> n >> q;
    sgt::insert(root, INF);
    sgt::insert(root, -INF);
    for (int i = 1; i <= n; i++)
    {
        sgt::insert(root, 1);
        uf::fa[i] = i;
        uf::siz[i] = 1;
    }
    while (q--)
    {
        int type;
        std::cin >> type;
        if (type == 0)
        {
            int x, y;
            std::cin >> x >> y;
            uf::merge(x, y);
        }
        else
        {
            int k;
            std::cin >> k;
            std::cout << sgt::find(root, k + 1) << "\n";
        }
    }
    sgt::delete_tree(root);
    return 0;
}