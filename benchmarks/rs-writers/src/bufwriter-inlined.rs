use std::io::{BufWriter, Write};

// $ cargo build --release --bin bufwriter-inlined
// $ time ./target/release/bufwriter-inlined &>/dev/null
// ./target/release/bufwriter &> /dev/null  0.11s user 0.00s system 43% cpu 0.257 total

fn main() {
    let out = std::io::stdout();
    let mut out = BufWriter::new(out.lock());
    macro_rules! puts {($($format:tt)*) => (let _ = write!(out,$($format)*););}

    for i in 0..1000_000 {
        puts!("{}\n", i);
    }

    /*for i in 0..1000_000 {
        puts!("{}\n", i);
    }*/
}
