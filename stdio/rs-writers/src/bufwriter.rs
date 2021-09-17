use std::io::{Write, BufWriter};

macro_rules! puts {
	($($format:tt)*) => {{
        let out = std::io::stdout();
        let mut out = BufWriter::new(out.lock());
        let _ = write!(out,$($format)*);
    }}
}

// $ cargo build --release --bin bufwriter
// $ time ./target/release/bufwriter &>/dev/null
// ./target/release/bufwriter &> /dev/null  0.74s user 0.31s system 82% cpu 1.266 total

fn main() {
    for i in 0..1000_000 {
        puts!("{} ", i);
    }

    for i in 0..1000_000 {
        puts!("{}\n", i);
    }
}
