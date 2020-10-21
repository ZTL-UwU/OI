#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN_N = 1e4 + 10;
const int MAXN = 1e6 + 10;
int trie[MAXN_N][30];
int fail[MAXN_N];
int endf[MAXN_N];
int num;
void clear()
{
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));
    memset(endf, 0, sizeof(endf));
    num = 0;
}
void insert(string s)
{
    int u = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int ch = s[i] - 'a';
        if (!trie[u][ch])
            trie[u][ch] = ++num;
        u = trie[u][ch];
    }
    endf[u] += 1;
}
void get_fail()
{
    queue<int> q;
    for (int i = 0; i < 26; i++)
    {
        int v = trie[0][i];
        if (v)
        {
            q.push(v);
            fail[v] = 0;
        }
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; i++)
        {
            int v = trie[u][i];
            if (v)
            {
                fail[v] = trie[fail[u]][i];
                q.push(v);
            }
            else
                trie[u][i] = trie[fail[u]][i];
        }
    }
}
int query(string str)
{
    int u = 0;
    int ans = 0;
    for (int i = 0; i < str.size(); i++)
    {
        int ch = str[i] - 'a';
        u = trie[u][ch];
        int v = u;
        while (v && endf[v] != -1)
        {
            ans += endf[v];
            endf[v] = -1;
            v = fail[v];
        }
    }
    return ans;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        clear();
        string str;
        int n;
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            insert(s);
        }
        cin >> str;
        get_fail();
        // for (int i = 0; i < num; i++)
        //     cout << fail[i] << " ";
        // cout << "\n";
        cout << query(str) << "\n";
    }
    return 0;
}