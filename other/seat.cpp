#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
int ans[7][7];
bool used[38];
void seat()
{
    for (int i = 0; i < 6; i ++)
    {
        for (int j = 0; j < 6; j ++)
        {
            while (1)
            {
                int k = rand() % 37 + 1;
                if (!used[k])
                {
                    ans[i][j] = k;
                    used[k] = true;
                    break;
                }
            }
        }
    }
}
int main()
{
    srand(79666);
    seat();
    for (int i = 0; i < 6; i ++)
    {
        for (int j = 0; j < 6; j ++)
        {
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}