#[allow(unused_imports)]
use std::cmp::*;
#[allow(unused_imports)]
use std::collections::*;
use std::io::{Write, BufWriter};

macro_rules! with_dollar_sign { ($($body:tt)*) => {
    macro_rules! __with_dollar_sign { $($body)* }
    __with_dollar_sign!($);
}}
macro_rules! setup_out { ($fn:ident,$fn_s:ident) => {
    let out = std::io::stdout();
    let mut out = BufWriter::new(out.lock());
    with_dollar_sign! { ($d:tt) => {
        #[allow(unused_macros)]
        macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
        #[allow(unused_macros)]
        macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
    }}
};}
// https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8
pub fn readln() -> String {
	let mut line = String::new();
	::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
	line
}
#[allow(unused_macros)]
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
#[allow(unused_macros)]
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

// $ rs-cp-batch {$__PROB__} | diff {$__PROB__}.out -
// $ cargo run {$__PROB__}

///
/// {$__DATE__}
///
/// {$__TIME__}-
///
fn main() {
    setup_out!(put,puts);

    let n = readln!(usize);
    let a = readln!([i64]);

    puts!("{}", n);
}
