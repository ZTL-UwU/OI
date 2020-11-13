#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <cmath>

const int MAXN = 2e2;

class MAT
{
public:
    MAT()
    {
        this->val.resize(MAXN);
        for (int i = 0; i < MAXN; i++)
            this->val[i].resize(MAXN);
    }

    std::vector<std::vector<double>> val;
    int size;
};

inline void gauss(MAT &mat)
{
    for (int i = 0; i < mat.size; i++)
    {
        int max_row = i;
        for (int j = i + 1; j < mat.size; j++)
            if (std::fabs(mat.val[j][i]) > std::fabs(mat.val[max_row][i]))
                max_row = j;

        for (int j = 0; j < mat.size + 1; j++)
            std::swap(mat.val[i][j], mat.val[max_row][j]);

        if (mat.val[i][i] == 0)
        {
            std::cout << "No Solution";
            return;
        }

        for (int j = 0; j < mat.size; j++)
            if (j != i)
                for (int k = i + 1; k < mat.size + 1; k++)
                    mat.val[j][k] -= mat.val[j][i] * (mat.val[i][k] / mat.val[i][i]);
    }

    std::cout.setf(std::ios::fixed);
    for (int i = 0; i < mat.size; i++)
        std::cout << std::setprecision(2) << mat.val[i][mat.size] / mat.val[i][i] << "\n";
}

int main()
{
    MAT mat;
    std::cin >> mat.size;

    for (int i = 0; i < mat.size; i++)
        for (int j = 0; j < mat.size + 1; j++)
            std::cin >> mat.val[i][j];

    gauss(mat);
    return 0;
}