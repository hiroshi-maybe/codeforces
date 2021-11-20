///
/// GCD libraries
/// =======
///
/// # Use cases
///
/// * Compute gcd(a, b) or lcm(a, b)
///   * Result may be negative if given numbers are negative
///
/// # Examples
///
/// ```
/// use cp_lib::{gcd, lcm};
///
/// let g = gcd(2415, 3289);
/// assert_eq!(g, 23);
///
/// let l = lcm(4278, 8602);
/// assert_eq!(l, 799986);
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/gcd.cpp
///

// region: gcd

#[rustfmt::skip]
#[allow(dead_code)]
mod gcd {
    use std::cmp::PartialEq;
    use std::ops::Rem;
    #[inline(always)] pub fn gcd<T: Gcd>(x: T, y: T) -> T { x.gcd(&y) }
    #[inline(always)] pub fn lcm<T: Gcd>(x: T, y: T) -> T { x.lcm(&y) }
    pub trait Gcd: Copy + Rem<Output = Self> + PartialEq {
        fn gcd(&self, other: &Self) -> Self;
        fn lcm(&self, other: &Self) -> Self;
    }
    macro_rules! impl_gcd {
        ($integer:ty) => {
            impl Gcd for $integer {
                #[inline] fn gcd(&self, other: &Self) -> Self {
                    let mut m = *self; let mut n = *other;
                    while m != 0 { let temp = m; m = n % temp; n = temp; }
                    n
                }
                #[inline] fn lcm(&self, other: &Self) -> Self {
                    self / gcd(*self, *other) * other
                }
            }
        };
    }
    impl_gcd!(i32);impl_gcd!(i64);impl_gcd!(usize);
}
pub use gcd::*;

// endregion: gcd

#[cfg(test)]
mod tests_gcd {
    use super::*;

    #[test]
    fn test_gcd() {
        assert_eq!(gcd(2415, 3289), 23);
        assert_eq!(gcd(406, 555), 1);
        assert_eq!(gcd(-12 as i32, 36).abs(), 12);
        assert_eq!(gcd(899 as usize, 493), 29);
        assert_eq!(gcd(15646365345434_i64, 64364363463464), 2);
    }

    #[test]
    fn test_lcm() {
        assert_eq!(lcm(4278, 8602), 799986);
        assert_eq!(lcm(10, 9), 90);
        assert_eq!(lcm(-12 as i32, 36).abs(), 36);
        assert_eq!(lcm(943349532_i64, 156464), 36900060293712);
    }
}
