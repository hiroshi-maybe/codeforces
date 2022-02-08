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
/// assert_eq!(uf.root(1), uf.root(3));
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
/// * https://github.com/hiroshi-maybe/atcoder/blob/780d25af84fd7cc0e5f21dfe8f407d787d11e0bc/solutions/sum_of_maximum_weights.rs#L20
/// * https://github.com/hiroshi-maybe/atcoder/blob/bbbe96fc9d1a6a21449889e61f6acd209a7215b0/solutions/destruction.rs#L16
/// * https://github.com/hiroshi-maybe/atcoder/blob/f852d84f195ed184a5a544452b19b9c660e70f6d/solutions/bridge.rs#L39
/// * https://github.com/hiroshi-maybe/atcoder/blob/3d3fb3ee32fc028824707166bca0febba3da9a7c/solutions/mst_1.rs#L54
/// * https://github.com/hiroshi-maybe/atcoder/blob/ae67b896152e7d7a4e61815d8365c9da72b6893c/solutions/range_sums.rs#L34
///

// region: union_find

#[rustfmt::skip]
#[allow(dead_code)]
mod uf {
    pub struct UnionFind {
        pub group_count: usize,
        par_or_size: Vec<isize>,
    }
    impl UnionFind {
        pub fn new(n: usize) -> UnionFind {
            UnionFind { group_count: n, par_or_size: vec![-1; n], }
        }
        pub fn root(&mut self, x: usize) -> usize {
            if self.par_or_size[x] < 0 as isize { x } else {
                self.par_or_size[x] = self.root(self.par_or_size[x] as usize) as isize;
                self.par_or_size[x] as usize
            }
        }
        pub fn same_set(&mut self, x: usize, y: usize) -> bool { self.root(x) == self.root(y) }
        pub fn size(&mut self, x: usize) -> usize {
            let root = self.root(x); -self.par_or_size[root] as usize
        }
        pub fn merge(&mut self, x: usize, y: usize) -> usize {
            let (mut p, mut c) = (self.root(x), self.root(y));
            if p == c { return p; }
            if -self.par_or_size[p] < -self.par_or_size[c] { std::mem::swap(&mut p, &mut c); }
            self.group_count -= 1;
            self.par_or_size[p] += self.par_or_size[c];
            self.par_or_size[c] = p as isize;
            p
        }
        pub fn roots(&mut self) -> Vec<usize> {
            (0..self.par_or_size.len()).filter(|&u| self.root(u) == u).collect::<Vec<_>>()
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
            assert_eq!(uf.root(root), root);
        }
    }
}
