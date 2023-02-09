///
/// Trie tree
/// =======
///
/// # Use cases
/// * Find the longest prefix match by pre-processing strings and building a tree
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
        root_node: Box<TrieNode<C>>,
        _marker: PhantomData<C>,
    }

    pub trait CharSet: Copy {
        const DAT_SIZE: usize;
        const BASE: u8;
        fn char_to_u8(c: char) -> u8 {
            c as u8 - Self::BASE
        }
    }

    #[derive(Copy, Clone)]
    pub struct LowerAlphabetSet;
    impl CharSet for LowerAlphabetSet {
        const DAT_SIZE: usize = 26;
        const BASE: u8 = b'a';
    }

    impl<C: CharSet> Trie<C> {
        pub fn new() -> Self {
            Trie {
                root_node: Box::new(TrieNode::new()),
                _marker: PhantomData,
            }
        }

        pub fn insert(&mut self, id: usize, cs: Vec<char>) {
            let cs = Self::normalize(cs);
            self.root_node.insert(id, cs.as_slice())
        }

        pub fn erase(&mut self, id: usize, cs: Vec<char>) -> bool {
            let cs = Self::normalize(cs);
            self.root_node.erase(id, cs.as_slice())
        }

        pub fn search(&self, cs: Vec<char>) -> Option<usize> {
            let cs = Self::normalize(cs);
            let node = self.root_node.find(cs.as_slice());
            node.and_then(|n| n.terminated_str_ids.iter().next().copied())
        }

        pub fn prefix_cnt(&self, cs: Vec<char>) -> usize {
            let cs = Self::normalize(cs);
            let node = self.root_node.find(cs.as_slice());
            node.map_or(0, |n| n.matched_string_cnt)
        }

        fn normalize(cs: Vec<char>) -> Vec<u8> {
            cs.iter().map(|&c| C::char_to_u8(c)).collect::<Vec<_>>()
        }
    }

    #[derive(Clone)]
    struct TrieNode<C: CharSet> {
        matched_string_cnt: usize, // # of strings in the subtree of the node
        terminated_str_ids: HashSet<usize>, // IDs of strings ending here
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

        fn find(&self, cs: &[u8]) -> Option<&TrieNode<C>> {
            if let Some(c) = cs.first() {
                let i = *c as usize;
                if let Some(child) = self.children[i].as_ref() {
                    child.find(&cs[1..])
                } else {
                    None
                }
            } else {
                Some(self)
            }
        }
    }
}
pub use trie::{CharSet, LowerAlphabetSet, LowerAlphabetTrie, Trie};
// endregion: trie

#[cfg(test)]
mod tests_trie_tree {
    use super::*;

    #[test]
    fn test_insert_and_search() {
        let mut trie = LowerAlphabetTrie::new();
        trie.insert(0, "apple".chars().collect());

        assert_eq!(trie.search("apple".chars().collect()), Some(0));
        assert_eq!(trie.search("appl".chars().collect()), None);

        trie.insert(1, "app".chars().collect());

        assert_eq!(trie.search("app".chars().collect()), Some(1));
        assert_eq!(trie.search("appl".chars().collect()), None);
        assert_eq!(trie.prefix_cnt("app".chars().collect()), 2);
    }

    #[test]
    fn test_insert_and_erase() {
        let mut trie = LowerAlphabetTrie::new();
        trie.insert(0, "apple".chars().collect());
        trie.insert(1, "app".chars().collect());

        assert_eq!(trie.erase(0, "app".chars().collect()), false);
        assert_eq!(trie.erase(1, "app".chars().collect()), true);
        assert_eq!(trie.search("app".chars().collect()), None);
    }
}
