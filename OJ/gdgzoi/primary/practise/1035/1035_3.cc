#include <iostream>
#include <vector>
using namespace std;
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
    int n, a;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        insert(a);
    }
    long long ans = 0;
    while (size >= 2)
    {
        int x = q[1];
        pop();
        int y = q[1];
        pop();
        ans += (x + y);
        insert(x + y);
    }

    cout << ans;
    return 0;
}