echo "1 0 0" | ./input_maker.exe > CF571D.sample.1.in
./std_2.exe < CF571D.sample.1.in > CF571D.sample.1.out
echo "example 1"

echo "2 0 0" | ./input_maker.exe > CF571D.sample.2.in
./std_2.exe < CF571D.sample.2.in > CF571D.sample.2.out
echo "example 2"

for ((i=1;i<=20;i+=1)) {
    echo "0 1 0" | ./input_maker.exe > CF571D.1.$i.in
    ./std_2.exe < CF571D.1.$i.in > CF571D.1.$i.out
    echo "data.1.$i"
}

for ((i=1;i<=30;i+=1)) {
    echo "0 2 0" | ./input_maker.exe > CF571D.2.$i.in
    ./std_2.exe < CF571D.2.$i.in > CF571D.2.$i.out
    echo "data.2.$i"
}

for ((i=1;i<=108;i+=1)) {
    echo "0 3 0" | ./input_maker.exe > CF571D.3.$i.in
    ./std_2.exe < CF571D.3.$i.in > CF571D.3.$i.out
    echo "data.3.$i"
}

for ((i=1;i<=20;i+=1)) {
    echo "0 3 1" | ./input_maker.exe > CF571D.4.$i.in
    ./std_2.exe < CF571D.4.$i.in > CF571D.4.$i.out
    echo "data.4.$i"
}

for ((i=1;i<=20;i+=1)) {
    echo "0 3 2" | ./input_maker.exe > CF571D.5.$i.in
    ./std_2.exe < CF571D.5.$i.in > CF571D.5.$i.out
    echo "data.5.$i"
}
