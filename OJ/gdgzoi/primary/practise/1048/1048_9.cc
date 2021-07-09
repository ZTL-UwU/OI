// Wrong

#include <iostream>
#include <cstring>
#include <string>

const int MAX_CHARACTER = 40;
const int MAX_N = 100;
const int MAX_NODE = MAX_N * 100;

class Trie
{
private:
    int base[MAX_NODE][MAX_CHARACTER];
    bool end[MAX_NODE];
    int node_cnt = 0;

public:
    Trie()
    {
        std::memset(base, 0, sizeof(base));
        std::memset(end, false, sizeof(end));
    }

    void insert(std::string str)
    {
        int u = 0;
        for (std::size_t i = 0; i < str.size(); i++)
        {
            if (base[u][str[i] - 'a'] == 0)
                base[u][str[i] - 'a'] = ++node_cnt;
            u = base[u][str[i] - 'a'];
        }

        end[u] = true;
    }

    int pair_max_prefix(std::string passage)
    {
        int u = 0;
        int res = 0;
        for (std::size_t i = 0; i < passage.size(); i++)
        {
            if (!base[u][passage[i] - 'a'])
                return res + 1;
            u = base[u][passage[i] - 'a'];
            if (end[u])
            {
                u = 0;
                res = i;
            }
        }

        return passage.size();
    }
};

int main()
{
    int n, q;
    std::cin >> n >> q;

    Trie dictionary;
    for (int _i = 0; _i < n; _i++)
    {
        std::string str;
        std::cin >> str;
        dictionary.insert(str);
    }

    for (int _i = 0; _i < q; _i++)
    {
        std::string passage;
        std::cin >> passage;
        std::cout << dictionary.pair_max_prefix(passage) << "\n";
    }

    return 0;
}
