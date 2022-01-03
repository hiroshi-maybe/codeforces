#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch hidden_permutations | diff hidden_permutations.out -
// $ cargo run --bin hidden_permutations

///
/// 1/3/2022
///
/// 7:56-9:15 give up
/// 9:30-9:47 read solution tweets and AC
///
/// https://codeforces.com/blog/entry/98654
/// https://twitter.com/laycrs/status/1478047013413732352
/// https://twitter.com/heno_code/status/1478047516956704768
/// https://twitter.com/kzyKT_M/status/1478047231567876096
/// https://twitter.com/ei1333/status/1478046632319254529
///

const LOC: bool = false;
const ANS: [usize; 4] = [1, 3, 4, 2];

fn ask(i: usize, q: &mut Vec<usize>) -> usize {
    println!("? {}", i + 1);

    if !LOC {
        let res = readln!(usize);
        assert_ne!(res, 0);
        res - 1
    } else {
        let res = q[i];
        let org_q = q.clone();
        for i in 0..q.len() {
            q[i] = org_q[ANS[i] - 1];
        }
        res - 1
    }
}

fn ans(p: &Vec<usize>) {
    if !LOC {
        print!("!");
        for p in p {
            print!(" {}", p + 1);
        }
        println!();
    } else {
        let ans = ANS.iter().copied().collect_vec();
        let act = p.iter().map(|x| *x + 1).collect_vec();
        assert_eq!(ans, act);
    }
}

fn solve() {
    let n = readln!(usize);

    let mut q = (1..=n).collect_vec();

    let mut res = vec![n; n];
    for i in 0..n {
        if res[i] != n {
            continue;
        }

        loop {
            if ask(i, &mut q) == i {
                break;
            }
        }

        let mut cur = i;
        loop {
            let next = ask(i, &mut q);
            res[cur] = next;
            //dbgln!(i, cur, next, q);
            cur = next;
            if res[next] != n {
                break;
            }
        }
    }
    ans(&res);
}

fn main() {
    //setup_out!(put, puts);
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
