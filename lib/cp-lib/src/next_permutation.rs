///
/// next_permutation
/// =======
///
/// # Use cases
///
/// * Find next lexicographically larger sequence
///
/// # Examples
///
/// ```
/// use cp_lib::next_permutation;
/// let mut p = vec![1, 1, 0, 2];
/// p.sort();
///
/// loop {
///     println!("{:?}", p);
///
///     if !next_permutation(&mut p) {
///         break;
///     }
/// }
///
///
/// ```
///
/// # References:
/// * https://aloso.github.io/2021/03/09/creating-an-iterator
///   * for iterator implementation
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/66166d65b5c8b7069dd0b6170d6410555a75e35a/solutions/select_mul.rs#L51
/// * https://github.com/hiroshi-maybe/atcoder/blob/4d9dae43eba33accb93600ee4981e78baf085766/solutions/abc_identity.rs#L34
///

// region: next_permutation

#[rustfmt::skip]
#[allow(dead_code)]
mod permutation {
    pub fn next_permutation<T>(xs: &mut [T]) -> bool
        where T: std::cmp::Ord
    {
        let asc_i = match xs.windows(2).rposition(|w| w[0] < w[1]) {
            Some(i) => i,
            None => { return false; }
        };
        let min_larger_offset = xs[asc_i + 1..]
            .binary_search_by(|x| match xs[asc_i].cmp(x) {
                std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
                ord => ord,
            })
            .unwrap_err();
        xs.swap(asc_i, asc_i + min_larger_offset);
        xs[asc_i + 1..].reverse();
        true
    }

    pub trait Permutations<T> {
        fn next_permutations(&self) -> Permutation<'_, T> where Self: Sized;
    }
    impl<T> Permutations<T> for Vec<T> where T: std::cmp::Ord {
        fn next_permutations(&self) -> Permutation<'_, T> {
            Permutation::new(&self[..])
        }
    }
    pub struct Permutation<'a, T> {
        dat: &'a [T],
        map: Vec<usize>,
        cnt: i64,
    }
    impl<'a, T: std::cmp::Ord> Permutation<'a, T> {
        fn new(dat: &'a [T]) -> Permutation<'a, T> {
            Permutation { dat, map: (0..dat.len()).collect::<Vec<_>>(), cnt: 0 }
        }
        fn get_ith(&self, i: usize) -> &'a T {
            &self.dat[self.map[i]]
        }
    }

    impl<'a, T: std::cmp::Ord> Iterator for Permutation<'a, T> {
        type Item = Vec<&'a T>;

        fn next(&mut self) -> Option<Self::Item> {
            let n = self.dat.len();
            let res = (0..n).map(|i| self.get_ith(i)).collect::<Vec<_>>();
            if self.cnt < 0 { return None; }
            if n == 0 {
                if self.cnt == 0 { self.cnt=-1; return Some(res); }
            }

            if let Some(asc_i) = (0..n - 1).rposition(|i0| self.get_ith(i0) < self.get_ith(i0 + 1)) {
                let min_larger_offset = (asc_i + 1..n).map(|i| self.get_ith(i)).collect::<Vec<_>>()
                    .binary_search_by(|x| match self.get_ith(asc_i).cmp(x) {
                        std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
                        ord => ord,
                    })
                    .unwrap_err();
                self.map.swap(asc_i, asc_i + min_larger_offset);
                self.map[asc_i + 1..].reverse();
                self.cnt += 1;
                Some(res)
            } else {
                self.cnt = -1;
                Some(res)
            }
        }
    }
}
pub use permutation::next_permutation;
pub use permutation::Permutations;

// endregion: next_permutation

#[cfg(test)]
mod tests_comb {
    use super::*;

    fn assert_next_permutation(xs: &mut Vec<i32>, expected: Vec<Vec<i32>>) {
        let mut it = xs.next_permutations();
        let mut i = 0;
        while let Some(ys) = it.next() {
            for j in 0..xs.len() {
                assert_eq!(*ys[j], expected[i][j]);
            }
            i += 1;
        }

        for (i, ys) in expected.iter().enumerate() {
            assert_eq!(*xs, *ys);
            assert_eq!(next_permutation(xs), i < expected.len() - 1);
        }
    }

    #[test]
    fn test_next_permutation_empty() {
        let mut xs: Vec<i32> = vec![];
        let mut it = xs.next_permutations();
        assert_eq!(it.next(), Some(vec![]));
        assert_eq!(it.next(), None);
        assert_eq!(next_permutation(&mut xs), false);
    }

    #[test]
    fn test_next_permutation_one() {
        let mut xs = vec![1];
        let mut it = xs.next_permutations();
        assert_eq!(it.next(), Some(vec![&xs[0]]));
        assert_eq!(it.next(), None);
        assert_eq!(next_permutation(&mut xs), false);
    }

    #[test]
    fn test_next_permutation_two() {
        let expected = vec![vec![1, 2], vec![2, 1]];
        let mut xs = vec![1, 2];
        assert_next_permutation(&mut xs, expected);

        let expected = vec![vec![1, 1]];
        let mut xs = vec![1, 1];
        assert_next_permutation(&mut xs, expected);
    }

    #[test]
    fn test_next_permutation_three() {
        let expected = vec![
            vec![1, 2, 3],
            vec![1, 3, 2],
            vec![2, 1, 3],
            vec![2, 3, 1],
            vec![3, 1, 2],
            vec![3, 2, 1],
        ];
        let mut xs = vec![1, 2, 3];
        assert_next_permutation(&mut xs, expected);

        let expected = vec![vec![1, 1, 2], vec![1, 2, 1], vec![2, 1, 1]];
        let mut xs = vec![1, 1, 2];
        assert_next_permutation(&mut xs, expected);
    }
}
