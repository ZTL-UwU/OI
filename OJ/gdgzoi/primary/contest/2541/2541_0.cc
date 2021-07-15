// WILEIVUQI

#include <iostream>
#include <vector>

int main()
{
    std::string input;
    std::cin >> input;

    std::vector<int> gap;
    for (std::size_t i = 0; i < input.size(); i++)
        if (input[i] == ',')
            gap.push_back(i);

    std::string str = input.substr(0, gap[0]);
    std::string ptr1 = input.substr(gap[0] + 1, gap[1] - gap[0] - 1);
    std::string ptr2 = input.substr(gap[1] + 1, input.size() - gap[1] + 1);

    int p1_first_end = -1;
    int p2_last_start = -1;
    for (std::size_t i = 0; i < str.size(); i++)
    {
        if (i <= str.size() - ptr1.size() && p1_first_end == -1)
        {
            for (std::size_t j = 0; j < ptr1.size(); j++)
            {
                if (ptr1[j] != str[i + j])
                    break;
                if (j == ptr1.size() - 1)
                    p1_first_end = i + j;
            }
        }

        if (i <= str.size() - ptr2.size())
        {
            for (std::size_t j = 0; j < ptr2.size(); j++)
            {
                if (ptr2[j] != str[i + j])
                    break;
                if (j == ptr2.size() - 1)
                    p2_last_start = i;
            }
        }
    }

    if (p2_last_start <= p1_first_end || p1_first_end == -1 || p2_last_start == -1)
        std::cout << "-1";
    else
        std::cout << p2_last_start - p1_first_end - 1;
    return 0;
}