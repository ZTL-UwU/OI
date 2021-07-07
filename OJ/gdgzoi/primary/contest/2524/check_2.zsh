#!zsh

clang++ ./check_2.cc -o ./check_2.exe -O2
./check_2.exe > test_2.in
clang++ ./2524_2.cc -o 2524_2.exe --std=c++11 -O2
./2524_2.exe < test_2.in > test_2.out