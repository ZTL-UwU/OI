echo "1 0 0" | ./input_maker.exe > CF571D.sample.1.in
./std_2.exe < CF571D.sample.1.in > CF571D.sample.1.out

echo "2 0 0" | ./input_maker.exe > CF571D.sample.2.in
./std_2.exe < CF571D.sample.2.in > CF571D.sample.2.out

echo "1 0 0" | ./input_maker.exe > CF571D.sample.3.in
./std_2.exe < CF571D.sample.3.in > CF571D.sample.3.out

echo "2 0 0" | ./input_maker.exe > CF571D.sample.4.in
./std_2.exe < CF571D.sample.4.in > CF571D.sample.4.out

echo "1 0 0" | ./input_maker.exe > CF571D.sample.5.in
./std_2.exe < CF571D.sample.5.in > CF571D.sample.5.out

echo "2 0 0" | ./input_maker.exe > CF571D.sample.6.in
./std_2.exe < CF571D.sample.6.in > CF571D.sample.6.out

for ((i=1;i<=60;i+=1)) {
    echo "0 1 0" | ./input_maker.exe > CF571D.1.$i.in
    ./std_2.exe < CF571D.1.$i.in > CF571D.1.$i.out
}

for ((i=1;i<=90;i+=1)) {
    echo "0 2 0" | ./input_maker.exe > CF571D.2.$i.in
    ./std_2.exe < CF571D.2.$i.in > CF571D.2.$i.out
}

for ((i=1;i<=384;i+=1)) {
    echo "0 3 0" | ./input_maker.exe > CF571D.3.$i.in
    ./std_2.exe < CF571D.3.$i.in > CF571D.3.$i.out
}

for ((i=1;i<=60;i+=1)) {
    echo "0 3 1" | ./input_maker.exe > CF571D.4.$i.in
    ./std_2.exe < CF571D.4.$i.in > CF571D.4.$i.out
}
