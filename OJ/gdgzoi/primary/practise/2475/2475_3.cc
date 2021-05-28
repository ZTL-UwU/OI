#include <iostream>
#define endl '\n'
using namespace std;
int n;
int m = -0x7fffffff;
int tree[100000];
int star[100000];
int ans[100000];
inline int lowbit(int x) { return x & (-x); }
void add(int x)
{
    while (x <= m)
    {
        tree[x]++;
        x += lowbit(x);
    }
}
inline int sum(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
int main()
{
    cin >> n;
    int dum;
    for (int i = 0; i < n; i++)
        cin >> star[i] >> dum, m = max(m, star[i] + 1);
    for (int i = 0; i < n; i++)
    {
        int grade = sum(star[i] + 1);
        add(star[i] + 1);
        ans[grade]++;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << endl;
    return 0;
}