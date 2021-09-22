#![allow(unused)]
use std::collections::*;

macro_rules! vvec {
    ($v:expr; $n:expr) => { Vec::from(vec![$v; $n]) };
    ($v:expr; $n:expr $(; $ns:expr)+) => { Vec::from(vec![vvec![$v $(; $ns)*]; $n]) };
}

pub trait SetMinMax {
    fn setmin<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
    fn setmax<'a>(&'a mut self, other: Self) -> (bool, &'a Self);
}
#[rustfmt::skip]
macro_rules! _set {
    ($self:ident, $cmp:tt, $other:ident) => {{
        let update = $other $cmp *$self;
        if update { *$self = $other; }
        (update, $self)
    }};
}
#[rustfmt::skip]
impl<T> SetMinMax for T
where
    T: PartialOrd,
{
    fn setmin<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, <, other) }
    fn setmax<'a>(&'a mut self, other: T) -> (bool, &'a Self) { _set!(self, >, other) }
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
