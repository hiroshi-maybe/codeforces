///
/// Bitmask iterator utility
/// =======
///
/// # Use cases
///
/// * Iterate 0..1 << n
/// * Check or iterate i-th one bit in a binary representation
/// * BitSet APIs are inspired by {fixedbitset crate}[https://docs.rs/fixedbitset/latest/fixedbitset/index.html]
///
/// # Usage
///
/// ```
/// use cp_lib::{BitMask, BitSet};
///
/// let mut cnt = 0;
/// for bitset in BitMask::new(2) {
///     cnt += bitset.ones().count();
/// }
/// assert_eq!(cnt, 4);
///
/// let mut bitset = BitSet::from(5);
///
/// assert!(bitset[0]);
/// assert!(!bitset[1]);
/// assert!(bitset[2]);
/// assert_eq!(bitset.subset(0..2), BitSet::from(1));
/// assert!(bitset.put(1));
/// assert_eq!(bitset.val(), 7);
///
/// ```
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/bc06ff067fb2f828ec05f492ef6ceb3ea1a0fe86/solutions/many_formulas.rs#L43
/// * https://github.com/hiroshi-maybe/atcoder/blob/510db1272f7f295f405c0f359148c76a749fb39e/solutions/matrix_reducing.rs#L54
/// * https://github.com/hiroshi-maybe/atcoder/blob/7c3d34a0c9daf6ca8c8519a7962adff91fce9ded/solutions/booster.rs#L76
///

// region: bitmask
#[rustfmt::skip]
#[allow(dead_code)]
mod bitmask {
    #[derive(Debug, Copy, Clone)]
    pub struct BitMask(usize);
    impl BitMask {
        pub fn new(max_power_of_two: usize) -> BitMask { BitMask(max_power_of_two) }
        pub fn iter(&self) -> BitMaskIterator { BitMaskIterator(0..1<<self.0) }
    }
    impl IntoIterator for BitMask {
        type Item = BitSet; type IntoIter = BitMaskIterator;
        fn into_iter(self) -> Self::IntoIter { self.iter() }
    }

    //#[derive(IntoItarator)]
    pub struct BitMaskIterator(std::ops::Range<usize>);
    impl Iterator for BitMaskIterator {
        type Item = BitSet;
        fn next(&mut self) -> Option<Self::Item> {
            self.0.next().map(|m| BitSet(m))
        }
    }

    #[derive(PartialEq, Copy, Clone)]
    pub struct BitSet(usize);
    impl BitSet {
        pub fn full_bits(len: usize) -> BitSet { BitSet((1 << len) - 1) }
        pub fn contains(&self, i: usize) -> bool { (self.0 >> i) & 1 == 1 }
        pub fn ones(&self) -> BitSetBitsIterator { BitSetBitsIterator::new(BitSet(self.0), true) }
        pub fn zeros(&self) -> BitSetBitsIterator { BitSetBitsIterator::new(BitSet(self.0), false) }
        pub fn val(&self) -> usize { self.0 }
        pub fn put(&mut self, i: usize) -> bool { if self.contains(i) { false } else { self.0 |= 1 << i; true } }
        pub fn len(&self) -> usize {
            let bits = if usize::max_value() as u64 == u64::max_value() { 64 } else { 32 };
            (0..bits as usize).map(|i| self.contains(i)).rposition(std::convert::identity).map_or(0, |i| i+1)
        }
        pub fn subset(&self, range: std::ops::Range<usize>) -> BitSet {
            let mut dat = self.0; dat >>= range.start;
            BitSet::from(dat & ((1 << range.len()) -1))
        }
        pub fn concat<T: Into<BitSet>>(&self, other: T) -> BitSet {
            let other = other.into();
            BitSet::from((self.0 << other.len()) | other.val())
         }
    }
    impl From<usize> for BitSet {
        fn from(val: usize) -> BitSet { BitSet(val) }
    }
    impl std::ops::Index<usize> for BitSet {
        type Output = bool;
        fn index(&self, bit: usize) -> &bool {
            if self.contains(bit) { &true } else { &false }
        }
    }
    impl std::fmt::Debug for BitSet {
        fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
            let v = self.0;
            std::fmt::Binary::fmt(&v, f)
        }
    }
    pub struct BitSetBitsIterator { set: BitSet, iter: std::ops::Range<usize>, is_ones: bool }
    impl BitSetBitsIterator {
        pub fn new(set: BitSet, is_ones: bool) -> Self {
            BitSetBitsIterator {
                set: set, iter: 0..set.len(), is_ones: is_ones
            }
        }
    }
    impl Iterator for BitSetBitsIterator {
        type Item = usize;
        fn next(&mut self) -> Option<Self::Item> {
            let is_ones = self.is_ones; let set = self.set;
            self.iter.find(|&i| if is_ones { set.contains(i) } else { !set.contains(i) })
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
    fn test_bitset_contains() {
        let bs = BitSet::from(5);

        assert!(bs.contains(0));
        assert!(!bs.contains(1));
        assert!(bs.contains(2));
        assert!(!bs.contains(3));
    }

    #[test]
    fn test_bitset_index() {
        let bs = BitSet::from(5);

        assert!(bs[0]);
        assert!(!bs[1]);
        assert!(bs[2]);
        assert!(!bs[3]);
    }

    #[test]
    fn test_bitset_ones() {
        let mut it = BitSet::from(5).ones();

        assert_eq!(it.next(), Some(0));
        assert_eq!(it.next(), Some(2));
        assert_eq!(it.next(), None);
    }

    #[test]
    fn test_bitset_zeros() {
        let mut it = BitSet::from(5).zeros();

        assert_eq!(it.next(), Some(1));
        assert_eq!(it.next(), None);
    }

    #[test]
    fn test_bitset_val() {
        let bs = BitSet::from(5);
        assert_eq!(bs.val(), 5);

        let bs = BitSet::from(0);
        assert_eq!(bs.val(), 0);

        let bs = BitSet::from(usize::MAX);
        assert_eq!(bs.val(), usize::MAX);
    }

    #[test]
    fn test_bitset_put() {
        let mut bs = BitSet::from(0);
        assert_eq!(bs.put(1), true);
        assert_eq!(bs.val(), 2);

        assert_eq!(bs.put(1), false);
        assert_eq!(bs.val(), 2);

        assert_eq!(bs.put(4), true);
        assert_eq!(bs.val(), 18);
    }

    #[test]
    fn test_bitset_len() {
        let bs = BitSet::from(7);
        assert_eq!(bs.len(), 3);

        let bs = BitSet::from(0);
        assert_eq!(bs.len(), 0);
    }

    #[test]
    fn test_bitset_subset() {
        let bs = BitSet::from(21); // 10101
        assert_eq!(bs.subset(1..4), BitSet::from(2));
        assert_eq!(bs.subset(0..5), bs);
        assert_eq!(bs.subset(2..5), BitSet::from(5));
    }

    #[test]
    fn test_bitset_concat() {
        let bs1 = BitSet::from(21); // 10101
        let bs2 = BitSet::from(10); // 1010
        let bs = bs1.concat(bs2);
        assert_eq!(bs, BitSet::from((21 << 4) + 10));

        let bs = bs1.concat(10);
        assert_eq!(bs, BitSet::from((21 << 4) + 10));
    }

    #[test]
    fn test_bitset_full_bits() {
        let bs = BitSet::full_bits(3);
        assert_eq!(bs.val(), 7);

        let bs = BitSet::full_bits(7);
        assert_eq!(bs.val(), 127);
    }
}
