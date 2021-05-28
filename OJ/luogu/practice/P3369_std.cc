#include <bits/stdc++.h>
using std::vector;
const double alpha = 0.7;
int re;
struct node
{
    node *l, *r;
    int val, size = 0, cnt = 0;
    bool deleted;
    bool isbad()
    {
        if (this->cnt * alpha < this->l->cnt || this->cnt * alpha < this->r->cnt)
            return true;
        return false;
    }
    void push_up()
    {
        this->size = !this->deleted + this->l->size + this->r->size;
        this->cnt = 1 + this->l->cnt + this->r->cnt;
    }
};
node *null;
void get_subtree(node *now, vector<node *> &nodes)
{
    if (now == null)
        return;
    get_subtree(now->l, nodes);
    if (!now->deleted)
        nodes.push_back(now);
    get_subtree(now->r, nodes);
    if (now->deleted)
        delete now;
}
node *build(vector<node *> &nodes, int l, int r)
{
    if (l >= r)
        return null;
    int mid = (l + r) / 2;
    node *tree = nodes[mid];
    tree->l = build(nodes, l, mid);
    tree->r = build(nodes, mid + 1, r);
    tree->push_up();
    return tree;
}
void rebuild(node *&tree)
{
    re++;
    vector<node *> nodes;
    get_subtree(tree, nodes);
    tree = build(nodes, 0, nodes.size());
}
void insert(node *&tree, int val)
{
    if (tree == null)
    {
        tree = new node;
        tree->val = val;
        tree->cnt = 1;
        tree->size = 1;
        tree->l = null;
        tree->r = null;
        tree->deleted = false;
        return;
    }
    ++tree->cnt;
    ++tree->size;
    if (val >= tree->val)
        insert(tree->r, val);
    else
        insert(tree->l, val);
    if (tree->isbad())
        rebuild(tree);
}
int rank(node *now, int val)
{
    int ans = 1;
    while (now != null)
    {
        if (now->val >= val)
            now = now->l;
        else
        {
            ans += now->l->size + !now->deleted;
            now = now->r;
        }
    }
    return ans;
}
int kth(node *now, int rank)
{
    while (now != null)
    {
        if (!now->deleted && now->l->size + 1 == rank)
            return now->val;
        if (now->l->size >= rank)
            now = now->l;
        else
        {
            rank -= now->l->size + !now->deleted;
            now = now->r;
        }
    }
    return -1;
}
void erase(node *&tree, int rank)
{
    if (!tree->deleted && rank == tree->l->size + 1)
    {
        tree->deleted = true;
        --tree->size;
        return;
    }
    --tree->size;
    if (rank <= tree->l->size + !tree->deleted)
        erase(tree->l, rank);
    else
        erase(tree->r, rank - tree->l->size - !tree->deleted);
}
node *root;
int main()
{
    null = new node;
    root = null;
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
            insert(root, x);
        if (op == 2)
            erase(root, rank(root, x));
        if (op == 3)
            printf("%d\n", rank(root, x));
        if (op == 4)
            printf("%d\n", kth(root, x));
        if (op == 5)
            printf("%d\n", kth(root, rank(root, x) - 1));
        if (op == 6)
            printf("%d\n", kth(root, rank(root, x + 1)));
    }
}