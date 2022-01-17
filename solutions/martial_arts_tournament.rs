#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch martial_arts_tournament | diff martial_arts_tournament.out -
// $ cargo run --bin martial_arts_tournament

///
/// 1/16/2022
///
/// 7:56-8:54 give up
///
/// 1/17/2022
///
/// 11:52-12:19 AC after reading solution tweets
///
/// https://codeforces.com/blog/entry/99136
///
/// https://twitter.com/kzyKT_M/status/1482757791504736260
/// https://twitter.com/laycrs/status/1482760197584334850
///

fn f(p: usize, st: usize, xs: &Vec<(usize, u64)>) -> (u64, usize) {
    let mut sum = 0;
    for i in st..xs.len() {
        if sum + xs[i].1 > (1 << p) {
            return ((1 << p) - sum, i);
        }
        sum += xs[i].1;
    }
    ((1 << p) - sum, xs.len())
}

fn solve() -> u64 {
    let n = readln!(usize);
    let mut a = readln!([usize]);
    a.sort_unstable();

    let mut xs: Vec<(usize, u64)> = vec![];
    for a in a {
        if xs.is_empty() || xs.last().unwrap().0 != a {
            xs.push((a, 0));
        }
        xs.last_mut().unwrap().1 += 1;
    }

    let p_ub = n.next_power_of_two().trailing_zeros() as usize;
    let mut res = 1 << 30;
    for p1 in 0..=p_ub {
        let (miss1, k1) = f(p1, 0, &xs);
        for p2 in 0..=p_ub {
            let (miss2, k2) = f(p2, k1, &xs);
            let rem = xs[k2..].iter().map(|&x| x.1).sum::<u64>();
            let miss3 = rem.next_power_of_two() - rem;
            // (0..).map(|p| (1 << p) - rem).find(|&m| m >= 0).unwrap();
            res.setmin(miss1 + miss2 + miss3 as u64);
        }
    }

    res
}

fn main() {
    setup_out!(put, puts);

    for _ in 0..readln!(usize) {
        let res = solve();
        puts!("{}", res);
    }
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
		fn setmin<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
		fn setmax<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
	}
	macro_rules! _set { ($self:ident, $cmp:tt, $other:ident) => {{
			let update = $other $cmp *$self;
			if update { *$self = $other; }
			(update, $self)
	}}; }
	impl<T> SetMinMax for T where T: PartialOrd {
		fn setmin<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, <, other) }
		fn setmax<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, >, other) }
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
