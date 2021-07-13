#include <iostream>
#include <string>

const int MAX_N = 1e6 + 10;

class KMP
{
private:
    std::string ptr;
    int next[MAX_N];

public:
    KMP(std::string ptr)
    {
        this->ptr = ptr;

        int p1 = 0;
        int p2 = -1;
        next[0] = -1;
        while (p1 < ptr.size())
        {
            if (p2 == -1 || ptr[p1] == ptr[p2])
                next[++p1] = ++p2;
            else
                p2 = next[p2];
        }
    }

    bool find(std::string str)
    {
        int p1 = 0;
        int p2 = 0;
        while (p1 < str.size())
        {
            if (p2 == -1 || str[p1] == ptr[p2])
            {
                p1++;
                p2++;
            }
            else
                p2 = next[p2];

            if (p2 == ptr.size())
                return true;
        }

        return false;
    }
};

int main()
{
    std::string s1;
    std::string s2;

    std::cin >> s1 >> s2;
    int n = s1.size();
    s1 = s1 + s1;

    KMP s(s2);
    if (s.find(s1))
    {
        int i = 0;
        int j = 1;
        int k = 0;
        while (i < n && j < n && k < n)
        {
            if (s1[i + k] == s1[j + k])
                k++;
            else
            {
                if (s1[i + k] > s1[j + k])
                    i += k + 1;
                else
                    j += k + 1;
                if (i == j)
                    j++;
                k = 0;
            }
        }

        std::cout << "Yes\n";
        for (int l = std::min(i, j); l < std::min(i, j) + n; l++)
            std::cout << s1[l];
    }
    else
        std::cout << "No";

    return 0;
}