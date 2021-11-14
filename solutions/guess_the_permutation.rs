#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch guess_the_permutation | diff guess_the_permutation.out -
// $ cargo run --bin guess_the_permutation

///
/// 11/13/2021
///
/// 23:13-24:20 give up
/// 25:06-25:46 read solution tweets and got AC
///
/// https://twitter.com/kzyKT_M/status/1459798533897601025
/// https://twitter.com/laycrs/status/1459798351696646147
/// https://twitter.com/laycrs/status/1459809653316263938
///

fn ask(q: std::ops::Range<i64>, cnt: &mut i32) -> i64 {
    println!("? {} {}", q.start + 1, q.end);

    /*let a = vec![1, 3, 2, 5, 4];
    let mut res = 0;
    for i in q.start..q.end {
        for j in i + 1..q.end {
            res += if a[j as usize] < a[i as usize] { 1 } else { 0 };
        }
    }*/

    let res = readln!(i64);
    if res == -1 {
        std::process::exit(1);
    }
    *cnt += 1;
    assert!(*cnt <= 40);
    res
}

fn ans(i: i64, j: i64, k: i64) {
    println!("! {} {} {}", i + 1, j + 1, k);
}

fn solve() {
    let n = readln!(i64);
    let mut cnt = 0;

    let zk = ask(0..n, &mut cnt);
    let mut good = n;
    let mut bad = 0;
    while (good - bad).abs() > 1 {
        let m = (good + bad) / 2;
        let x = ask(0..m, &mut cnt);
        if x >= zk {
            good = m;
        } else {
            bad = m;
        }
    }
    let k = good;
    let zk1 = ask(0..k - 1, &mut cnt);
    let j = zk1 - zk + k - 1;
    let zj = ask(0..j, &mut cnt);
    let zj1 = ask(0..j - 1, &mut cnt);
    let i = zj1 - zj + j - 1;
    ans(i, j, k);
}

fn main() {
    let t = readln!(usize);
    for _ in 0..t {
        solve();
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
