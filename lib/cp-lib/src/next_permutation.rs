// region: next_permutation
#[rustfmt::skip]
#[allow(dead_code)]
pub fn next_permutation<T>(xs: &mut [T]) -> bool
where
    T: std::cmp::Ord,
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
// endregion: next_permutation

#[cfg(test)]
mod tests_comb {
    use super::*;

    fn assert_next_permutation(xs: &mut Vec<i32>, expected: Vec<Vec<i32>>) {
        for (i, ys) in expected.iter().enumerate() {
            assert_eq!(*xs, *ys);
            assert_eq!(next_permutation(xs), i < expected.len() - 1);
        }
    }

    #[test]
    fn test_next_permutation_empty() {
        let mut xs: Vec<i32> = vec![];
        assert_eq!(next_permutation(&mut xs), false);
    }

    #[test]
    fn test_next_permutation_one() {
        let mut xs = vec![1];
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
