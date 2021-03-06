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
    int k = 0;
    while (not end[u] and k < str.size())
        u = trie[u][str[k++] - 'A'];

    if (k == str.size())
        return true;
    return false;
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::string op, str;
        std::cin >> op >> str;
        
        if (op == "insert")
            insert(str);
        else
            std::cout << find(str);
    }
    return 0;
}