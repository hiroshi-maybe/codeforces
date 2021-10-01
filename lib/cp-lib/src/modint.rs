// region: mod_int

#[rustfmt::skip]
#[macro_use]
pub mod mod_int {
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
            pub struct $struct_name {}
            impl mod_int::Modulus for $struct_name { fn modulus() -> i64 { $modulo } }
        };
    }
    macro_rules! define_convert {
        ($integer:ty) => {
            impl<M: Modulus> From<$integer> for ModInt<M> { fn from(v: $integer) -> ModInt<M> { ModInt::<M>::new(v as i64) } }
        };
    }
    define_convert!(i32); define_convert!(u32); define_convert!(i64); define_convert!(u64); define_convert!(usize);
}
define_modulus!(Mod1000000007, 1_000_000_007);
define_modulus!(Mod998244353, 998_244_353);
pub type ModInt1000000007 = mod_int::ModInt<Mod1000000007>;
pub type ModInt998244353 = mod_int::ModInt<Mod998244353>;
// type ModInt = ModInt1000000007;
// endregion: mod_int

// region: comb
mod comb {
    use super::mod_int::{ModInt, Modulus};

    pub struct Com<T> {
        fac: Vec<T>,
        ifac: Vec<T>,
    }

    impl<M: Modulus> Com<ModInt<M>> {
        pub fn new(n: usize) -> Com<ModInt<M>> {
            let mut fac = vec![ModInt::<M>::from(1); n + 1];
            let mut ifac = vec![ModInt::<M>::from(1); n + 1];
            for i in 1..=n {
                fac[i] = fac[i - 1] * i;
            }
            ifac[n] = ModInt::<M>::from(1) / fac[n];
            for i in (1..=n - 1).rev() {
                ifac[i] = ifac[(i + 1)] * (i + 1);
            }
            Com { fac, ifac }
        }

        pub fn choose(&self, n: usize, k: usize) -> ModInt<M> {
            if n < k {
                return ModInt::<M>::from(0);
            }
            self.fac[n] * self.ifac[n - k] * self.ifac[k]
        }

        pub fn fact(&self, n: usize) -> ModInt<M> {
            self.fac[n]
        }

        pub fn perm(&self, n: usize, k: usize) -> ModInt<M> {
            if n < k {
                return ModInt::<M>::from(0);
            }
            self.fac[n] * self.ifac[n - k]
        }

        pub fn multi_choose(&self, n: usize, k: usize) -> ModInt<M> {
            if n == 0 && k == 0 {
                return ModInt::<M>::from(1);
            }
            self.choose(n + k - 1, k)
        }
    }
}
use comb::*;
// endregion: comb

#[cfg(test)]
mod tests_modint {
    use super::*;

    type ModInt = ModInt1000000007;

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

#[cfg(test)]
mod tests_comb {
    use super::*;

    type ModInt = ModInt1000000007;

    #[test]
    fn test_choose() {
        let com = Com::<ModInt>::new(2_000_000);

        assert_eq!(com.choose(4, 2).val(), 6);
        assert_eq!(com.choose(1, 2).val(), 0);
        assert_eq!(com.choose(50, 15).val(), 829559370);
        assert_eq!(com.choose(2_000_000, 1).val(), 2_000_000);
        assert_eq!(com.choose(2_000_000, 1_000_000).val(), 192151600);
        assert_eq!(com.choose(1, 2_000_001).val(), 0);
    }

    #[test]
    #[should_panic(expected = "index out of bounds")]
    fn test_choose_out_of_index() {
        let com = Com::<ModInt>::new(2_000_000);
        let _ = com.choose(2_000_001, 1);
    }

    #[test]
    fn test_fact() {
        let com = Com::<ModInt>::new(2_000_000);

        assert_eq!(com.fact(0).val(), 1);
        assert_eq!(com.fact(1).val(), 1);
        assert_eq!(com.fact(2).val(), 2);
        assert_eq!(com.fact(3).val(), 6);
        assert_eq!(com.fact(10).val(), 3628800);
        assert_eq!(com.fact(15).val(), 674358851);
        assert_eq!(com.fact(20).val(), 146326063);
        assert_eq!(com.fact(1_000_000).val(), 641102369);
        assert_eq!(com.fact(2_000_000).val(), 578095319);
    }

    #[test]
    #[should_panic(expected = "index out of bounds")]
    fn test_fact_out_of_index() {
        let com = Com::<ModInt>::new(2_000_000);
        let _ = com.fact(2_000_001);
    }

    #[test]
    fn test_perm() {
        let com = Com::<ModInt>::new(2_000_000);

        assert_eq!(com.perm(4, 2).val(), 12);
        assert_eq!(com.perm(1, 2).val(), 0);
        assert_eq!(com.perm(50, 15).val(), 673538977);
        assert_eq!(com.perm(2_000_000, 1).val(), 2_000_000);
        assert_eq!(com.perm(2_000_000, 1_000_000).val(), 104818485);
        assert_eq!(com.perm(1, 2_000_001).val(), 0);
    }

    #[test]
    #[should_panic(expected = "index out of bounds")]
    fn test_perm_out_of_index() {
        let com = Com::<ModInt>::new(2_000_000);
        let _ = com.perm(2_000_001, 1);
    }

    #[test]
    fn test_multi_choose() {
        let com = Com::<ModInt>::new(2_000_000);

        assert_eq!(com.multi_choose(0, 0).val(), 1);
        assert_eq!(com.multi_choose(1, 0).val(), 1);
        assert_eq!(com.multi_choose(0, 1).val(), 0);
        assert_eq!(com.multi_choose(1, 1).val(), 1);
        assert_eq!(com.multi_choose(1, 2).val(), 1);
        assert_eq!(com.multi_choose(4, 2).val(), 10);
        assert_eq!(com.multi_choose(50, 15).val(), 998746094);
        assert_eq!(com.multi_choose(2_000_000, 1).val(), 2_000_000);
        assert_eq!(com.multi_choose(1, 2_000_000).val(), 1);
    }

    #[test]
    #[should_panic(expected = "index out of bounds")]
    fn test_multi_choose_out_of_index() {
        let com = Com::<ModInt>::new(2_000_000);
        let _ = com.multi_choose(2_000_000, 1_000_000);
    }
}
