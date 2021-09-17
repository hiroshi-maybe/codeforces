// $ cargo build --release --bin print
// $ ./target/release/print &> /dev/null  0.59s user 0.27s system 71% cpu 1.184 total
fn main() {
    for i in 0..1000_000 {
        print!("{}\n", i);
    }

    /*    for i in 0..1000_000 {
        println!("{}", i);
    }*/
}
