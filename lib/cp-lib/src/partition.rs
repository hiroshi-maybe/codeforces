///
/// Utility to binary search partition position
/// =======
///
/// # Use cases
///
/// * Find the position to partition with a shim of partition_point()
///
/// # Examples
///
/// ```
/// ```
///
/// # References:
/// * https://github.com/rust-lang/rust/pull/73577
/// * https://doc.rust-lang.org/std/vec/struct.Vec.html#method.partition_point
/// * https://codeforces.com/contest/1626/submission/142997904
///
///
/// # Used problems:
/// *
///

// region: partition

// #[rustfmt::skip]
#[allow(dead_code)]
mod partition {
    use std::cmp::Ordering;
    pub trait PartitionSlice {
        type Item;
        /// Find the partition point for which left segment satisifies the predicate
        /// items = [true, true, true, false, false]
        ///                            ^ res
        fn _partition_point<P>(&self, pred: P) -> usize
        where
            P: FnMut(&Self::Item) -> bool;
    }

    impl<T> PartitionSlice for [T] {
        type Item = T;
        fn _partition_point<P>(&self, mut pred: P) -> usize
        where
            P: FnMut(&T) -> bool,
        {
            self.binary_search_by(|x| {
                if pred(x) {
                    Ordering::Less
                } else {
                    Ordering::Greater
                }
            })
            .unwrap_or_else(std::convert::identity)
        }
    }
}
pub use partition::PartitionSlice;

// endregion: partition

#[cfg(test)]
mod tests_partition {
    use super::*;

    #[test]
    fn test_partition_point() {
        let a = vec![1, 2, 3, 3, 4, 4, 5, 100];

        assert_eq!(a._partition_point(|&x| x < 1), 0);
        assert_eq!(a._partition_point(|&x| x < 2), 1);
        assert_eq!(a._partition_point(|&x| x < 3), 2);
        assert_eq!(a._partition_point(|&x| x < 4), 4);
        assert_eq!(a._partition_point(|&x| x < 99), 7);
        assert_eq!(a._partition_point(|&x| x < 100), 7);
        assert_eq!(a._partition_point(|&x| x < 101), 8);

        let a = vec![5, 3, 1, 3, 100, 4];
        assert_eq!(a._partition_point(|&x| x % 2 == 1), 4);
        assert_eq!(a._partition_point(|&x| x % 2 == 0), 0);
    }
}
