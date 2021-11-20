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
