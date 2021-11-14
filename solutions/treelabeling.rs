#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;

// $ cp-batch treelabeling | diff treelabeling.out -
// $ cargo run --bin treelabeling

///
/// 11/12/2021
///
/// 7:43-8:39 runtime error
/// 9:00-9:09 got AC
///
/// https://codeforces.com/blog/entry/96866
/// https://twitter.com/laycrs/status/1459198082218741761
/// https://twitter.com/kzyKT_M/status/1459198797503156224
///

fn msb(mut u: usize) -> usize {
    let mut res = 0;
    while u > 0 {
        res += 1;
        u /= 2;
    }
    res
}

fn dfs(u: usize, g: &Vec<Vec<usize>>, par: usize, p: usize, res: &mut Vec<Vec<usize>>) {
    res[p].push(u);
    for v in &g[u] {
        if *v != par {
            dfs(*v, g, u, 1 - p, res);
        }
    }
}

fn solve() -> Vec<usize> {
    let n = readln!(usize);
    let mut g = vec![vec![]; n];
    for (u, v) in readlns!(usize1, usize1; n-1) {
        g[u].push(v);
        g[v].push(u);
    }

    let mxb = msb(n);
    let mut msbs = vec![vec![]; mxb];
    for p in 1..=n {
        msbs[msb(p) - 1].push(p);
    }

    let mut gs = vec![vec![]; 2];
    dfs(0, &g, n, 0, &mut gs);

    let mut res = vec![0; n];
    let p = if gs[0].len() >= gs[1].len() { 1 } else { 0 };
    let mask = gs[p].len();
    for i in 0..=msb(mask) {
        if (mask >> i) & 1 == 1 {
            assert_eq!(msbs[i].len(), 1 << i);
            while let Some(n) = msbs[i].pop() {
                res[gs[p].pop().unwrap()] = n;
            }
        }
    }
    for &n in msbs.iter().flatten() {
        res[gs[1 - p].pop().unwrap()] = n;
    }
    res

    /*
    for mask in 0..1usize << mxb {
        let mut cnts = vec![gs[0].len() as i32, gs[1].len() as i32];
        for i in 0..mxb {
            let g = if (mask >> i) & 1 == 1 { 1 } else { 0 };
            cnts[g] -= msbs[i].len() as i32;
        }
        if cnts[0] == 0 && cnts[1] == 0 {
            let mut res = vec![0; n];
            for i in 0..mxb {
                let g = if (mask >> i) & 1 == 1 { 1 } else { 0 };
                //dbgln!(i, g, gs[g], msbs[i]);
                while let Some(p) = msbs[i].pop() {
                    res[gs[g].pop().unwrap()] = p;
                }
            }
            return res;
        }
    }
    unreachable!()
    */
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);
    for _ in 0..t {
        let res = solve();
        for u in res {
            put!("{} ", u);
        }
        puts!();
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
