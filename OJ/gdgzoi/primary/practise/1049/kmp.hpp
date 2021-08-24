#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <string>

const int MAX_N = 1e6 + 10;

class KMP
{
private:  
    int next[MAX_N];
    std::string ptr;

public:
    KMP(std::string ptr)
    {
        this->ptr = ptr;
        next[0] = -1;

        int p1 = 0;
        int p2 = -1;

        while (p1 < ptr.size())
        {
            if (p2 == -1 || ptr[p1] == ptr[p2])
                next[p1++] = p2++;
            else
                p2 = next[p2];
        }
    }

    std::size_t search(std::string str)
    {
        int p1 = 0;
        int p2 = -1;

        while (p1 < str.size())
        {
            if (p2 == -1 || ptr[p1] == ptr[p2])
            {
                p1++;
                p2++;
            }
            else
                p2 = next[p2];

            if (p2 == this->ptr.size())
                return p1 - this->ptr.size() + 1;
        }

        return -1;
    }
};

#endif