///
/// Prefix sum libraries
/// =======
///
/// # Use cases
///
/// * Compute 2d prefix sum in the area represented by the left top point (i1, j1) and right bottom point (i2, j2)
///
/// # Examples
///
/// ```
/// use cp_lib::PrefixSum2d;
///
/// let mx = vec![
///    vec![3, 0, 1, 4, 2],
///    vec![5, 6, 3, 2, 1],
///    vec![1, 2, 0, 1, 5],
///    vec![4, 1, 0, 1, 7],
///    vec![1, 0, 3, 0, 5],
/// ];
/// let cum = PrefixSum2d::from(&mx);
/// assert_eq!(cum.query((2, 1), (5, 4)), 8);
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/gcd.cpp
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/ab69a3bff6c7bbdd81ecb1e2be477e6d7f5fed77/solutions/grid_filling.rs#L67
///

// region: prefixsum2d
#[rustfmt::skip]
#[allow(dead_code)]
mod prefixsum2d {
    pub struct PrefixSum2d<T> { r: usize, c: usize, prefix_sum: Vec<Vec<T>>, }
    pub trait Zero { const ZERO: Self; }

    macro_rules! impl_zero {
        ($integer:ty) => { impl Zero for $integer { const ZERO: $integer = 0; } };
    }
    impl_zero!(i64);

    impl<T: Zero + Clone + Copy + std::ops::Add<Output = T> + std::ops::Sub<Output = T>>
        PrefixSum2d<T>
    {
        pub fn from(mx: &Vec<Vec<T>>) -> Self {
            let (r, c) = (mx.len(), mx[0].len());
            let mut prefix_sum = vec![vec![T::ZERO; c + 1]; r + 1];
            for i in 0..r {
                for j in 0..c {
                    prefix_sum[i + 1][j + 1] =
                        prefix_sum[i + 1][j] + prefix_sum[i][j + 1] - prefix_sum[i][j] + mx[i][j];
                }
            }
            PrefixSum2d::<T> { r, c, prefix_sum }
        }

        pub fn query(&self, p1: (usize, usize), p2: (usize, usize)) -> T {
            self.prefix_sum[p2.0][p2.1] - self.prefix_sum[p1.0][p2.1] - self.prefix_sum[p2.0][p1.1]
                + self.prefix_sum[p1.0][p1.1]
        }
    }
}
pub use prefixsum2d::*;
// endregion: prefixsum2d

#[cfg(test)]
mod tests_prefixsum2d {
    use super::*;

    #[test]
    fn test_query() {
        let mx = vec![
            vec![3, 0, 1, 4, 2],
            vec![5, 6, 3, 2, 1],
            vec![1, 2, 0, 1, 5],
            vec![4, 1, 0, 1, 7],
            vec![1, 0, 3, 0, 5],
            vec![1, 2, 3, 4, 5],
        ];

        let ps = PrefixSum2d::from(&mx);
        assert_eq!(ps.query((2, 1), (5, 4)), 8);
        assert_eq!(ps.query((1, 1), (3, 3)), 11);
        assert_eq!(ps.query((1, 2), (3, 5)), 12);
        assert_eq!(ps.query((1, 2), (1, 2)), 0);
        assert_eq!(ps.query((1, 2), (0, 1)), 0);
    }
}
