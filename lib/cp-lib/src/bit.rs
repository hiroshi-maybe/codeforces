///
/// Binary Indexed Tree (Fenwick tree)
/// =======
///
/// # Use cases
///
/// * Point update in O(lg N)
/// * Range sum query in O(lg N)
///
/// # Examples
///
/// ```
/// use cp_lib::BIT;
/// let a = vec![2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9];
/// let mut bit = BIT::new(a.len(), 0);
/// for i in 0..a.len() {
///     bit.add(i, a[i]);
/// }
/// bit.add(3, 6);
/// assert_eq!(bit.query_range(2..3), 1);
/// assert_eq!(bit.query_range(0..4), 13);
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/range-query.cpp
/// * https://cp-algorithms.com/data_structures/fenwick.html
/// * https://en.wikipedia.org/wiki/Fenwick_tree
/// * https://github.com/atcoder/ac-library/blob/master/document_ja/fenwicktree.md
/// * https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/fenwicktree.rs
///
/// # Used problems
///
/// * https://github.com/hiroshi-maybe/leetcode/blob/b80c649bd4dcc788f279f898e1a513f1cfa58366/775-global-and-local-inversions/global-and-local-inversions.rs#L9
/// * https://github.com/hiroshi-maybe/atcoder/blob/34252573b731ba310d088e4b8b39d2d6457eced0/solutions/leq.rs#L141
///

// region: bit

#[rustfmt::skip]
#[allow(dead_code)]
pub mod bit {
    pub struct BIT<T> { n: usize, dat: Vec<T>, /* dat[i] = ∑ { A[g(i)..=i] } */ identity: T }
    impl<T> BIT<T>
    where
        T: Clone + std::ops::AddAssign,
    {
        pub fn new(n: usize, identity: T) -> Self {
            BIT { n, dat: vec![identity.clone(); n], identity }
        }
        // A[pos] += delta
        pub fn add(&mut self, pos: usize, delta: T) {
            let mut i = pos + 1;
            while i <= self.n {
                self.dat[i - 1] += delta.clone();
                i = h(i);
            }
        }
        // query ∑ { A[i] : i=r.start..<r.end }
        pub fn query_range(&self, range: std::ops::Range<usize>) -> T
        where
            T: std::ops::Sub<Output = T>,
        {
            debug_assert!(range.start <= range.end);
            self.query(..range.end) - self.query(..range.start)
        }
        // query ∑ { A[i] : i=0..<r.end }
        pub fn query(&self, range: std::ops::RangeTo<usize>) -> T {
            let mut r = range.end;
            debug_assert!(r <= self.n);
            let mut res = self.identity.clone();
            while r > 0 {
                res += self.dat[r - 1].clone();
                r = std::cmp::max(g(r), 1) - 1;
            }
            res
        }
    }
    fn g(i: usize) -> usize { i & (i + 1) }
    fn h(i: usize) -> usize { i | (i + 1) }

    pub fn compress<T: Ord + Clone>(a: Vec<T>) -> Vec<usize> {
        let mut aa = a.clone();
        aa.sort_unstable();
        aa.dedup();
        let mut res = vec![];
        res.reserve(a.len());
        for i in 0..a.len() {
            res.push(aa.binary_search(&a[i]).unwrap());
        }
        res
    }
    pub fn inversions(a: &Vec<i32>) -> Vec<usize> {
        let a = compress(a.clone());
        let n = a.len();
        let mut bit = BIT::new(n, 0usize);
        let mut res = vec![0; n];
        for i in (0..n).rev() {
            res[i] = bit.query(..a[i]);
            bit.add(a[i], 1);
        }
        res
    }
}
pub use bit::{compress, inversions, BIT};

// endregion: bit

#[cfg(test)]
mod tests_modint {
    use super::*;

    #[test]
    fn test_bit() {
        let a = vec![2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9];
        let mut bit = BIT::new(a.len(), 0);
        for i in 0..a.len() {
            bit.add(i, a[i]);
        }
        assert_eq!(bit.query(..0), 0);
        assert_eq!(bit.query(..3), 4);
        assert_eq!(bit.query(..4), 7);

        bit.add(3, 6);
        assert_eq!(bit.query_range(2..3), 1);
        assert_eq!(bit.query_range(0..4), 13);
    }

    #[test]
    fn test_inversions() {
        let a = vec![2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9];
        let inversions = vec![2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0];

        assert_eq!(bit::inversions(&a), inversions);
    }
}
