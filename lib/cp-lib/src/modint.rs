#[rustfmt::skip]
#[macro_use]
#[allow(unused_mut)]
mod mod_int {
    use std::convert::TryFrom;
    use std::marker::PhantomData;
    use std::ops::*;
    pub trait Modulus: Copy { fn modulus() -> i64; }

    #[derive(Copy, Clone, Debug, Hash, PartialEq, Eq, PartialOrd, Ord)]
    pub struct ModInt<M> { val: u32, phantom: PhantomData<fn() -> M> }
    impl<M: Modulus> ModInt<M> {
        pub fn val(self) -> u32 { self.val }
        pub fn pow(self, mut n: i64) -> Self {
            debug_assert!(n >= 0);
            let mut res = Self::raw(1);
            let mut p = self;
            while n > 0 {
                if n % 2 != 0 { res *= p; }
                p *= p; n >>= 1;
            }
            res
        }
        pub fn inv(self) -> Self { self.pow(M::modulus() - 2) }
        fn new(val: i64) -> Self {
            let mut v = val;
            if val < 0 { v = v % M::modulus() + M::modulus(); }
            if v >= M::modulus() { v -= M::modulus(); }
            if v >= M::modulus() { v %= M::modulus(); }
            Self::raw(v)
        }
        fn raw(val: i64) -> Self { Self { val: u32::try_from(val).unwrap(), phantom: PhantomData } }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> Add<T> for ModInt<M> {
        type Output = Self;
        fn add(self, other: T) -> Self { Self::new(self.val as i64 + other.into().val as i64) }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> Sub<T> for ModInt<M> {
        type Output = Self;
        fn sub(self, other: T) -> Self { Self::new(self.val as i64 - other.into().val as i64) }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> Mul<T> for ModInt<M> {
        type Output = Self;
        fn mul(self, other: T) -> Self { Self::new((self.val as i64) * (other.into().val as i64) % M::modulus()) }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> Div<T> for ModInt<M> {
        type Output = Self;
        fn div(self, other: T) -> Self { self * other.into().inv() }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> AddAssign<T> for ModInt<M> {
        fn add_assign(&mut self, other: T) { *self = *self + other; }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> SubAssign<T> for ModInt<M> {
        fn sub_assign(&mut self, other: T) { *self = *self - other; }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> MulAssign<T> for ModInt<M> {
        fn mul_assign(&mut self, other: T) { *self = *self * other; }
    }
    impl<M: Modulus, T: Into<ModInt<M>>> DivAssign<T> for ModInt<M> {
        fn div_assign(&mut self, other: T) { *self = *self / other; }
    }
    impl<M: Modulus> Neg for ModInt<M> {
        type Output = Self;
        fn neg(self) -> Self { Self::new(-(self.val as i64)) }
    }
    impl<M: Modulus> ::std::fmt::Display for ModInt<M> {
        fn fmt(&self, f: &mut ::std::fmt::Formatter) -> ::std::fmt::Result { self.val().fmt(f) }
    }
    macro_rules! define_modulus {
        ($struct_name: ident, $modulo: expr) => {
            #[derive(Copy, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
            struct $struct_name {}
            impl mod_int::Modulus for $struct_name { fn modulus() -> i64 { $modulo } }
        };
    }
    macro_rules! define_convert {
        ($integer:ty) => {
            impl<M: Modulus> From<$integer> for ModInt<M> { fn from(v: $integer) -> ModInt<M> { ModInt::<M>::new(v as i64) } }
        };
    }
    define_convert!(i32); define_convert!(i64); define_convert!(usize);
}
define_modulus!(Mod1000000007, 1_000_000_007);
define_modulus!(Mod998244353, 998_244_353);
type ModInt = mod_int::ModInt<Mod1000000007>;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_from() {
        let a = ModInt::from(0);
        assert_eq!(a.val(), 0);

        let a = ModInt::from(-1);
        assert_eq!(a.val(), 1_000_000_006);

        let a = ModInt::from(1_000_000_008);
        assert_eq!(a.val(), 1);

        let a = ModInt::from(2_000_000_016);
        assert_eq!(a.val(), 2);
    }

    #[test]
    fn test_pow() {
        let a = ModInt::from(3).pow(2);
        assert_eq!(a.val(), 9);

        let a = ModInt::from(12345678);
        assert_eq!(a.inv().val(), 325842698);
    }

    #[test]
    fn test_inv() {
        let a = ModInt::from(3);
        assert_eq!(a.inv().val(), 333333336);

        let a = ModInt::from(12345678);
        assert_eq!(a.inv().val(), 325842698);
    }

    macro_rules! test_operator {
        ($lhs:expr, $op1:tt, $rhs:expr => $res:expr; $op2:tt) => {
            let a = $lhs $op1 $rhs;
            assert_eq!(a.val(), $res);

            let mut a = $lhs;
            a $op2 $rhs;
            assert_eq!(a.val(), $res);
        };
    }

    #[test]
    fn test_add() {
        test_operator!(ModInt::from(1), +, 2 => 3; +=);
        test_operator!(ModInt::from(1_000_000_000i64), +, 10 => 3; +=);
        test_operator!(ModInt::from(1), +, -8 => 1_000_000_000; +=);
        test_operator!(ModInt::from(2_000_000_000), +, 2_000_000_000 => 999999979; +=);
    }

    #[test]
    fn test_sub() {
        test_operator!(ModInt::from(10), -, 110 => 999999907; -=);
        test_operator!(ModInt::from(100usize), -, 10 => 90; -=);
    }

    #[test]
    fn test_mul() {
        test_operator!(ModInt::from(10), *, 10 => 100; *=);
        test_operator!(ModInt::from(20_000_000usize), *, 12345678 => 558271609; *=);
    }

    #[test]
    fn test_div() {
        test_operator!(ModInt::from(12), /, 3 => 4; /=);
        test_operator!(ModInt::from(20_000_000usize), /, 12345678 => 914382029; /=);
    }

    #[test]
    fn test_neg() {
        let a = -ModInt::from(1);
        assert_eq!(a.val(), 1_000_000_006);

        let a = -ModInt::from(0);
        assert_eq!(a.val(), 0);
    }
}
