#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::process::exit;

// $ cp-batch guess_the_string | diff guess_the_string.out -
// $ cargo run --bin guess_the_string

///
/// 6/12/2022
///
/// 8:23-9:20 give up
/// 11:30 read submit solutions
/// 12:44 AC
///
/// https://codeforces.com/contest/1697/submission/160310404
///

const LOCAL: bool = false;
static ANS: &str = "abcbabac";

fn ask1(i: usize) -> char {
    if LOCAL {
        ANS.chars().collect_vec()[i]
    } else {
        println!("? 1 {}", i + 1);
        let res = readln!(char);
        if res == '0' {
            exit(1);
        }
        res
    }
}

fn ask2(l: usize, r: usize) -> usize {
    if LOCAL {
        let x = ANS.chars().collect_vec();
        let mut cnt = vec![0; 26];
        for i in l..r {
            cnt[(x[i] as u8 - b'a') as usize] += 1;
        }
        cnt.iter().filter(|&&c| c > 0).count()
    } else {
        println!("? 2 {} {}", l + 1, r);
        let res = readln!(usize);
        if res == 0 {
            exit(1);
        }
        res
    }
}

fn ans(s: String) {
    println!("! {}", s);

    if LOCAL {
        assert_eq!(s, ANS);
    }
}

fn main() {
    // setup_out!(put, puts);
    let n = readln!(usize);

    let mut res = vec!['?'; n];
    let mut rpos = vec![n + 100; 26];
    for i in 0..n {
        let mut ps = rpos.iter().copied().filter(|&p| p < n).collect_vec();
        ps.sort();
        let tot = ask2(0, i + 1);
        // dbgln!(i, res, tot, ps);
        if tot > ps.len() {
            let c = ask1(i);
            rpos[(c as u8 - b'a') as usize] = i;
            res[i] = c;
        } else {
            let (mut good, mut bad) = (0, ps.len());
            while bad - good > 1 {
                let m = (good + bad) / 2;
                if ask2(ps[m], i + 1) == ps.len() - m {
                    good = m;
                } else {
                    bad = m;
                }
            }
            let c = res[ps[good]];
            res[i] = c;
            // dbgln!(good, ps[good], i, c);
            rpos[(c as u8 - b'a') as usize] = i;
        }
    }

    ans(res.iter().collect::<String>());
}

use crate::cplib::io::*;
use crate::cplib::minmax::*;
use crate::cplib::vec::*;
// region: cplib
#[rustfmt::skip]
#[allow(dead_code)]
pub mod cplib {
pub mod io {
	macro_rules! _with_dollar_sign { ($($body:tt)*) => { macro_rules! __with_dollar_sign { $($body)* } __with_dollar_sign!($); }}
	macro_rules! setup_out {
		($fn:ident,$fn_s:ident) => {
			use std::io::Write;
			let out = std::io::stdout();
			let mut out = ::std::io::BufWriter::new(out.lock());
				_with_dollar_sign! { ($d:tt) => {
				macro_rules! $fn { ($d($format:tt)*) => { let _ = write!(out,$d($format)*); } }
				macro_rules! $fn_s { ($d($format:tt)*) => { let _ = writeln!(out,$d($format)*); } }
			}}
		};
	}
	macro_rules! _epr { ($v:expr $(,)?) => {eprint!("{} = {:?}, ", stringify!($v), $v)}; }
	macro_rules! dbgln { ($($val:expr),*) => {{ eprint!("[{}:{}] ", file!(), line!()); ($(_epr!($val)),*); eprintln!(); }}; }
	pub fn readln_str() -> String {
		let mut line = String::new();
		::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
		line
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
	macro_rules! readlns {
		($($t:tt),*; $n:expr) => {{ let stdin = ::std::io::stdin();
			::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
				let line = line.unwrap(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*)
			}).collect::<Vec<_>>()
		}};
	}
	macro_rules! readln {
		($($t:tt),*) => {{ let line = cplib::io::readln_str(); #[allow(unused_mut)]let mut it = line.split_whitespace(); _read!(it; $($t),*) }};
	}
	pub(crate) use {readlns, readln, setup_out, dbgln, _with_dollar_sign, _epr, _read};
}
pub mod minmax {
	pub trait SetMinMax {
		fn setmin(&mut self, other: Self) -> bool;
		fn setmax(&mut self, other: Self) -> bool;
	}
	macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
			let update = $other $cmp *$self;
			if update { *$self = $other; }
			update
	}}; }
	impl<T> SetMinMax for T where T: PartialOrd {
		fn setmin(&mut self, other: T) -> bool { _set!(self, <, other) }
		fn setmax(&mut self, other: T) -> bool { _set!(self, >, other) }
	}
}
pub mod vec {
	pub trait CollectVec: Iterator { fn collect_vec(self) -> Vec<Self::Item> where Self: Sized { self.collect() } }
	impl<T> CollectVec for T where T: Iterator {}
	macro_rules! vvec {
		($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
		($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
	}
	pub(crate) use vvec;
}
}
// endregion: cplib
