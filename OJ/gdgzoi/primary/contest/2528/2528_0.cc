#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 1e6;
const int ROOT = 0;

struct node
{
    std::size_t id;
    std::string name;
    char type;
};

std::vector<node> t[MAX_N];
std::string name[MAX_N];
std::size_t node_cnt = 0;

std::size_t get_end(std::size_t l, std::size_t r, const std::vector<std::string> &input)
{
    int s = 0;
    for (auto i = l; i < r; i++)
    {
        if (input[i][0] == 'd')
            s++;
        else if (input[i][0] == ']')
            s--;
        if (s == 0)
            return i;
    }

    return 0;
}

void dfs(int u, std::size_t l, std::size_t r, const std::vector<std::string> &input)
{
    for (auto i = l; i < r; i++)
    {
        if (input[i][0] == 'f' || input[i][0] == 'd')
        {
            t[u].push_back({++node_cnt, input[i], input[i][0]});
            name[node_cnt] = input[i];
            if (input[i][0] == 'd')
            {
                const auto end = get_end(i, r, input);
                if (end == 0)
                    continue;
                dfs(node_cnt, i + 1, end, input);
                i = end;
            }
        }
    }
}

void output(int u, int depth)
{
    for (int i = 0; i < depth; i++)
        std::cout << "|     ";
    std::cout << name[u] << "\n";

    std::vector<std::pair<std::string, int>> files;
    for (auto v : t[u])
        if (v.type == 'f')
            files.push_back({name[v.id], v.id});
    std::sort(files.begin(), files.end(),
              [](std::pair<std::string, int> a, std::pair<std::string, int> b) -> bool { return a.first < b.first; });

    for (auto v : t[u])
        if (v.type == 'd')
            output(v.id, depth + 1);
    for (auto v : files)
        output(v.second, depth);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::string str;
    int set = 0;
    while (true)
    {
        std::vector<std::string> input;
        for (int i = 0; i < MAX_N; i++)
            t[i].clear();

        std::getline(std::cin, str);
        if (str == "#")
            return 0;

        if (set != 0)
            std::cout << "\n";
        std::cout << "DATA SET " << ++set << ":\n";
        while (true)
        {
            if (str == "*")
            {
                break;
                std::cin.get();
            }
            input.push_back(str);
            std::getline(std::cin, str);
        }

        name[ROOT] = "ROOT";
        dfs(ROOT, 0, input.size(), input);
        output(ROOT, 0);
    }
    return 0;
}
