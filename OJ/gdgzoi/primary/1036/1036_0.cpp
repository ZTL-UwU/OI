#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
struct data { int l, r; };
const int MAXN = 10000;
data tree[MAXN];
stack<string> input;
void clear()
{
    while (!input.empty())
        input.pop();
    for (int i = 0; i < MAXN; i++)
        tree[i].l = -1, tree[i].r = -1;
}
void output(int k)
{
    char tmp = k + 'A';
    cout << tmp;
    if (tree[k].l >= 0)
        output(tree[k].l);
    if (tree[k].r >= 0)
        output(tree[k].r);
}
void dfs(int p, int k)
{
    if (p > k)
    {
        if (tree[k].r < 0)
        {
            tree[k].r = p;
            return;
        }
        dfs(p, tree[k].r);
    }
    if (p < k)
    {
        if (tree[k].l < 0)
        {
            tree[k].l = p;
            return;
        }
        dfs(p, tree[k].l);
    }
}
int main()
{
    while (1)
    {
        clear();
        bool flag = 0;
        int num = 0;
        while (1)
        {
            string tmp;
            cin >> tmp;
            if (tmp == "*")
                break;
            if (tmp == "$")
            {
                flag = 1;
                break;
            }
            ++num;
            input.push(tmp);
        }
        int root = input.top()[0] - 'A';
        input.pop();
        for (int i = 0; i < num - 1; i++)
        {
            string str = input.top();
            for (int j = 0; j < str.size(); j++)
                dfs(str[j] - 'A', root);
            input.pop();
        }
        output(root);
        cout << "\n";
        if (flag)
            break;
    }
    return 0;
}