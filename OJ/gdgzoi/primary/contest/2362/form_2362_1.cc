#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <string>

int main()
{
    std::ofstream ans("ans.ans");
    for (int i = 2; i <= 10000; i++)
    {
        if (i == 90)
            continue;
        std::cout << i << " : ";
        std::ofstream ofs("in.in");
        ofs << i;
        ofs.close();

        std::system("./2362_1.exe");

        std::string res;
        std::ifstream ifs("out.out");
        getline(ifs, res);
        std::cout << res << "\n";
        ans << res << "\n";
        ifs.close();
    }
    ans.close();
}