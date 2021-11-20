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
        let g = gcd(2415, 3289);
        assert_eq!(g, 23);

        let g = gcd(406, 555);
        assert_eq!(g, 1);

        let g: i32 = gcd(-12, 36);
        assert_eq!(g.abs(), 12);
    }

    #[test]
    fn test_lcm() {
        let l = lcm(4278, 8602);
        assert_eq!(l, 799986);

        let l = lcm(10, 9);
        assert_eq!(l, 90);

        let l: i32 = lcm(-12, 36);
        assert_eq!(l.abs(), 36);
    }
}
