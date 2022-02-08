#![allow(unused_macros, unused_imports)]
use std::cmp::*;
use std::collections::*;
use std::process::exit;

// $ cp-batch finding_zero | diff finding_zero.out -
// $ cargo run --bin finding_zero

///
/// 2/6/2022
///
/// 8:39-9:00 give up
///
/// 2/7/2022
///
/// 22:15-23:24 read editorial and AC
///
/// https://codeforces.com/blog/entry/99563
///
/// https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.v6u85tv68itv
///
/// https://twitter.com/kzyKT_M/status/1490371181597184004
/// https://twitter.com/natsugir/status/1490376554878148612
/// https://twitter.com/kinaba/status/1490378233593827331
///

const LOCAL: bool = false;
const A: [usize; 5] = [0, 1, 1, 1, 1];

fn ans(i: usize, j: usize) {
    println!("! {} {}", i + 1, j + 1);
    if LOCAL {
        assert!(A[i] == 0 || A[j] == 0);
    }
}

fn ask(i: usize, j: usize, k: usize) -> usize {
    println!("? {} {} {}", i + 1, j + 1, k + 1);
    let res = if LOCAL {
        A[i].max(A[j]).max(A[k]) - A[i].min(A[j]).min(A[k])
    } else {
        let res = readln!(isize);
        if res == -1 {
            exit(1);
        }
        res as usize
    };
    //dbgln!(res);
    res
}

fn solve() {
    let n = readln!(usize);

    let mut s = HashSet::new();
    s.insert(0);
    s.insert(1);

    for i in (2..n).step_by(2).take_while(|&i| i < n) {
        let j = (i + 1..)
            .filter_map(|i| {
                if s.contains(&(i % n)) {
                    None
                } else {
                    Some(i % n)
                }
            })
            .next()
            .unwrap();
        s.insert(i);
        s.insert(j);
        //dbgln!(s);
        assert_eq!(s.len(), 4);

        let mut xs = s
            .iter()
            .map(|&i| {
                let is = s.iter().filter(|&&j| i != j).copied().collect_vec();
                (i, ask(is[0], is[1], is[2]))
            })
            .collect_vec();

        xs.sort_unstable_by_key(|&x| x.1);
        xs.pop();
        xs.pop();

        s = xs.iter().map(|&x| x.0).collect::<HashSet<_>>();
    }

    let mut s = s.iter().copied().collect_vec();
    if s.len() == 1 {
        s.push(0);
    }
    ans(s[0], s[1]);
}

fn main() {
    //setup_out!(put, puts);
    for _ in 0..readln!(usize) {
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
