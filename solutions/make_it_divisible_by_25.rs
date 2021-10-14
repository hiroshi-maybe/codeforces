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
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
	}
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
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
}

// $ rs-cp-batch make_it_divisible_by_25 | diff make_it_divisible_by_25.out -
// $ cargo run --bin make_it_divisible_by_25

///
/// 10/13/2021
///
/// 7:50-8:17 AC
///

const INF: usize = 1000;
fn f(s: &Vec<char>, p: &Vec<char>) -> usize {
    let mut j = 0;
    let mut lastp = INF;
    for i in 0..s.len() {
        if j < p.len() && s[i] == p[j] {
            j += 1;
            lastp = i;
        }
    }
    if j == p.len() {
        //dbgln!(s, p, lastp);
        lastp + 1 - p.len()
    } else {
        INF
    }
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(i32);
    for _ in 0..t {
        let mut s = readln!([char]);
        s.reverse();
        let mut res = INF;
        res = min(res, f(&s, &vec!['0', '0']));
        res = min(res, f(&s, &vec!['5', '2']));
        res = min(res, f(&s, &vec!['0', '5']));
        res = min(res, f(&s, &vec!['5', '7']));
        if res == INF {
            res = s.len();
        }

        puts!("{}", res);
    }
}
