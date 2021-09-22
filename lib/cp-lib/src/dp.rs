#![allow(unused)]
use std::collections::*;

macro_rules! vvec {
    ($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
    ($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
}

pub trait SetMinMax {
    fn setmin(&mut self, other: Self) -> bool;
    fn setmax(&mut self, other: Self) -> bool;
}

impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin(&mut self, other: T) -> bool {
        *self > other && {
            *self = other;
            true
        }
    }
    fn setmax(&mut self, other: T) -> bool {
        *self < other && {
            *self = other;
            true
        }
    }
}

#[cfg(test)]
mod tests {
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

    #[test]
    fn test_setmin() {
        // larger
        let mut a = 10;
        let res = a.setmin(11);

        assert_eq!(a, 10);
        assert_eq!(res, false);

        // equal
        let mut a = 10;
        let res = a.setmin(10);

        assert_eq!(a, 10);
        assert_eq!(res, false);

        // smaller
        let mut a = 10;
        let res = a.setmin(9);

        assert_eq!(a, 9);
        assert_eq!(res, true);
    }

    #[test]
    fn test_setmax() {
        // larger
        let mut a = 10;
        let res = a.setmax(11);

        assert_eq!(a, 11);
        assert_eq!(res, true);

        // equal
        let mut a = 10;
        let res = a.setmax(10);

        assert_eq!(a, 10);
        assert_eq!(res, false);

        // smaller
        let mut a = 10;
        let res = a.setmax(9);

        assert_eq!(a, 10);
        assert_eq!(res, false);
    }
}
