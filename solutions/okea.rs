#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch okea | diff okea.out -
// $ cargo run --bin okea

///
/// 2/6/2022
///
/// 7:16-8:38 AC
///
/// https://codeforces.com/blog/entry/99563
///

fn solve(n: usize, k: usize) -> Option<Vec<Vec<usize>>> {
    if k == 1 {
        return Some((1..=n * k).map(|x| vec![x]).collect_vec());
    }

    if n % 2 == 1 {
        return None;
    }

    let mut res = vec![vec![]; n];
    let mut cur = 1;
    for i in (0..n).step_by(2) {
        for _ in 0..k {
            res[i].push(cur);
            cur += 2;
        }
    }
    let mut cur = 2;
    for i in (1..n).step_by(2) {
        for _ in 0..k {
            res[i].push(cur);
            cur += 2;
        }
    }

    let mut cnt = vec![0; n * k];
    for &a in res.iter().flatten() {
        cnt[a - 1] += 1;
    }
    assert!(cnt.iter().all(|&x| x == 1));

    /*
    let mut ok = true;
    for i in 0..n {
        for w in 2..=k {
            ok &= res[i]
                .windows(w)
                .all(|xs| xs.iter().copied().sum::<usize>() % w == 0);
        }
    }

    if ok {
        Some(res)
    } else {
        None
    }*/
    Some(res)
}

fn main() {
    setup_out!(put, puts);

    for _ in 0..readln!(usize) {
        let (n, k) = readln!(usize, usize);
        if let Some(res) = solve(n, k) {
            puts!("YES");
            for r in res {
                for x in r {
                    put!("{} ", x);
                }
                puts!("");
            }
        } else {
            puts!("NO");
        }
    }
}

#[test]
fn test_assert() {
    for n in 1..=5 {
        for k in 1..=5 {
            let act = solve(n, k);
            let exp = bruteforce(n, k);

            if act.is_some() != exp.is_some() {
                dbgln!(n, k, act, exp);
            }
            assert!(act.is_some() == exp.is_some());
        }
    }
}

#[allow(dead_code)]
fn bruteforce(n: usize, k: usize) -> Option<usize> {
    let l = n * k;
    let p = (1..=l).collect_vec();
    for p in p.permutations() {
        let mut ok = true;
        for i in 0..l / k {
            for w in 2..=k {
                ok &= p[i * k..(i + 1) * k]
                    .windows(w)
                    .all(|xs| xs.iter().copied().sum::<usize>() % w == 0);
            }
        }
        if ok {
            return Some(0);
            //dbgln!(l, l / k, k, p);
            /*for i in 0..l / k {
                dbgln!(&p[i * k..i * (k + 1)]);
            }*/
        }
    }
    return None;
}

#[test]
fn test_exper() {
    use rand::prelude::*;

    //let mut rng = thread_rng();
    for n in (1..=1).step_by(2) {
        for k in 1..=5 {
            let l = n * k;
            let p = (1..=l).collect_vec();
            for p in p.permutations() {
                let mut ok = true;
                for i in 0..l / k {
                    for w in 2..=k {
                        ok &= p[i * k..(i + 1) * k]
                            .windows(w)
                            .all(|xs| xs.iter().copied().sum::<usize>() % w == 0);
                    }
                }
                if ok {
                    dbgln!(l, l / k, k, p);
                    /*for i in 0..l / k {
                        dbgln!(&p[i * k..i * (k + 1)]);
                    }*/
                    break;
                }
            }
        }
    }
}

#[rustfmt::skip]
#[allow(dead_code)]
mod permutation {
	pub fn next_permutation<T>(xs: &mut [T]) -> bool where T: std::cmp::Ord {
		let asc_i = match xs.windows(2).rposition(|w| w[0] < w[1]) {
			Some(i) => i,
			None => { return false; }
		};
		let min_larger_offset = xs[asc_i + 1..]
			.binary_search_by(|x| match xs[asc_i].cmp(x) {
				std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
				ord => ord,
			})
			.unwrap_err();
		xs.swap(asc_i, asc_i + min_larger_offset);
		xs[asc_i + 1..].reverse();
		true
	}
	pub trait Permutations<T> { fn permutations(&self) -> Permutation<'_, T> where Self: Sized; }
	impl<T> Permutations<T> for Vec<T> where T: std::cmp::Ord {
		fn permutations(&self) -> Permutation<'_, T> { Permutation::new(&self[..]) }
	}
	pub struct Permutation<'a, T> { next_perm: Option<Vec<&'a T>>, }
	impl<'a, T: std::cmp::Ord> Permutation<'a, T> {
		fn new(dat: &'a [T]) -> Permutation<'a, T> {
			Permutation { next_perm: Some(dat.iter().map(|x| x).collect::<Vec<_>>()) }
		}
	}

	impl<'a, T: std::cmp::Ord> Iterator for Permutation<'a, T> {
		type Item = Vec<&'a T>;
		fn next(&mut self) -> Option<Self::Item> {
			if let Some(perm) = &mut self.next_perm {
				let res = perm.clone();
				if !next_permutation(perm) { self.next_perm = None; }
				Some(res)
			} else {
				None
			}
		}
	}
}
pub use permutation::{next_permutation, Permutations};

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
