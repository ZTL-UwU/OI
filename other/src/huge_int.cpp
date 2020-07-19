#include <iostream>
#include "huge_int.hpp"
using namespace std;
int main()
{
    huge_int a, b;
    cin >> a >> b;
    bool tmp = a != b;
    cout << tmp;
    return 0;
}