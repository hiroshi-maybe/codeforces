#[allow(unused_imports)]
use std::collections::*;
#[allow(unused_imports)]
use std::io::{self, prelude::*};
use std::str;

// https://codeforces.com/contest/1517/submission/113985996
struct Scanner<R> {
    reader: R,
    buf_str: Vec<u8>,
    buf_iter: str::SplitWhitespace<'static>,
}
impl<R: BufRead> Scanner<R> {
    fn new(reader: R) -> Self {
        Self { reader, buf_str: vec![], buf_iter: "".split_whitespace() }
    }
    fn token<T: str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_until(b'\n', &mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe {
                let slice = str::from_utf8_unchecked(&self.buf_str);
                std::mem::transmute(slice.split_whitespace())
            }
        }
    }
}

// target/release/ebtechscanner < ../1e6int.input  0.05s user 0.01s system 22% cpu 0.261 total
fn main() {
    let (stdin, _) = (io::stdin(), io::stdout());
    let mut scan = Scanner::new(stdin.lock());
    let n = scan.token::<usize>();
    let mut a = Vec::with_capacity(n);
    for _ in 0..n {
        a.push(scan.token::<i64>());
    }

    println!("{}", n);
}
