#include <iostream>
#include <map>
using namespace std;
map<long long, string> shortest, longest;
map<string, long long> cnt;
long long st;
int n;
int main()
{
    string str;
    cin >> str;
    int m = str.size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j <= m - i; j++)
        {
            st = 0;
            string sub = str.substr(i, j);
            for (int k = 0; k <= m - j; k++)
                if (str.substr(k, j) == sub)
                    st |= (1LL << (k + j));
            if (!shortest[st].length() || j < shortest[st].length())
                shortest[st] = sub;
            if (j > longest[st].length())
                longest[st] = sub;
            cnt[sub] = st;
        }
    }
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        long long tmp = cnt[s];
        cout << shortest[cnt[s]] << ' ' << longest[cnt[s]] << ' ';
        for (int j = 0; j < 50; j++)
            if ((1LL << j) & tmp)
                cout << j << ' ';
        cout << "\n";
    }
    return 0;
}