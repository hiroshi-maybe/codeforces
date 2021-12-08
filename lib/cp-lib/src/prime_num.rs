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
/// use cp_lib::Divisors;
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
    pub trait Divisors where Self: Sized { fn divisors(&self) -> Vec<Self>; }
    macro_rules! impl_int_fact { ($integer:ty) => {
        impl Divisors for $integer {
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
}

#[cfg(test)]
mod tests_int_fact {
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
}
