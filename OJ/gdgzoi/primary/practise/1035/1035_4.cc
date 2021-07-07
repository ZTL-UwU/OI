#include <iostream>
#include <queue>
using namespace std;
priority_queue<int, vector<int>, greater<int>> h;
int main()
{
    int n, k;
    char c;
    scanf("%d", &n);
    while (n--)
    {
        scanf("\n%c", &c);
        if (c == 'i')
        {
            scanf(" %d", &k);
            h.push(k);
        }
        if (c == 'q')
        {
            printf("%d\n", h.top());
            h.pop();
        }
    }
    return 0;
}