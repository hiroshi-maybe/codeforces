///
/// Segment tree
/// =======
///
/// # Use cases
///
/// * Range query and point update for Monoid
/// * `RangeMinQuery` and `RangeMaxQuery` available out of the box
/// * Implement `Monoid` trait for custom range query
///
/// # Examples
///
/// ```
/// use cp_lib::RangeMinQuery;
/// let a = vec![2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9];
/// let mut rmq = RangeMinQuery::from(a);
///
/// assert_eq!(rmq.query(2..8), 1);
/// rmq.update(5, -1);
/// assert_eq!(rmq.query(2..8), -1);
///
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/a20169f8ffdd463b83a9aa28a8c1ba9c2b029baa/lib/range-query.cpp#L51
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/leetcode/blob/master/307-Range-Sum-Query/range-sum-query-mutable.rs#L36
/// * https://github.com/hiroshi-maybe/atcoder/blob/f634dc91bb9d3cea7df11b803fcb6af8ef296482/solutions/rectangle_gcd.rs#L87
///

// region: segment_tree

#[rustfmt::skip]
#[allow(dead_code)]
mod segment_tree {
    pub struct Min(i64);
    impl Monoid for Min {
        type V = i64;
        const IDENTITY: i64 = i64::max_value();
        fn binary_operation(a: &i64, b: &i64) -> i64 { *a.min(b) }
    }
    pub struct Max(i64);
    impl Monoid for Max {
        type V = i64;
        const IDENTITY: i64 = i64::min_value();
        fn binary_operation(a: &i64, b: &i64) -> i64 { *a.max(b) }
    }
    pub type RangeMinQuery = SegmentTree<Min>;
    pub type RangeMaxQuery = SegmentTree<Max>;

    pub trait Monoid {
        type V: Clone;
        const IDENTITY: Self::V;
        fn binary_operation(a: &Self::V, b: &Self::V) -> Self::V;
    }

    pub struct SegmentTree<M: Monoid> { n: usize, size: usize, dat: Vec<M::V>, }
    impl<M: Monoid> SegmentTree<M> {
        pub fn new(n: usize) -> SegmentTree<M> {
            let size = n.next_power_of_two();
            let dat = vec![M::IDENTITY; 2 * size];
            SegmentTree { n, size, dat }
        }
        pub fn merge_all(&mut self) {
            (1..self.size).rev().for_each(|i| self.merge(i));
        }
        pub fn query(&self, range: std::ops::Range<usize>) -> M::V {
            assert!(range.start <= range.end && range.end <= self.n);
            let (mut l, mut r) = (self.map_index(range.start), self.map_index(range.end));
            if l == r { return M::IDENTITY.clone(); }
            let (mut lval, mut rval) = (M::IDENTITY.clone(), M::IDENTITY.clone());
            while l < r {
                if l & 1 != 0 {
                    lval = M::binary_operation(&lval, &self.dat[l]);
                    l += 1;
                }
                if r & 1 != 0 {
                    r -= 1;
                    rval = M::binary_operation(&self.dat[r], &rval);
                }
                l >>= 1; r >>= 1;
            }
            M::binary_operation(&lval, &rval)
        }
        pub fn update(&mut self, i: usize, val: M::V) {
            assert!(i < self.n);
            let mut i = self.map_index(i);
            self.dat[i] = val;
            i >>= 1;
            while i > 0 { self.merge(i); i >>= 1; }
        }
        pub fn max_right<Pred: Fn(&M::V) -> bool>(&self, l: usize, pred: Pred) -> usize {
            assert!(l <= self.n);
            assert!(pred(&M::IDENTITY.clone()));
            if l == self.n { return self.n; }
            let mut l = self.map_index(l);
            let mut sum = M::IDENTITY.clone();
            while {
                // do
                while l % 2 == 0 { l >>= 1; }
                if !pred(&M::binary_operation(&sum, &self.dat[l])) {
                    while l < self.size {
                        l = 2 * l;
                        let res = M::binary_operation(&sum, &self.dat[l]);
                        if pred(&res) { sum = res; l += 1; }
                    }
                    return l - self.size;
                }
                sum = M::binary_operation(&sum, &self.dat[l]);
                l += 1;
                // while
                l.count_ones() > 1
            } {}
            self.n
        }
        pub fn min_left<Pred: Fn(&M::V) -> bool>(&self, r: usize, pred: Pred) -> usize {
            assert!(r <= self.n);
            assert!(pred(&M::IDENTITY.clone()));
            if r == 0 { return 0; }
            let mut r = self.map_index(r);
            let mut sum = M::IDENTITY.clone();
            while {
                // do
                r -= 1;
                while r > 1 && r % 2 == 1 { r >>= 1; }
                if !pred(&M::binary_operation(&self.dat[r], &sum)) {
                    while r < self.size {
                        r = 2 * r + 1;
                        let res = M::binary_operation(&self.dat[r], &sum);
                        if pred(&res) { sum = res; r -= 1; }
                    }
                    return r + 1 - self.size;
                }
                sum = M::binary_operation(&self.dat[r], &sum);
                // while
                r.count_ones() > 1
            } {}
            0
        }
        fn merge(&mut self, i: usize) {
            self.dat[i] = M::binary_operation(&self.dat[2 * i], &self.dat[2 * i + 1]);
        }
        fn map_index(&self, i: usize) -> usize { i + self.size }
    }

    impl<M: Monoid> From<&[M::V]> for SegmentTree<M> {
        fn from(v: &[M::V]) -> Self {
            let mut segtree = SegmentTree::new(v.len());
            segtree.dat[segtree.size..(segtree.size + v.len())].clone_from_slice(v);
            segtree.merge_all();
            segtree
        }
    }
    impl<M: Monoid> From<Vec<M::V>> for SegmentTree<M> {
        fn from(v: Vec<M::V>) -> Self { v[..].into() }
    }
}
pub use segment_tree::{Monoid, RangeMaxQuery, RangeMinQuery, SegmentTree};

// endregion: segment_tree

#[cfg(test)]
mod tests_segment_tree {
    use super::*;

    #[test]
    fn test_range_minimum_query() {
        let a = vec![2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9];
        let mut rmq = RangeMinQuery::from(a);

        assert_eq!(rmq.query(2..8), 1);
        assert_eq!(rmq.query(3..8), 2);
        rmq.update(5, -1);
        assert_eq!(rmq.query(2..8), -1);
    }

    #[test]
    fn test_range_maximum_query() {
        let a = vec![20, 1, 5, 3, 2, 3, 4, 5];
        let mut rmq = RangeMaxQuery::from(a);

        assert_eq!(rmq.query(1..4), 5);
        assert_eq!(rmq.query(0..8), 20);
        rmq.update(3, 100);
        assert_eq!(rmq.query(2..8), 100);
    }

    #[test]
    fn test_monoid() {
        pub struct Gcd(i64);
        impl Monoid for Gcd {
            type V = i64;
            const IDENTITY: i64 = 0;
            fn binary_operation(a: &i64, b: &i64) -> i64 {
                let mut m = *a;
                let mut n = *b;
                while m != 0 {
                    let temp = m;
                    m = n % temp;
                    n = temp;
                }
                n
            }
        }

        let a = vec![20, 12, 60, 28, 30, 50, 40, 5];
        let mut s = SegmentTree::<Gcd>::from(a);

        assert_eq!(s.query(1..4), 4);
        assert_eq!(s.query(0..8), 1);
        s.update(3, 24);
        assert_eq!(s.query(1..4), 12);
    }
}
