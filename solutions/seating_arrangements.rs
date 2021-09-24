#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

#[rustfmt::skip]
#[macro_use]
#[allow(dead_code)]
mod io {
    macro_rules! with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
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
    pub fn readln() -> String {
        let mut line = String::new();
        ::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
        line
    }
    macro_rules! readlns {
        ($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
            ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
                let line = line.unwrap();
                let it = line.split_whitespace();
                _read!(it; $($t),*)
            }).collect::<Vec<_>>()
        }};
    }
    macro_rules! readln {
        ($($t:tt),*) => {{ let line = io::readln(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
    }
    macro_rules! _read {
        ($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
        ($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
        ($it:ident; usize1) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
        ($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
        ($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
        ($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
        ($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
    }
    macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
    macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
}

// Reference: https://en.wikipedia.org/wiki/Fenwick_tree
pub struct FenwickTree<T> {
    n: usize,
    ary: Vec<T>,
    e: T,
}

impl<T: Clone + std::ops::AddAssign<T>> FenwickTree<T> {
    pub fn new(n: usize, e: T) -> Self {
        FenwickTree {
            n,
            ary: vec![e.clone(); n],
            e,
        }
    }
    pub fn accum(&self, mut idx: usize) -> T {
        let mut sum = self.e.clone();
        while idx > 0 {
            sum += self.ary[idx - 1].clone();
            idx &= idx - 1;
        }
        sum
    }
    /// performs data[idx] += val;
    pub fn add<U: Clone>(&mut self, mut idx: usize, val: U)
    where
        T: std::ops::AddAssign<U>,
    {
        let n = self.n;
        idx += 1;
        while idx <= n {
            self.ary[idx - 1] += val.clone();
            idx += idx & idx.wrapping_neg();
        }
    }
    /// Returns data[l] + ... + data[r - 1].
    pub fn sum(&self, l: usize, r: usize) -> T
    where
        T: std::ops::Sub<Output = T>,
    {
        self.accum(r) - self.accum(l)
    }
}

// $ rs-cp-batch seating_arrangements | diff seating_arrangements.out -
// $ cargo run seating_arrangements

///
/// 9/12/2021
///
/// 8:32-9:51 easy
/// 10:38 solved hard after contest
///
/// https://codeforces.com/blog/entry/94803
///
/// https://twitter.com/laycrs/status/1437102458375864320
/// https://twitter.com/n_vip/status/1437101222444498949
/// https://twitter.com/kzyKT_M/status/1437100412390100995
///

fn f(a: &Vec<i64>) -> i64 {
    let n = a.len();
    let mut a: Vec<_> = a.iter().enumerate().map(|(i, &x)| (x, n - i)).collect();
    a.sort();

    let mut bit = FenwickTree::new(n, 0i64);
    let mut res = 0;
    for (_, i) in a {
        let ii = n - i;
        res += bit.sum(0, ii);
        bit.add(ii, 1);
    }

    res
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);

    for _ in 0..t {
        let (n, m) = readln!(usize, usize);
        let a = readln!([i64]);
        dbgln!(n, m);
        let mut a: Vec<_> = a.iter().enumerate().map(|(i, &x)| (x, i)).collect();
        a.sort();

        let mut res = 0;
        for i in 0..n {
            let mut suba = Vec::with_capacity(m);
            for j in 0..m {
                suba.push((a[i * m + j].1, a[i * m + j].0));
            }
            suba.sort();
            let b = suba.iter().map(|(_, x)| *x).collect();
            res += f(&b);
        }

        puts!("{}", res);
    }
}
