use proconio::input;

// cargo build --bin proconio --release
// target/release/proconio < ../1e6int.input  0.04s user 0.01s system 18% cpu 0.302 total
fn main() {
    input! {
        n: usize,
        a: [i64; n],
    }

    println!("{}, {}", n, a[100]);
}
