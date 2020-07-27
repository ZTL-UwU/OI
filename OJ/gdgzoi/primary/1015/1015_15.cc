#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1e6 + 10;
int a[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);
    int cnt = 0;
    int maxn = -1;
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == a[i + 1])
        {
            cnt++;
        }
        else
        {
            if (cnt >= maxn)
            {
                if (cnt > maxn)
                {
                    maxn = cnt;
                    ans.clear();
                }
                ans.push_back(a[i]);
            }
            cnt = 0;
        }
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}