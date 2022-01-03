#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::ops::Range;

// $ cp-batch integers_shop | diff integers_shop.out -
// $ cargo run --bin integers_shop

///
/// 1/3/2022
///
/// 6:44-7:55 give up
/// 10:00-10:58 read solution tweets and AC
///
/// https://codeforces.com/blog/entry/98654
/// https://twitter.com/laycrs/status/1478047013413732352
/// https://twitter.com/heno_code/status/1478047516956704768
/// https://twitter.com/kzyKT_M/status/1478047231567876096
/// https://twitter.com/ei1333/status/1478046632319254529
///

fn cal_cost(xs: &Vec<(i64, i64, i64)>) -> i64 {
    xs.iter().map(|&(_, _, c)| c).sum::<i64>()
}

fn solve(n: usize, lrs: &Vec<(i64, i64, i64)>) -> Vec<(i64, i64, i64)> {
    let inf = 10i64.pow(17);
    let (mut l, mut r) = (inf, -inf);
    let (mut lcost, mut rcost, mut lrcost) = (inf, inf, inf);
    let mut res = vec![(inf, inf, inf); n];
    for s in 0..n {
        let (mut ll, rr, c) = lrs[s];
        ll -= 1;

        if l > ll {
            l = ll;
            lcost = inf;
            lrcost = inf;
        }
        if l == ll {
            lcost.setmin(c);
        }

        if rr > r {
            r = rr;
            rcost = inf;
            lrcost = inf;
        }
        if r == rr {
            rcost.setmin(c);
        }
        if l == ll && r == rr {
            lrcost.setmin(c);
        }

        res[s] = (l, r, min(lcost + rcost, lrcost));
        //dbgln!(s, ll, rr, c, res[s]);
    }
    res
}

#[allow(dead_code)]
fn solve_broken(n: usize, lrs: &Vec<(i64, i64, i64)>) -> Vec<(i64, i64, i64)> {
    let inf = 10i64.pow(17);
    let mut cur = vec![(inf, -inf, inf)];
    let mut res = vec![(inf, inf, inf); n];
    for s in 0..n {
        let (mut l, r, c) = lrs[s];
        l -= 1;

        //dbgln!(l, r, c, cur);
        let fi: (i64, i64, i64) = *cur.first().unwrap();
        let la: (i64, i64, i64) = *cur.last().unwrap();

        let lb = min(l, fi.0);
        let rb = max(r, la.1);

        let mut cost = inf;
        let mut next = vec![];

        for x in vec![fi, (l, r, c)] {
            for y in vec![la, (l, r, c)] {
                if x.0 == lb && y.1 == rb {
                    let mut cand = vec![x, y];
                    if cand.len() == 2 && cand[0] == cand[1] {
                        cand.pop();
                    }
                    let cost2 = cal_cost(&cand);
                    if cost2 < cost {
                        next = cand;
                        cost = cost2;
                    } else if cost2 == cost && cand.len() > next.len() {
                        next = cand;
                    }
                }
            }
        }

        cur = next;
        res[s] = (lb, rb, cal_cost(&cur));
    }
    res
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);
    for _ in 0..t {
        let n = readln!(usize);
        let lrs = readlns!(i64, i64, i64; n);
        let res = solve(n, &lrs);
        for (_, _, r) in res {
            puts!("{}", r);
        }
    }
}

#[test]
fn test_random() {
    use rand::prelude::*;
    loop {
        let mut rng = thread_rng();
        let n = 5;
        let max_l = 5;
        let max_c = 5;
        let lrs = (0..n)
            .map(|_| {
                let l = rng.gen_range(1, max_l + 1);
                (l, rng.gen_range(l, max_l + 1), rng.gen_range(1, max_c))
            })
            .collect_vec();

        let exp = solve(n, &lrs);
        let act = solve_broken(n, &lrs);
        if act != exp {
            dbgln!(act, exp, lrs);
        }
        assert_eq!(act, exp);
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
