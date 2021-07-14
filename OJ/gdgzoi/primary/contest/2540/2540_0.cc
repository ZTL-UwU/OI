#include <iostream>
#include <string>
#include <queue>

struct Word
{
    std::string content;
    unsigned int cnt;

    bool operator<(const Word &x) const
    {
        if (this->cnt == x.cnt)
            return this->content > x.content;
        return this->cnt > x.cnt;
    }
};

const int MAX_CHARACTER = 30;

std::priority_queue<Word> dictionary[MAX_CHARACTER];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int k, n;
    std::cin >> k >> n;

    for (int _i = 0; _i < k; _i++)
    {
        std::string str;
        std::cin >> str;

        dictionary[str[0] - 'a'].push({str, 0});
    }

    for (int _i = 0; _i < n; _i++)
    {
        char ch;
        std::cin >> ch;
        const auto content = dictionary[ch - 'a'].top().content;
        const auto cnt = dictionary[ch - 'a'].top().cnt;
        std::cout << content << "\n";
        dictionary[ch - 'a'].pop();
        dictionary[ch - 'a'].push({content, cnt + 1});
    }
    return 0;
}
