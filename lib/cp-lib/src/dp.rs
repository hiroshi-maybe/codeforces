#![allow(unused)]
use std::collections::*;

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
