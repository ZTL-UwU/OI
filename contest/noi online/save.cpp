#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 1e6 + 10;
struct data { int id; string name; int num; };
vector<string> ans_name;
vector<data> v;
string str, ptr;
int nextt[MAXN];
int last[MAXN];
int st[MAXN];
int top;
void get_next()
{
    int j = 0;
    int k = -1;
    nextt[0] = -1;
    while (j < ptr.size())
    {
        if (k == -1 || ptr[j] == ptr[k])
            nextt[++j] = ++k;
        else
            k = nextt[k];
    }
}
int kmp()
{
    int ans = 0;
    int i = 0;
    int j = 0;
    while (i < str.size())
    {
        if (j == -1 || str[i] == ptr[j])
        {
            last[i] = ++j;
            st[++top] = i++;
        }
        else
            j = nextt[j];
        if (j == ptr.size())
        {
            ans++;
            top -= ptr.size();
            j = last[st[top]];
        }
    }
    return ans;
}
bool cmp(data x, data y)
{
    if (x.num != y.num)
        return x.num > y.num;
    return x.id < y.id;
}
int main()
{
    ptr = "sos";
    get_next();
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++)
    {
        string name;
        cin >> name >> str;
        v.push_back((data){i, name, kmp()});
    }
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); i ++)
    {
        cout << v[i].name << " ";
        if (i != 0 && v[i + 1].num != v[i].num)
            break;
    }
    cout << "\n";
    cout << v[0].num << "\n";
    return 0;
}