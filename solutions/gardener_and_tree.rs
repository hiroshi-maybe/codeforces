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

// $ rs-cp-batch gardener_and_tree | diff gardener_and_tree.out -
// $ cargo run --bin gardener_and_tree

///
/// 10/13/2021
///
/// 9:09-9:28 WA
/// 9:48 MLE Lol.
/// 10:00 AC
///

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);
    for _ in 0..t {
        let _ = readln!([usize]);
        let (n, k) = readln!(usize, usize);
        let mut g = vec![vec![]; n];
        let mut deg = vec![0; n];
        for (u, v) in readlns!(usize1, usize1; n-1) {
            g[u].push(v);
            g[v].push(u);
            deg[u] += 1;
            deg[v] += 1;
        }

        if n == 1 {
            puts!("0");
            continue;
        }

        let mut q = VecDeque::new();
        for u in 0..n {
            if deg[u] == 1 {
                q.push_back(u);
            }
        }

        let mut viz = vec![false; n];
        for _ in 0..k {
            let mut l = q.len();
            while l > 0 {
                l -= 1;
                let u = q.pop_front().unwrap();
                deg[u] -= 1;
                viz[u] = true;
                for &v in &g[u] {
                    deg[v] -= 1;
                    if deg[v] == 1 {
                        q.push_back(v);
                    }
                }
            }
        }
        //dbgln!(cnt, n);
        let cnt = viz.iter().filter(|&&a| a).count();

        puts!("{}", n - cnt);
    }
}
