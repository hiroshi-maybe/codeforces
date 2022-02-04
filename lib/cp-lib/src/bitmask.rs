///
/// Bitmask iterator utility
/// =======
///
/// # Use cases
///
/// * Iterate 0..1 << n
/// * Check or iterate i-th one bit in a binary representation
///
/// # Usage
///
/// ```
/// use cp_lib::BitMask;
///
/// let mut cnt = 0;
/// for mask in BitMask::new(2) {
///     cnt += mask.ones().count();
/// }
/// assert_eq!(cnt, 4);
/// ```
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/3deda6b69b5d0141dc73918a3eb67e0662c4b71c/solutions/many_formulas.rs#L43
///

// region: bitmask
#[rustfmt::skip]
#[allow(dead_code)]
mod bitmask {
    #[derive(Debug, Copy, Clone)]
    pub struct BitMask(usize);
    impl BitMask {
        pub fn new(max_power_of_two: usize) -> BitMask { BitMask(max_power_of_two) }
        pub fn iter(&self) -> BitMaskIterator { BitMaskIterator { cur: 0, max_power_of_two: self.0 } }
    }
    impl IntoIterator for BitMask {
        type Item = BitSet; type IntoIter = BitMaskIterator;
        fn into_iter(self) -> Self::IntoIter { self.iter() }
    }
    pub struct BitMaskIterator { cur: usize, max_power_of_two: usize, }
    impl Iterator for BitMaskIterator {
        type Item = BitSet;
        fn next(&mut self) -> Option<Self::Item> {
            if self.cur < 1 << self.max_power_of_two {
                let bitset = self.cur;
                self.cur += 1;
                Some(BitSet(bitset))
            } else {
                None
            }
        }
    }

    #[derive(Debug, PartialEq, Copy, Clone)]
    pub struct BitSet(usize);
    impl BitSet {
        pub fn ith(&self, i: usize) -> bool { (self.0 >> i) & 1 == 1 }
        pub fn ones(&self) -> BitSetOnesIterator { BitSetOnesIterator { current_bit: 0, mask: *self } }
    }
    impl From<usize> for BitSet {
        fn from(val: usize) -> BitSet { BitSet(val) }
    }
    pub struct BitSetOnesIterator { current_bit: usize, mask: BitSet }
    impl Iterator for BitSetOnesIterator {
        type Item = usize;
        fn next(&mut self) -> Option<Self::Item> {
            let len = (self.mask.0.count_ones() + self.mask.0.count_zeros()) as usize;
            if let Some(next_bit) = (self.current_bit..len).find(|&i| self.mask.ith(i)) {
                self.current_bit = next_bit + 1;
                Some(next_bit)
            } else {
                None
            }
        }
    }
}
pub use bitmask::{BitMask, BitSet};
// endregion: bitmask

#[cfg(test)]
mod tests_bitmask {
    use super::*;

    #[test]
    fn test_bitmask() {
        let mut it = BitMask::new(3).iter();

        for m in 0usize..(1 << 3) {
            assert_eq!(it.next(), Some(BitSet::from(m)));
        }
        assert_eq!(it.next(), None);

        let mut it = BitMask::new(0).iter();
        assert_eq!(it.next(), Some(BitSet::from(0)));
        assert_eq!(it.next(), None);
    }

    #[test]
    fn test_bitset_ith() {
        let bs = BitSet::from(5);

        assert!(bs.ith(0));
        assert!(!bs.ith(1));
        assert!(bs.ith(2));
        assert!(!bs.ith(3));
    }

    #[test]
    fn test_bitset_ones() {
        let mut it = BitSet::from(5).ones();

        assert_eq!(it.next(), Some(0));
        assert_eq!(it.next(), Some(2));
        assert_eq!(it.next(), None);
    }
}
