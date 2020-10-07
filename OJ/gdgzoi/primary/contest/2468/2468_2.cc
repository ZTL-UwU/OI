#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>

const int MAXN = 4e5;
const int MAX_CHARACTER = 2;

int trie[MAXN][MAX_CHARACTER];
int trie_str_end[MAXN];
int trie_node;

int fail[MAXN];

inline void init()
{
    std::memset(trie_str_end, 0, sizeof(trie_str_end));
    std::memset(trie, 0, sizeof(trie));
    std::memset(fail, 0, sizeof(fail));
    trie_node = 0;
}

// Trie
inline void insert(std::string &str)
{
    int u = 0;
    for (auto i : str)
    {
        int son = i - 'a';

        if (trie[u][son] == 0)
            trie[u][son] = ++trie_node;
        u = trie[u][son];
    }

    trie_str_end[u] = str.size();
}

// AC Automata
inline void build()
{
    std::queue<int> q;

    // Init
    for (int i = 0; i < MAX_CHARACTER; i++)
    {
        int v = trie[0][i];
        if (v)
        {
            fail[v] = 0;
            q.push(v);
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < MAX_CHARACTER; i++)
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

inline int query(std::string &str)
{
    int u = 0;
    int ans = 0;

    for (auto i : str)
    {
        int son = i - 'a';
        u = trie[u][son];

        int v = u;
        while (v != 0 and trie_str_end[v] != -1)
        {
            ans = std::max(ans, trie_str_end[v]);
            trie_str_end[v] = -1;
            v = fail[v];
        }
    }

    return ans;
}

inline int AC_automata(std::vector<std::string> &ptr_list, std::string &str)
{
    for (auto i : ptr_list)
        insert(i);

    build();
    return query(str);
}

inline int solve(std::string &s, std::string &t, int l, int r)
{
    s = s.substr(l, r - l + 1);
    if (t.size() < s.size())
        std::swap(s, t);

    std::vector<std::string> substr_list;
    for (int i = 0; i < s.size(); i++)
        for (int j = 1; j <= s.size() - i; j++)
            substr_list.push_back(s.substr(i, j));

    return AC_automata(substr_list, t);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::string s, t;
    std::cin >> s >> t;

    int q;
    std::cin >> q;
    while (q--)
    {
        init();
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        std::cout << solve(s, t, l, r) << "\n";
    }
    return 0;
}