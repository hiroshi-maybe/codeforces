///
/// Sieve of Eratosthenes
/// =======
///
/// # Use cases
///
/// * Linear sieve
///   * Pre-compute factorizations of all numbers in [2;n) in O(n*log log n) time
///   * Query prime factors for given x (x<=n) in O(log n) time
///
/// # Implementation
///
/// self.divp[x] holds minimum divisor for `x`
///                   0  1  2  3  4  5  6  7  8  9 10  11 12
/// e.g. self.divp = [0, 0, 2, 3, 2, 5, 2, 7, 2, 3, 2, 11, 2]
///
/// # Examples
///
/// ```
/// use cp_lib::LinearSieve;
/// let sieve = LinearSieve::new(1_000_000);
///
/// assert_eq!(sieve.fact(120), vec![2, 2, 2, 3, 5]);
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/divisor.cpp
/// * https://cp-algorithms.com/algebra/prime-sieve-linear.html
///
/// # Used problems
///
/// * https://github.com/hiroshi-maybe/atcoder/blob/ab94707b57bc09e7083104d63d3dc49854e10002/solutions/coprime.rs#L54
/// * https://github.com/hiroshi-maybe/atcoder/blob/293d4122fb0cd64ba613e5a543da9156d8d68648/solutions/factors_of_factorial.rs#L116
/// * https://github.com/hiroshi-maybe/atcoder/blob/4a67f474a7af2837c4f14826e006e11307a14165/solutions/prime_sum_game.rs#L36
/// * https://github.com/hiroshi-maybe/atcoder/blob/4adf102316809fea2064e0d948254ade7743abab/solutions/factorial_and_multiple.rs#L64
///

// region: sieve

#[rustfmt::skip]
#[allow(dead_code)]
mod sieve {
    pub struct LinearSieve { n: usize, divp: Vec<usize>, }
    impl LinearSieve {
        pub fn new(n: usize) -> Self {
            let mut sieve = LinearSieve { n, divp: vec![0; n + 1], };
            for p in 2..=n {
                if sieve.divp[p] != 0 { continue; }
                sieve.divp[p] = p;
                for q in (p * p..).step_by(p).take_while(|q| q <= &n) {
                    if sieve.divp[q] == 0 { sieve.divp[q] = p; }
                }
            }
            sieve
        }
        pub fn fact(&self, mut x: usize) -> Vec<usize> {
            let mut res = vec![];
            while x > 1 { res.push(self.divp[x]); x /= self.divp[x]; }
            res.sort_unstable();
            res
        }
        pub fn is_prime(&self, n: usize) -> bool {
            if n >= self.n { panic!("argument exceeds sieve table size") }
            n != 0 && self.divp[n] == n
        }
    }
}
pub use sieve::*;

// endregion: sieve

///
/// Integer Factorization
/// =======
///
/// # Use cases
///
/// * Divisor enumeration, O(√n) time
///   * Enumerate divisors with trial division
///   * Result is sorted
///
/// # Examples
///
/// ```
/// use cp_lib::IntFactorial;
///
/// assert_eq!(12_i64.divisors(), vec![1,2,3,4,6,12]);
/// ```
///
/// # Note
///
/// * size of divisors is upper-bounded by HCN(n)
/// * Highly Composite Number: http://wwwhomes.uni-bielefeld.de/achim/highly.txt
/// * HCN(10^9)≈1440, HCN(10^6)≈256
///   * HCN(10^1) = 4 (6)
///   * HCN(10^2) = 12 (60)
///   * HCN(10^3) = 32 (840)
///   * HCN(10^4) = 64 (7560)
///   * HCN(10^5) = 128 (83160)
///   * HCN(10^6) = 240 (720720)
///   * HCN(10^7) = 448 (8648640)
///   * HCN(10^8) = 768 (73513440)
///   * HCN(10^9) = 1344 (735134400)
///   * HCN(10^12) = 6720 (963761198400)
///   * HCN(10^15) = 26880 (8.664213e+014)
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/divisor.cpp
/// * https://cp-algorithms.com/algebra/factorization.html
///

// region: int_fact

#[rustfmt::skip]
#[allow(dead_code)]
mod int_fact {
    use std::collections::HashMap;
    pub trait IntFactorial where Self: Sized {
        fn divisors(&self) -> Vec<Self>;
        fn prime_facts(&self) -> Vec<Self>;
        fn prime_facts_map(&self) -> HashMap<Self, usize>;
    }
    macro_rules! impl_int_fact { ($integer:ty) => {
        impl IntFactorial for $integer {
            fn divisors(&self) -> Vec<Self> {
                let n = *self; let mut res = vec![];
                for d in (1..).take_while(|&d| d * d <= n).filter(|&d| n % d == 0) {
                    res.push(d);
                    let dd = n / d;
                    if d != dd { res.push(dd); }
                }
                res.sort_unstable();
                res
            }
            fn prime_facts(&self) -> Vec<Self> {
                let mut n = *self; let mut res = vec![];
                for p in (2..).take_while(|&p| p * p <= *self) {
                    while n % p == 0 {
                        res.push(p);
                        n /= p;
                    }
                }
                if n > 1 { res.push(n); }
                res
            }
            fn prime_facts_map(&self) -> HashMap<Self, usize> {
                let ps = self.prime_facts();
                let mut map = HashMap::new();
                for p in ps {
                    *(map.entry(p).or_insert(0)) += 1;
                }
                map
            }
        }
    }; }
    impl_int_fact!(i64); impl_int_fact!(i32); impl_int_fact!(usize);
}
pub use int_fact::*;

// endregion: int_fact

#[cfg(test)]
mod tests_sieve {
    use super::*;

    #[test]
    fn test_linear_sieve() {
        let sieve = LinearSieve::new(1_000_000);
        assert_eq!(sieve.fact(120), vec![2, 2, 2, 3, 5]);
        assert_eq!(sieve.fact(0), vec![]);
        assert_eq!(sieve.fact(1), vec![]);
        assert_eq!(sieve.fact(2), vec![2]);
    }

    #[test]
    fn test_is_prime() {
        let sieve = LinearSieve::new(1_000_000);
        assert_eq!(sieve.is_prime(0), false);
        assert_eq!(sieve.is_prime(1), false);
        assert_eq!(sieve.is_prime(2), true);
        assert_eq!(sieve.is_prime(3), true);
        assert_eq!(sieve.is_prime(4), false);
        assert_eq!(sieve.is_prime(5), true);
        assert_eq!(sieve.is_prime(6), false);
    }
}

#[cfg(test)]
mod tests_int_fact {
    use std::collections::HashMap;

    use super::*;

    #[test]
    fn test_divisors() {
        assert_eq!(
            120.divisors(),
            vec![1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120]
        );
        assert_eq!(1.divisors(), vec![1]);

        assert_eq!(0.divisors(), vec![]);
        assert_eq!((-1).divisors(), vec![]);
    }

    #[test]
    fn test_prime_facts() {
        assert_eq!(120.prime_facts(), vec![2, 2, 2, 3, 5]);
        assert!(1.prime_facts().is_empty());
        assert!(0.prime_facts().is_empty());
        assert!((-1).prime_facts().is_empty());
    }

    #[test]
    fn test_prime_facts_map() {
        assert_eq!(
            120.prime_facts_map(),
            HashMap::from([(2, 3), (3, 1), (5, 1)])
        );
        assert_eq!(13.prime_facts_map(), HashMap::from([(13, 1)]));
        assert!(1.prime_facts_map().is_empty());
        assert!(0.prime_facts_map().is_empty());
        assert!((-1).prime_facts_map().is_empty());
    }
}
