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

// $ rs-cp-batch bakry_and_partitioning | diff bakry_and_partitioning.out -
// $ cargo run --bin bakry_and_partitioning

///
/// 10/3/2021
///
/// 8:14-9:41 WA
/// 10:40-11:28 AC
///
/// 10/12/2021
///
/// Review editorial and add simpler solution
///
/// https://codeforces.com/blog/entry/95583
/// https://twitter.com/hanseilimak/status/1448151883357442049
///
/// https://twitter.com/laycrs/status/1444702692115320833
/// https://twitter.com/maspy_stars/status/1444703294408986625
/// https://twitter.com/kzyKT_M/status/1444704322730684419
///

#[allow(dead_code)]
fn dfs1(u: usize, par: usize, g: &Vec<Vec<usize>>, xor: &mut Vec<i64>, a: &Vec<i64>) -> i64 {
    let mut res = a[u];
    for v in &g[u] {
        if *v != par {
            res ^= dfs1(*v, u, g, xor, a);
        }
    }
    xor[u] = res;
    res
}
#[allow(dead_code)]
fn dfs2(u: usize, par: usize, g: &Vec<Vec<usize>>, xor: &Vec<i64>, mut want0: bool) -> bool {
    // dbgln!(u, want0);
    if want0 {
        if xor[u] == 0 {
            want0 = false;
        }
    } else {
        if xor[u] == xor[0] {
            //dbgln!(u, want0, xor[u], xor[0]);
            return true;
        }
    }

    let mut res = false;
    for v in &g[u] {
        if *v != par {
            res |= dfs2(*v, u, g, xor, want0);
        }
    }
    res
}
#[allow(dead_code)]
fn dfs3(u: usize, par: usize, g: &Vec<Vec<usize>>, xor: &Vec<i64>, res: &mut bool) -> bool {
    let mut ans = false;
    if xor[u] == xor[0] {
        ans = true;
    }

    let mut cnt = 0;
    for v in &g[u] {
        if *v != par {
            cnt += if dfs3(*v, u, g, xor, res) { 1 } else { 0 };
        }
    }
    if cnt >= 2 {
        *res = true;
    }
    //dbgln!(u, cnt, res, ans);
    ans || cnt >= 1
}
#[allow(dead_code)]
fn solve_v1(n: usize, k: i32, a: &Vec<i64>, g: &Vec<Vec<usize>>) -> bool {
    let mut xor = vec![0i64; n];
    dfs1(0, n + 1, &g, &mut xor, &a);
    //dbgln!(xor);
    if xor[0] == 0 {
        return true;
    }
    if k == 2 {
        return false;
    }

    let mut res = dfs2(0, n + 1, &g, &xor, true);
    if !res {
        dfs3(0, n + 1, &g, &xor, &mut res);
    }
    res
}

fn dfs(u: usize, par: usize, g: &Vec<Vec<usize>>, a: &Vec<i64>, all: i64, cnt: &mut i32) -> i64 {
    let mut xor = a[u];
    for &v in &g[u] {
        if v == par {
            continue;
        }
        xor ^= dfs(v, u, g, a, all, cnt);
    }
    if xor == all {
        *cnt += 1;
        return 0;
    }
    xor
}

fn solve_v2(_n: usize, k: i32, a: &Vec<i64>, g: &Vec<Vec<usize>>) -> bool {
    let all = a.iter().fold(0, |a, &b| a ^ b);
    if all == 0 {
        return true;
    }
    if k == 2 {
        return false;
    }
    let mut cnt = 0;
    dfs(0, g.len(), g, a, all, &mut cnt);
    // dbgln!(cnt, k, cnt > k);
    cnt >= 3
}

fn main() {
    setup_out!(put, puts);

    let t = readln!(usize);
    for _ in 0..t {
        let (n, k) = readln!(usize, i32);
        let a = readln!([i64]);
        let mut g: Vec<Vec<usize>> = vec![vec![]; n];
        for _ in 0..n - 1 {
            let (u, v) = readln!(usize1, usize1);
            g[u].push(v);
            g[v].push(u);
        }

        let res = solve_v2(n, k, &a, &g);
        puts!("{}", if res { "YES" } else { "NO" });
    }
}
