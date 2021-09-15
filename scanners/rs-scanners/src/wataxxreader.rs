#![allow(non_snake_case, unused)]
use std::collections::*;

// String reader for testing
macro_rules! readstr {
	(source = $s:expr, $($t:tt),*; $n:expr) => {
		$s.lines().take($n).map(|line| {
			let mut it = line.split_whitespace();
			_read!(it; $($t),*)
		}).collect::<Vec<_>>()
	};

	(source = $s:expr, $($t:tt),*) => {{
		let mut it = $s.split_whitespace();
		_read!(it; $($t),*)
	}};
}

// https://atcoder.jp/contests/nikkei2019-2-final/submissions/8962004
pub fn readln() -> String {
	let mut line = String::new();
	::std::io::stdin().read_line(&mut line).unwrap_or_else(|e| panic!("{}", e));
	line
}

#[allow(unused_macros)]
macro_rules! readlns {
	($($t:tt),*; $n:expr) => {{
		let stdin = ::std::io::stdin();
		let ret = ::std::io::BufRead::lines(stdin.lock()).take($n).map(|line| {
			let line = line.unwrap();
			let mut it = line.split_whitespace();
			_read!(it; $($t),*)
		}).collect::<Vec<_>>();
		ret
	}};
}
#[allow(unused_macros)]
macro_rules! readln {
	($($t:tt),*) => {{
		let line = readln();
        #[allow(unused_mut)]
		let mut it = line.split_whitespace();
		_read!(it; $($t),*)
	}};
}
macro_rules! _read {
	($it:ident; [char]) => {
		_read!($it; String).chars().collect::<Vec<_>>()
	};
	($it:ident; [u8]) => {
		Vec::from(_read!($it; String).into_bytes())
	};
	($it:ident; usize1) => {
		$it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1
	};
	($it:ident; [usize1]) => {
		$it.map(|s| s.parse::<usize>().unwrap_or_else(|e| panic!("{}", e)) - 1).collect::<Vec<_>>()
	};
	($it:ident; [$t:ty]) => {
		$it.map(|s| s.parse::<$t>().unwrap_or_else(|e| panic!("{}", e))).collect::<Vec<_>>()
	};
	($it:ident; $t:ty) => {
		$it.next().unwrap_or_else(|| panic!("input mismatch")).parse::<$t>().unwrap_or_else(|e| panic!("{}", e))
	};
	($it:ident; $($t:tt),+) => {
		($(_read!($it; $t)),*)
	};
}

// cargo build --bin watareader --release
// target/release/watareader < ../1e6int.input  0.04s user 0.01s system 18% cpu 0.302 total
fn main() {
    let n = readln!(usize);
	let a = readln!([i64]);
    // let (n, a) = read!(usize, [i64]);

    println!("{}, {}", n, a[100]);
}

#[cfg(test)]
mod tests {
	#[test]
    fn input_single_value() {
        let a = readstr! {
			source = "123",
            i32
        };
		assert_eq!(a, 123);
    }

	#[test]
    fn input_double() {
        let a = readstr! {
			source = "12345.67890",
            f64
        };
		let eps = 1e-4;
		assert!((12345.6789-a).abs() < eps);
    }

	#[test]
    fn input_tuple() {
        let (a, b, c) = readstr! {
			source = "1 2 3",
            i32, i32, i32
        };
		assert_eq!(a, 1);
		assert_eq!(b, 2);
		assert_eq!(c, 3);
    }

	#[test]
    fn input_string() {
        let cs = readstr! {
			source = "abcdef",
            [char]
        };
		assert_eq!(cs, vec!['a','b','c','d','e','f']);
    }

	#[test]
    fn input_bytes() {
        let cs = readstr! {
			source = "1a2b",
            [u8]
        };
		assert_eq!(cs, vec!['1' as u8,'a' as u8,'2' as u8,'b' as u8]);
    }

	#[test]
    fn input_usize1() {
        let n = readstr! {
			source = "314",
            usize1
        };
		assert_eq!(n, 313);
    }

	#[test]
    fn input_usize1s() {
        let a = readstr! {
			source = "3 1 4",
            [usize1]
        };
		assert_eq!(a, vec![2,0,3]);
    }

	#[test]
    fn input_vec() {
        let a = readstr! {
			source = "1234567890123 23456789012 34567890123",
            [i64]
        };
		assert_eq!(a, vec![1234567890123,23456789012,34567890123]);
    }

	#[test]
	fn input_lines() {
		let (n, m) = readstr! {
			source = "2 3",
            usize, usize
        };
        let a = readstr! {
			source = "12 34 56\n78 90 12\n",
            [i64]; n
        };
		assert_eq!(a[0], vec![12,34,56]);
		assert_eq!(a[1], vec![78,90,12]);
    }
}
