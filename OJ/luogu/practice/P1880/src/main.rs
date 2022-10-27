fn main() {
    const MAX_N: usize = 210;
    let mut dp1: [[i32; MAX_N]; MAX_N] = [[0; MAX_N]; MAX_N];
    let mut dp2: [[i32; MAX_N]; MAX_N] = [[0; MAX_N]; MAX_N];
    let mut a: [i32; MAX_N] = [0; MAX_N];
    let mut sum: [i32; MAX_N] = [0; MAX_N];

    let mut l1 = String::new();
    let mut l2 = String::new();
    std::io::stdin().read_line(&mut l1).unwrap();
    std::io::stdin().read_line(&mut l2).unwrap();
    let mut r1 = l1.trim().split(' ');
    let mut r2 = l2.trim().split(' ');

    let n: usize = r1.next().unwrap().parse().unwrap();

    for i in 1..n + 1 {
        a[i] = r2.next().unwrap().parse().unwrap();

        a[n + i] = a[i];
        sum[i] += sum[i - 1];
    }

    for len in 1..n {
        let mut i: usize = 1;
        loop {
            let j = i + len;

            dp2[i][j] = std::i32::MAX;
            for k in i..j {
                dp1[i][j] = max(dp1[i][j], dp1[i][k] + dp1[k + 1][j] + sum[j] - sum[i - 1]);
                dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k + 1][j] + sum[j] - sum[i - 1]);
            }

            i += 1;
            if j > 2 * n {
                break;
            }
        }
    }
}

fn min(a: i32, b: i32) -> i32 {
    if a > b {
        b
    } else {
        a
    }
}

fn max(a: i32, b: i32) -> i32 {
    if a > b {
        a
    } else {
        b
    }
}
