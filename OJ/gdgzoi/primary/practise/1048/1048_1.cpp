#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
using namespace std;
const int MAXN = 1e5 + 10;
multiset<string> h;
vector<string> tmp;
set<string> res;
string s[MAXN];
bool cmp(string a, string b)
{
    if (h.count(a) != h.count(b))
        return h.count(a) > h.count(b);
    return a < b;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        h.insert(s[i]);
    }
    for (int i = 0; i < n; i++)
        if (h.count(s[i]) >= 3)
            res.insert(s[i]);
    cout << res.size() << "\n";
    for (auto iter = res.begin(); iter != res.end(); iter++)
        tmp.push_back(*iter);
    sort(tmp.begin(), tmp.end(), cmp);
    for (int i = 0; i < tmp.size(); i++)
        cout << tmp[i] << "\n";
    return 0;
}