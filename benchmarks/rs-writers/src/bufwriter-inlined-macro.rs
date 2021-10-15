// See https://github.com/rust-lang/rust/issues/35853 for with_dollar_sign!

#[allow(unused_macros)]
#[macro_use]
mod io {
    macro_rules! with_dollar_sign {
        ($($body:tt)*) => {
            macro_rules! __with_dollar_sign { $($body)* }
            __with_dollar_sign!($);
        }
    }

    macro_rules! setup_out {
        ($fn:ident,$fn_s:ident) => {
            use std::io::Write;
            let out = std::io::stdout();
            let mut out = ::std::io::BufWriter::new(out.lock());
            with_dollar_sign! { ($d:tt) => {
                macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
                macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
            }}
        };
    }

    // Debug output
    macro_rules! _epr {
        ($v:expr $(,)?) => {
            eprint!("{} = {:?}, ", stringify!($v), $v)
        };
    }
    macro_rules! dbgln {
        ($($val:expr),*) => {{
            eprint!("[{}:{}] ", file!(), line!());
            ($(_epr!($val)),*);
            eprintln!();
        }};
    }
}

// $ cargo build --release --bin bufwriter-inlined-macro
// $ time ./target/release/bufwriter-inlined-macro &>/dev/null
// ./target/release/bufwriter-inlined-macro &> /dev/null  0.12s user 0.00s system 97% cpu 0.124 total

fn main() {
    setup_out!(put, puts);

    for i in 0..1000_000 {
        put!("{} ", i);
    }

    for i in 0..1000_000 {
        puts!("{}", i);
    }
}
