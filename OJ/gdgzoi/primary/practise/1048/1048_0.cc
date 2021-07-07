#include <bits/c++config.h>
#include <ios>
#include <iostream>

const int MAX_ALPHABAT = 26;
const int MAX_N = 1e6 + 10;
const int ROOT = 0;

int trie[MAX_N][MAX_ALPHABAT];
bool end[MAX_N];
int time_stamp;

void insert(std::string str)
{
    int u = ROOT;
    for (auto ch : str)
    {
        if (trie[u][ch - 'A'] == 0)
            trie[u][ch - 'A'] = ++time_stamp;
        u = trie[u][ch - 'A'];
    }

    end[u] = true;
}

bool find(std::string str)
{
    int u = 0;
    std::size_t k = 0;
    while (k < str.size() and trie[u][str[k] - 'A'] != 0)
        u = trie[u][str[k++] - 'A'];

    if (k == str.size() and end[u])
        return true;
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string op, str;
        std::cin >> op >> str;

        if (op == "insert")
            insert(str);
        else
            std::cout << (find(str) ? "yes" : "no") << "\n";
    }
    return 0;
}