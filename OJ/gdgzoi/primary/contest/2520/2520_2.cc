#include <unordered_map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>

struct loop
{
    int line_num;
    char val_name;
    int o;
    bool will_enter;
};

int string_to_int(const std::string &str)
{
    std::stringstream ss;
    ss << str;

    int res;
    ss >> res;

    return res;
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
        int line_cnt;
        std::string o;

        std::cin >> line_cnt >> o;
        std::cin.get();

        std::vector<std::string> v;
        v.resize(line_cnt);
        for (int i = 0; i < line_cnt; i++)
            std::getline(std::cin, v[i]);

        std::stack<loop> st;
        std::unordered_map<int, bool> val_name_map;

        int tot_ans = 0;
        int ans = 0;
        bool flag = true;
        for (int i = 0; i < line_cnt; i++)
        {
            if (v[i][0] == 'E')
            {
                if (st.empty())
                {
                    std::cout << "ERR\n";
                    flag = false;
                    break;
                }
                else
                {
                    loop top = st.top();
                    st.pop();

                    // std::cout << "-" << top.line_num << " " << i << "\n";
                    val_name_map[top.val_name] = false;
                    if (top.line_num == i - 1)
                        ans = std::max(ans, top.o);
                    else
                        tot_ans += ans;
                    
                    if (i == line_cnt - 1)
                        tot_ans += ans;
                }
            }
            else
            {
                std::stringstream ss;
                ss << v[i];

                char op, val_name;
                std::string start;
                std::string end;
                ss >> op >> val_name >> start >> end;

                if (val_name_map[val_name] == true)
                {
                    std::cout << "ERR\n";
                    flag = false;
                    break;
                }
                val_name_map[val_name] = true;

                if (start[0] == 'n')
                {
                    st.push((loop){i, val_name, 0, false});
                    continue;
                }
                if (end[0] == 'n')
                {
                    st.push((loop){i, val_name, 1, true});
                    continue;
                }

                const int start_num = string_to_int(start);
                const int end_num = string_to_int(end);

                if (start_num >= end_num)
                    st.push((loop){i, val_name, 0, false});
                else
                    st.push((loop){i, val_name, 0, true});
            }
        }

        if (flag)
            std::cout << tot_ans << "\n";
    }
    return 0;
}