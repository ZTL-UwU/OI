clang++ ./1033_1_data_maker.cc -o ./1033_1_data_maker.exe
clang++ ./1033_1.cc -o ./1033_1.exe
clang++ ./1033_1_std.cc -o ./1033_1_std.exe

for ((i = 0; i < 10; i++)) {
    zsh ./1033_1_checker.zsh
}