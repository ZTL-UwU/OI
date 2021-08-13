#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <set>
#include <utility>
using namespace std;

int main(int argc, char *argv[])
{
    FILE *f_in = fopen(argv[1], "r");   //测试输入
    FILE *f_out = fopen(argv[2], "r");  //测试输出
    FILE *f_user = fopen(argv[3], "r"); //用户输出
    int ret = 0;                        // AC=0,WA=1

    double a, b;
    fscanf(f_out, "%lf", &a);
    fscanf(f_user, "%lf", &b);
    if (fabs(a - b) > 1e-6) // WA
        ret = 1;

    fclose(f_in);
    fclose(f_out);
    fclose(f_user);
    return ret;
}
