#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::io::{BufWriter, Write};

macro_rules! with_dollar_sign { ($($body:tt)*) => {
	macro_rules! __with_dollar_sign { $($body)* }
	__with_dollar_sign!($);
}}
macro_rules! setup_out {
    ($fn:ident,$fn_s:ident) => {
        let out = std::io::stdout();
        let mut out = BufWriter::new(out.lock());
        with_dollar_sign! { ($d:tt) => {
            macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
            macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
        }}
    };
}
pub fn readln() -> String {
    let mut line = String::new();
    ::std::io::stdin()
        .read_line(&mut line)
        .unwrap_or_else(|e| panic!("{}", e));
    line
}
macro_rules! readlns {
	($($t:tt),*; $n:expr) => {{
		let stdin = ::std::io::stdin();
		let ret = ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
			let line = line.unwrap();
			let mut it = line.split_whitespace();
			_read!(it; $($t),*)
		}).collect::<Vec<_>>();
		ret
	}};
}
macro_rules! readln {
	($($t:tt),*) => {{
		let line = readln();
		#[allow(unused_mut)]
		let mut it = line.split_whitespace();
		_read!(it; $($t),*)
	}};
}
macro_rules! _read {
	($it:ident; [char]) => { _read!($it; String).chars().collect::<Vec<_>>() };
	($it:ident; [u8]) => { Vec::from(_read!($it; String).into_bytes()) };
	($it:ident; usize1) => { it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1 };
	($it:ident; [usize1]) => { $it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>() };
	($it:ident; [$t:ty]) => { $it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>() };
	($it:ident; $t:ty) => { $it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e)) };
	($it:ident; $($t:tt),+) => { ($(_read!($it; $t)),*) };
}

// $ rs-cp-batch take_a_guess | diff take_a_guess.out -
// $ cargo run --bin take_a_guess

///
/// 9/17/2021
///
/// 20:05-22:58 First AC for interactive problem with Rust
///

const A: &'static [i64] = &[1, 6, 4, 2, 3, 5, 4];
const DBG: bool = false;

enum Command {
    And,
    Or,
}

fn ans(res: i64) {
    println!("finish {}", res);
}

fn ask(c: Command, i: usize, j: usize) -> i64 {
    let s = match c {
        Command::And => "and",
        Command::Or => "or",
    };
    println!("{} {} {}", s, i + 1, j + 1);
    if DBG {
        let x = A[i];
        let y = A[j];
        return match c {
            Command::And => x & y,
            Command::Or => x | y,
        };
    }
    let v = readln!(i64);
    v
}

fn ask_sum(i: usize, j: usize) -> i64 {
    let and = ask(Command::And, i, j);
    let or = ask(Command::Or, i, j);
    and + or
}

fn main() {
    setup_out!(put, puts);

    let (n, k) = readln!(usize, usize);
    dbg!(n, k);

    let ab = ask_sum(0, 1);
    let ac = ask_sum(0, 2);
    let bc = ask_sum(1, 2);

    let mut res = vec![-1i64; n];
    let a0 = (ac + ab - bc) / 2;
    let a1 = ab - a0;
    let a2 = ac - a0;
    res[0] = a0;
    res[1] = a1;
    res[2] = a2;
    for i in 3..n {
        let x = ask_sum(i, 0);
        res[i] = x - a0;
    }
    res.sort();

    ans(res[k - 1]);
}
