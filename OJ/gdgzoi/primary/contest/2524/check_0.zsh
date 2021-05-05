#!zsh

python3 -u ./check_0.py > test_0.in
g++ ./2524_0.cc -o ./2524_0.exe --std=c++11

./2524_0.exe < test_0.in > test_0.out
