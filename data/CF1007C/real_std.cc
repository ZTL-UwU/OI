#include "guess.h"
#include <bits/stdc++.h>

using namespace std;

void solve(long long n)
{
    long long x = 0, y = 0, jump_x = 1, jump_y = 1;
    int steps = 0;

    while (1)
    {
        steps++;
        jump_x = min(jump_x, n - x);
        jump_y = min(jump_y, n - y);

        int res = query(x + jump_x, y + jump_y);

        if (res == 0 || res == -1)
            return;

        if (res == 1)
        {
            x += jump_x;
            jump_x *= 2;
        }
        else if (res == 2)
        {
            y += jump_y;
            jump_y *= 2;
        }
        else if (res == 3)
        {
            jump_x /= 2;
            jump_y /= 2;
            jump_x = max(jump_x, 1LL);
            jump_y = max(jump_y, 1LL);
        }
    }

    return;
}