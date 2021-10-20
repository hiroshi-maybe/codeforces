#![allow(dead_code)]
#![allow(unused_macros, unused_imports)]
use std::collections::*;

// source for https://github.com/hiroshi-maybe/codeforces/blob/master/script/template-solver.rs

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
    macro_rules! vvec {
        ($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
        ($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
    }
    pub(crate) use vvec;
}
}
// endregion: cplib

// String reader for testing
macro_rules! readstr {
    (source = $s:expr, $($t:tt),*; $n:expr) => {
        $s.lines().take($n).map(|line| { let it = line.split_whitespace(); _read!(it; $($t),*) }).collect::<Vec<_>>()
    };
    (source = $s:expr, $($t:tt),*) => {{
        #[allow(unused_mut)]
        let mut it = $s.split_whitespace();
        _read!(it; $($t),*)
    }};
}

#[cfg(test)]
mod tests_io {
    use super::*;

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
        assert!((12345.6789 - a).abs() < eps);
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
        assert_eq!(cs, vec!['a', 'b', 'c', 'd', 'e', 'f']);
    }

    #[test]
    fn input_bytes() {
        let cs = readstr! {
            source = "1a2b",
            [u8]
        };
        assert_eq!(cs, vec!['1' as u8, 'a' as u8, '2' as u8, 'b' as u8]);
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
        assert_eq!(a, vec![2, 0, 3]);
    }

    #[test]
    fn input_vec() {
        let a = readstr! {
            source = "1234567890123 23456789012 34567890123",
            [i64]
        };
        assert_eq!(a, vec![1234567890123, 23456789012, 34567890123]);
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
        assert_eq!(n, 2);
        assert_eq!(m, 3);
        assert_eq!(a[0], vec![12, 34, 56]);
        assert_eq!(a[1], vec![78, 90, 12]);
    }
}

#[cfg(test)]
mod tests_minmax {
    use super::*;
    #[test]
    fn test_setmin() {
        // larger
        let mut a = 10;
        let (updated, min_value) = a.setmin(11);

        // This throws an error because `min_value` should be dropped before access of `a`
        // assert_eq!(a, 10);
        assert_eq!(updated, false);
        assert_eq!(*min_value, 10);
        assert_eq!(a, 10);

        // equal
        let mut a = 10;
        let (updated, min_value) = a.setmin(10);

        assert_eq!(updated, false);
        assert_eq!(*min_value, 10);
        assert_eq!(a, 10);

        // smaller
        let mut a = 10;
        let (updated, min_value) = a.setmin(9);

        assert_eq!(updated, true);
        assert_eq!(*min_value, 9);
        assert_eq!(a, 9);
    }

    #[test]
    fn test_setmax() {
        // larger
        let mut a = 10;
        let (updated, max_value) = a.setmax(11);

        assert_eq!(updated, true);
        assert_eq!(*max_value, 11);
        assert_eq!(a, 11);

        // equal
        let mut a = 10;
        let (updated, max_value) = a.setmax(10);

        assert_eq!(updated, false);
        assert_eq!(*max_value, 10);
        assert_eq!(a, 10);

        // smaller
        let mut a = 10;
        let (updated, max_value) = a.setmax(9);

        assert_eq!(updated, false);
        assert_eq!(*max_value, 10);
        assert_eq!(a, 10);
    }
}

#[cfg(test)]
mod tests_vec {
    use super::*;

    #[test]
    fn test_vvec() {
        let v = 0;
        let n = 2usize;
        let m = 3usize;
        let l = 4usize;

        let dp = vvec![v; n];
        assert_eq!(dp, [v, v]);

        let dp = vvec!(v; n; m);
        assert_eq!(dp, [[v, v, v], [v, v, v]]);

        let dp = vvec![v; n; m; l];
        assert_eq!(
            dp,
            [
                [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]],
                [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
            ]
        );

        let dp = vvec![vec![0, 1]; n];
        assert_eq!(dp, [[0, 1], [0, 1]]);
    }
}
