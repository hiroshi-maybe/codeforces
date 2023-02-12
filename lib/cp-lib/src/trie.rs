///
/// Trie tree
/// =======
///
/// # Use cases
/// * Find the longest prefix match by pre-processing strings and building a tree
///
/// # Usage
/// ```
/// use cp_lib::LowerAlphabetTrie;
///
/// let mut trie = LowerAlphabetTrie::new();
/// 
/// trie.insert(0, "apple");
/// assert_eq!(trie.search("apple"), Some(0));
/// assert_eq!(trie.search("appl"), None);
///
/// trie.insert(1, "app");
/// assert_eq!(trie.search("app"), Some(1));
/// assert_eq!(trie.search("appl"), None);
/// assert_eq!(trie.prefix_cnt("app"), 2);
/// ```
///
/// # Used problems
/// * https://github.com/hiroshi-maybe/atcoder/blob/7597da3164ac5ea67e00185553ae340834cdad00/solutions/karuta.rs#L70
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/trie.cpp
///

// region: trie
#[allow(dead_code)]
mod trie {
    use std::collections::HashSet;
    use std::marker::PhantomData;
    pub type LowerAlphabetTrie = Trie<LowerAlphabetSet>;
    pub struct Trie<C: CharSet> {
        pub root_node: Box<TrieNode<C>>,
        _marker: PhantomData<C>,
    }

    pub trait CharSet: Copy {
        const DAT_SIZE: usize;
        const BASE: u8;
        fn char_to_u8(c: char) -> u8 {
            c as u8 - Self::BASE
        }
    }

    pub struct TrieNodeIterator<'a, C: CharSet> {
        str: Vec<u8>,
        cur_pos: usize,
        cur_node: &'a Box<TrieNode<C>>,
    }
    impl<'a, C> Iterator for TrieNodeIterator<'a, C>
    where
        C: CharSet,
    {
        type Item = &'a TrieNode<C>;
        fn next(&mut self) -> Option<Self::Item> {
            if let Some(child) = self
                .str
                .get(self.cur_pos)
                .and_then(|&c| self.cur_node.children[c as usize].as_ref())
            {
                self.cur_node = child;
                self.cur_pos += 1;
                Some(child)
            } else {
                None
            }
        }
    }

    #[derive(Copy, Clone, Debug)]
    pub struct LowerAlphabetSet;
    impl CharSet for LowerAlphabetSet {
        const DAT_SIZE: usize = 26;
        const BASE: u8 = b'a';
    }

    pub trait StringEncodable {
        fn encode<C: CharSet>(&self) -> Vec<u8>;
        fn char_count(&self) -> usize;
    }

    impl StringEncodable for &str {
        fn encode<C: CharSet>(&self) -> Vec<u8> {
            self.chars().map(|c| C::char_to_u8(c)).collect()
        }

        fn char_count(&self) -> usize {
            self.chars().count()
        }
    }

    impl StringEncodable for Vec<char> {
        fn encode<C: CharSet>(&self) -> Vec<u8> {
            self.iter().map(|&c| C::char_to_u8(c)).collect()
        }
        fn char_count(&self) -> usize {
            self.len()
        }
    }

    impl StringEncodable for &Vec<char> {
        fn encode<C: CharSet>(&self) -> Vec<u8> {
            self.iter().map(|&c| C::char_to_u8(c)).collect()
        }

        fn char_count(&self) -> usize {
            self.len()
        }
    }

    impl<C: CharSet> Trie<C> {
        pub fn new() -> Self {
            Trie {
                root_node: Box::new(TrieNode::new()),
                _marker: PhantomData,
            }
        }

        pub fn insert<S: StringEncodable>(&mut self, id: usize, str: S) {
            let cs = str.encode::<C>();
            self.root_node.insert(id, cs.as_slice())
        }

        pub fn erase<S: StringEncodable>(&mut self, id: usize, str: S) -> bool {
            let cs = str.encode::<C>();
            self.root_node.erase(id, cs.as_slice())
        }

        pub fn search<S: StringEncodable>(&self, str: S) -> Option<usize> {
            self.find(str)
                .and_then(|n| n.terminated_str_ids.iter().next().copied())
        }

        pub fn prefix_cnt<S: StringEncodable>(&self, str: S) -> usize {
            self.find(str).map_or(0, |n| n.matched_string_cnt)
        }

        pub fn find<S: StringEncodable>(&self, str: S) -> Option<&TrieNode<C>> {
            let len = str.char_count();
            self.node_iter(str).enumerate().last().and_then(|(i, n)| {
                if i == len - 1 {
                    Some(n)
                } else {
                    None
                }
            })
        }

        pub fn node_iter<S: StringEncodable>(&self, str: S) -> TrieNodeIterator<C> {
            let cs = str.encode::<C>();
            TrieNodeIterator::<C> {
                str: cs,
                cur_pos: 0,
                cur_node: &self.root_node,
            }
        }
    }

    #[derive(Clone, Debug)]
    pub struct TrieNode<C: CharSet> {
        pub matched_string_cnt: usize, // # of strings in the subtree of the node
        pub terminated_str_ids: HashSet<usize>, // IDs of strings ending here
        children: Vec<Option<Box<TrieNode<C>>>>,
        _marker: PhantomData<C>,
    }

    impl<C: CharSet> TrieNode<C> {
        const INIT: Option<Box<TrieNode<C>>> = None;
        fn new() -> Self {
            TrieNode {
                matched_string_cnt: 0,
                terminated_str_ids: HashSet::new(),
                children: vec![Self::INIT; C::DAT_SIZE],
                _marker: PhantomData,
            }
        }

        fn insert(&mut self, id: usize, cs: &[u8]) {
            self.matched_string_cnt += 1;
            if let Some(c) = cs.first() {
                let i = *c as usize;
                if let Some(child) = self.children[i].as_mut() {
                    child.insert(id, &cs[1..]);
                } else {
                    let mut child = Box::new(TrieNode::new());
                    child.insert(id, &cs[1..]);
                    self.children[i] = Option::Some(child);
                }
            } else {
                self.terminated_str_ids.insert(id);
            }
        }

        fn erase(&mut self, id: usize, cs: &[u8]) -> bool {
            if let Some(c) = cs.first() {
                let i = *c as usize;
                if let Some(child) = self.children[i].as_mut() {
                    child.erase(id, &cs[1..])
                } else {
                    false
                }
            } else {
                self.terminated_str_ids.remove(&id)
            }
        }
    }
}
pub use trie::{CharSet, LowerAlphabetSet, LowerAlphabetTrie, StringEncodable, Trie};
// endregion: trie

#[cfg(test)]
mod tests_trie_tree {
    use super::*;

    #[test]
    fn test_insert_and_search() {
        let mut trie = LowerAlphabetTrie::new();
        trie.insert(0, "apple");

        assert_eq!(trie.search("apple"), Some(0));
        assert_eq!(trie.search("appl"), None);

        trie.insert(1, "app".chars().collect::<Vec<_>>());

        assert_eq!(trie.search("app"), Some(1));
        assert_eq!(trie.search("appl"), None);
        assert_eq!(trie.prefix_cnt("app"), 2);
    }

    #[test]
    fn test_insert_and_erase() {
        let mut trie = LowerAlphabetTrie::new();
        trie.insert(0, "apple");
        trie.insert(1, "app".chars().collect::<Vec<_>>());

        assert_eq!(trie.erase(0, "app"), false);
        assert_eq!(trie.erase(1, "app"), true);
        assert_eq!(trie.search("app"), None);
    }

    #[test]
    fn test_iterator() {
        let mut trie = LowerAlphabetTrie::new();
        trie.insert(0, "apple");

        let mut it = trie.node_iter("app");
        let n = it.next();
        assert_eq!(n.unwrap().matched_string_cnt, 1);
        let n = it.next();
        assert_eq!(n.unwrap().matched_string_cnt, 1);
        let n = it.next();
        assert_eq!(n.unwrap().matched_string_cnt, 1);
        assert!(it.next().is_none());
    }
}
