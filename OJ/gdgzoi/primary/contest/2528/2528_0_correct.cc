#include <iostream>
#include <vector>
#include <queue>

const int MAX_DEPTH = 1e3;

std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> pq[MAX_DEPTH];

void output_inner(unsigned int depth, const std::string &name)
{
    for (auto _i = 0; _i < depth; _i++)
        std::cout << "|     ";
    std::cout << name << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::string str;

    int data_cnt = 1;
    bool done = true;

    unsigned int depth = 1;
    while (true)
    {
        std::cin >> str;
        if (str == "#")
            return 0;

        if (done)
        {
            std::cout << "DATA SET " << data_cnt << ":\n";
            std::cout << "ROOT\n";
            done = false;
        }

        if (str.front() == 'd')
        {
            output_inner(depth, str);
            depth++;
        }
        else if (str.front() == 'f')
            pq[depth].push(str);
        else
        {
            while (!pq[depth].empty())
            {
                output_inner(depth - 1, pq[depth].top());
                pq[depth].pop();
            }
            depth--;
        }

        if (str.front() == '*')
        {
            depth = 1;
            done = true;
            data_cnt++;
            std::cout << "\n";
        }
    }

    return 0;
}
