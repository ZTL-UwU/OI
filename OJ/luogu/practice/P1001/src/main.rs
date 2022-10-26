fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let mut cin = input.trim().split(' ');

    let a: i32 = cin.next().unwrap().parse().unwrap();
    let b: i32 = cin.next().unwrap().parse().unwrap();

    println!("{}", a + b);
}
