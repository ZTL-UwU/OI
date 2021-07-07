#include <iostream>
#include <queue>
#include <vector>
using namespace std;
queue<int> tmp;
int q[100005];
int size;
void insert(int n)
{
    q[++size] = n;
    int son = size;
    int fa = son / 2;
    while (q[fa] > q[son] && son != 1)
    {
        swap(q[fa], q[son]);
        son = fa;
        fa = son / 2;
    }
}
void pop()
{
    q[1] = q[size--];
    int fa = 1;
    int son = fa * 2;
    while (son <= size)
    {
        if (q[son] > q[son + 1] && son < size)
            son++;
        if (q[son] < q[fa])
        {
            swap(q[son], q[fa]);
            fa = son;
            son = fa * 2;
        }
        else
        {
            break;
        }
    }
}
int main()
{
    int n, k, p;
    cin >> n >> k >> p;
    int now = 2;
    for (int i = 1; i <= k; i++)
        tmp.push(i);
    vector<int> v;
    while (!tmp.empty())
    {
        if (now == 1)
            v.push_back(tmp.front());
        tmp.pop();
        for (int i = 0; i < p; i++)
        {
            tmp.push(tmp.front());
            tmp.pop();
        }
        now = now % n + 1;
    }
    for (int i = 0; i < v.size(); i++)
        insert(v[i]);
    for (int i = 0; i < v.size(); i++)
    {
        cout << q[1] << endl;
        pop();
    }
    return 0;
}