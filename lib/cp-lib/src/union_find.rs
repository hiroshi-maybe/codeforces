///
/// Union-find tree
/// =======
///
/// # Use cases
///
/// * Disjoint set union
///   * Merge and find disjoint sets in O(α(n)), where α(n) is the inverse Ackermann function
///
/// # Examples
///
/// ```
/// use cp_lib::UnionFind;
/// let mut uf = UnionFind::new(10);
///
/// assert_eq!(uf.group_count, 10);
///
/// uf.merge(1, 3);
/// assert_eq!(uf.same_set(1, 3), true);
/// assert_eq!(uf.size(1), 2);
/// assert_eq!(uf.size(3), 2);
/// assert_eq!(uf.find(1), uf.find(3));
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/unionfind.cpp
/// * https://cp-algorithms.com/data_structures/disjoint_set_union.html
/// * https://github.com/rust-lang-ja/ac-library-rs/blob/master/src/dsu.rs
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/7feab571939e2e743356c32469aea228ba7730ac/solutions/linear_probing.rs#L21
/// * https://github.com/hiroshi-maybe/atcoder/blob/8a6b4a1328db02190a19174c0ba4323e0479e36c/solutions/reversible_cards.rs#L23
///

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
    pub struct UnionFind {
        pub group_count: usize,
        par: Vec<usize>, sizes: Vec<usize>,
    }
    impl UnionFind {
        pub fn new(n: usize) -> UnionFind {
            let par = (0..n).map(|i| i).collect::<Vec<_>>();
            UnionFind { group_count: n, par, sizes: vec![1; n], }
        }
        pub fn find(&mut self, x: usize) -> usize {
            if self.par[x] == x { x } else {
                self.par[x] = self.find(self.par[x]);
                self.par[x]
            }
        }
        pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.find(x) == self.find(y) }
        pub fn size(&mut self, x: usize) -> usize {
            let x = self.find(x);
            self.sizes[x]
        }
        pub fn merge(&mut self, x: usize, y: usize) -> usize {
            let (mut p, mut c) = (self.find(x), self.find(y));
            if p == c { return p; }
            if self.sizes[p] < self.sizes[c] { std::mem::swap(&mut p, &mut c); }
            self.group_count -= 1;
            self.sizes[p] += self.sizes[c];
            self.par[c] = p;
            p
        }
        pub fn roots(&mut self) -> Vec<usize> {
            (0..self.par.len()).filter(|&u| self.find(u) == u).collect::<Vec<_>>()
        }
    }
}
pub use uf::UnionFind;

// endregion: union_find

#[cfg(test)]
mod tests_uf {
    use super::*;

    #[test]
    fn test_union_find() {
        let mut uf = UnionFind::new(10);
        uf.merge(1, 3);

        assert_eq!(uf.same_set(1, 3), true);
        assert_eq!(uf.size(1), 2);
        assert_eq!(uf.size(3), 2);
        assert_eq!(uf.group_count, 9);

        uf.merge(4, 6);
        uf.merge(0, 2);
        uf.merge(7, 8);
        uf.merge(0, 1);
        uf.merge(4, 5);
        uf.merge(1, 2);

        assert_eq!(uf.same_set(0, 3), true);
        assert_eq!(uf.same_set(4, 6), true);
        assert_eq!(uf.same_set(7, 8), true);
        assert_eq!(uf.group_count, 4);
        for root in uf.roots() {
            assert_eq!(uf.find(root), root);
        }
    }
}
