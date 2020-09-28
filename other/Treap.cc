#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <string>
const int INF = 0x7fffffff;
namespace Treap
{
    struct node
    {
        node *right;
        node *left;
        int rand_val;
        int size = 0;
        int val;
        int cnt;
        void push_up();
    };
    void node::push_up() { this->size = this->left->size + this->right->size + this->cnt; }
    node *null;

    void new_node(node *&tree, int val)
    {
        tree = new node;
        tree->cnt = 1;
        tree->size = 1;
        tree->left = null;
        tree->right = null;
        tree->val = val;
        tree->rand_val = rand();
    }

    void delete_tree(node *now)
    {
        if (now == null)
            return;
        delete_tree(now->left);
        delete_tree(now->right);
        delete now;
    }

    void zig(node *&now)
    {
        node *tmp = now->left;
        now->left = tmp->right;
        tmp->right = now;
        now = tmp;
        now->right->push_up();
        now->push_up();
    }

    void zag(node *&now)
    {
        node *tmp = now->right;
        now->right = tmp->left;
        tmp->left = now;
        now = tmp;
        now->left->push_up();
        now->push_up();
    }

    int rank(node *now, int val)
    {
        if (now == null)
            return -1;
        if (val == now->val)
            return now->left->size + 1;
        if (val < now->val)
            return rank(now->left, val);
        return rank(now->right, val) + now->left->size + now->cnt;
    }

    int find(node *now, int rk)
    {
        if (now == null)
            return -1;
        if (now->left->size >= rk)
            return find(now->left, rk);
        if (now->left->size + now->cnt >= rk)
            return now->val;
        return find(now->right, rk - now->left->size - now->cnt);
    }

    void insert(node *&tree, int val)
    {
        if (tree == null)
        {
            new_node(tree, val);
            return;
        }
        if (val == tree->val)
        {
            tree->cnt++;
        }
        else if (val < tree->val)
        {
            insert(tree->left, val);
            if (tree->rand_val < tree->left->rand_val)
                zig(tree);
        }
        else
        {
            insert(tree->right, val);
            if (tree->rand_val < tree->right->rand_val)
                zag(tree);
        }
        tree->push_up();
    }

    void erase(node *&tree, int val)
    {
        if (tree == null)
            return;
        if (val == tree->val)
        {
            if (tree->cnt > 1)
            {
                tree->cnt--;
                tree->push_up();
                return;
            }
            if (tree->left != null || tree->right != null)
            {
                if (tree->right == null || tree->left->rand_val > tree->right->rand_val)
                {
                    zig(tree);
                    erase(tree->right, val);
                }
                else
                {
                    zag(tree);
                    erase(tree->left, val);
                }
            }
            else
                tree = null;
        }
        else
        {
            if (val < tree->val)
                erase(tree->left, val);
            else
                erase(tree->right, val);
            tree->push_up();
        }
    }

    int get_pre(int val, node *start)
    {
        node *ans;
        new_node(ans, -INF);
        node *now = start;
        while (now != null)
        {
            if (val == now->val)
            {
                if (now->left != null)
                {
                    now = now->left;
                    while (now->right != null)
                        now = now->right;
                    ans = now;
                }
                break;
            }
            if (now->val < val && now->val > ans->val)
                ans = now;
            if (val < now->val)
                now = now->left;
            else
                now = now->right;
        }
        return ans->val;
    }

    int get_next(int val, node *start)
    {
        node *ans;
        new_node(ans, INF);
        node *now = start;
        while (now != null)
        {
            if (val == now->val)
            {
                if (now->right != null)
                {
                    now = now->right;
                    while (now->left != null)
                        now = now->left;
                    ans = now;
                }
                break;
            }
            if (now->val > val && now->val < ans->val)
                ans = now;
            if (val < now->val)
                now = now->left;
            else
                now = now->right;
        }
        return ans->val;
    }
} // namespace Treap

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    Treap::null = new Treap::node;
    Treap::node *root = Treap::null;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        int type, x;
        std::cin >> type >> x;
        if (type == 1) Treap::insert(root, x);
        if (type == 2) Treap::erase(root, x);
        if (type == 3) std::cout << Treap::rank(root, x) << "\n";
        if (type == 4) std::cout << Treap::find(root, x) << "\n";
        if (type == 5) std::cout << Treap::get_pre(x, root) << "\n";
        if (type == 6) std::cout << Treap::get_next(x, root) << '\n';
    }
    delete_tree(root);
    return 0;
}