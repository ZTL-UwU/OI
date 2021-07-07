rm -rf data*
clang++ ./genB.cc -o ./genB.exe
clang++ ./stdB.cc -o ./stdB.exe

for ((i=1; i<=10000; i+=1)) {
    ./genB.exe > ./data$i.in
    ./stdB.exe < ./data$i.in > ./data$i.ans
    ./2525_1.exe < ./data$i.in > /tmp/data$i.out

    if diff /tmp/data$i.out ./data$i.ans
    then
        echo "AC $i"
    else
        echo "WA $i"
        break
    fi
}