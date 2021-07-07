#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Line
{
    char op, val_name;
    std::string start_str, end_str;
};

std::vector<Line> line;
std::unordered_map<int, bool> val_name_map;

int string_to_int(const std::string &str)
{
    std::stringstream ss;
    ss << str;
    int res = 0;
    ss >> res;

    return res;
}

int read_block(int l, int r)
{
    int res = 0;
    int max = 0;

    if (val_name_map[line[l].val_name])
        return -2;
    val_name_map[line[l].val_name] = true;

    if (line[l].start_str[0] == 'n' && line[l].end_str[0] != 'n')
        res = -1;
    else if (line[l].start_str[0] == 'n' && line[l].end_str[0] == 'n')
        res = 0;
    else if (line[l].end_str[0] == 'n')
        res = 1;
    else
    {
        const int start_num = string_to_int(line[l].start_str);
        const int end_num = string_to_int(line[l].end_str);

        if (start_num <= end_num)
            res = 0;
        else
            res = -1;
    }

    bool enterable = res != -1;

    int f_num = 0;
    int last_l = l;
    for (int i = l + 1; i <= r - 1; i++)
    {
        if (line[i].op == 'F')
            f_num++;
        else
        {
            f_num--;

            if (f_num == 0)
            {
                const int ret = read_block(last_l + 1, i);
                if (ret == -2)
                    return -2;

                val_name_map[line[last_l + 1].val_name] = false;
                max = std::max(max, ret);
                last_l = i;
            }
            else if (f_num == -1)
                return -2;
        }
    }

    if (f_num != 0)
        return -2;

    if (!enterable)
        return 0;

    return res + max;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        line.clear();
        val_name_map.clear();

        int line_cnt;
        std::string O;
        std::cin >> line_cnt >> O;
        std::cin.get();

        line.push_back((Line){'F', '#', "0", "0"});
        for (int i = 0; i < line_cnt; i++)
        {
            std::string tmp;
            std::getline(std::cin, tmp);

            std::stringstream ss;
            ss << tmp;
            char op, val_name;
            std::string start_str, end_str;
            ss >> op >> val_name >> start_str >> end_str;

            line.push_back((Line){op, val_name, start_str, end_str});
        }
        line.push_back((Line){'E', '#', "0", "0"});

        if (line[line.size() - 2].op == 'F')
        {
            std::cout << "ERR\n";
            continue;
        }

        if (line[1].op == 'E')
            std::cout << "ERR\n";
        else
        {
            const int ret = read_block(0, line.size() - 1);
            if (ret == -2)
            {
                std::cout << "ERR\n";
                continue;
            }

            int think = 0;
            for (std::size_t i = 0; i < O.size(); i++)
            {
                if (O[i] == '1')
                {
                    think = 0;
                    break;
                }
                if (O[i] == '^')
                {
                    think = string_to_int(O.substr(i + 1, O.size() - i - 2));
                    break;
                }
            }

            std::cout << (ret == think ? "Yes" : "No") << "\n";
        }
    }
    return 0;
}
