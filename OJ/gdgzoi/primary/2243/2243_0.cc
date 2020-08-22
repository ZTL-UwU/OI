#include <iostream>
#include <vector>
using std::vector;
const double alpha = 0.7;
namespace tzy
{
    struct node
    {
        node *left;
        node *right;
        int val;
        int cnt = 0;
        int size = 0;
        bool deleted;
        void push_up();
        bool is_negative();
    };
    bool node::is_negative()
    {
        if (this->cnt * alpha < this->left->cnt
            || this->cnt * alpha < this->right->cnt)
            return true;
        return false;
    }
    void node::push_up()
    {
        this->size = !this->deleted + this->left->size + this->right->size;
        this->cnt = 1 + this->left->cnt + this->right->cnt;
    }
    node *null;
    inline void delete_tree(node *now)
    {
        if (now == null)
            return;
        delete_tree(now->left);
        delete_tree(now->right);
        delete now;
    }
    inline void get_subtree(node *now, vector<node *> &nodes)
    {
        if (now == null)
            return;
        get_subtree(now->left, nodes);
        if (!now->deleted)
            nodes.push_back(now);
        get_subtree(now->right, nodes);
        if (now->deleted)
            delete now;
    }
    inline node *build(int l, int r, vector<node *> &nodes)
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
    inline void rebuild(node *&tree)
    {
        vector<node *> nodes;
        get_subtree(tree, nodes);
        tree = build(0, nodes.size(), nodes);
    }
    inline void insert(node *&tree, int val)
    {
        if (tree == null)
        {
            tree == new node;
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
        if (tree->is_negative())
            rebuild(tree);
    }
    inline int rank(node *now, int val)
    {
        int ans = 1;
        while (now != null)
        {
            if (now->val >= val)
                now = now->left;
            else
            {
                ans += now->left->size + !now->deleted;
                now = now->right;
            }
        }
        return ans;
    }
    inline int find(node *now, int rank)
    {
        while (now != null)
        {
            if (!now->deleted && now->left->size + 1 == rank)
                return now->val;
            if (now->left->size >= rank)
                now = now->left;
            else
            {
                rank -= now->left->size + !now->deleted;
                now = now->right;
            }
        }
        return -1;
    }
}; // namespace tzy
using namespace tzy;
int main()
{
    null = new node;
    node *root = null;
    int n;
    std::cin >> n;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        std::cin >> x;
        insert(root, x);
        ans += std::min(x - find(root, rank(root, x) - 1), find(root, rank(root, x + 1)) - x);
    }
    std::cout << ans;
    delete_tree(root);
    return 0;
}