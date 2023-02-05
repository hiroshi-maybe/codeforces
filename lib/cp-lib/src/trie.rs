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
mod trie {
    use std::{collections::HashSet, str::Chars};
    pub struct Trie {
        root_node: Box<TrieNode>,
    }

    impl Trie {
        pub fn new() -> Self {
            Trie {
                root_node: Box::new(TrieNode::new()),
            }
        }

        pub fn insert(&mut self, id: usize, str: &str) {
            self.root_node.insert(id, str.chars())
        }

        pub fn erase(&mut self, id: usize, str: &str) -> bool {
            self.root_node.erase(id, str.chars())
        }

        pub fn search(&self, str: &str) -> Option<usize> {
            let node = self.root_node.find(str.chars());
            node.and_then(|n| n.ending_str_ids.iter().next().copied())
        }

        pub fn prefix_cnt(&self, str: &str) -> usize {
            let node = self.root_node.find(str.chars());
            node.map_or(0, |n| n.matched_string_cnt)
        }
    }

    struct TrieNode {
        matched_string_cnt: usize,      // # of strings in the subtree of the node
        ending_str_ids: HashSet<usize>, // IDs of strings ending here
        children: [Option<Box<TrieNode>>; 26],
    }

    impl TrieNode {
        const INIT: Option<Box<TrieNode>> = None;
        fn new() -> Self {
            TrieNode {
                matched_string_cnt: 0,
                ending_str_ids: HashSet::new(),
                children: [Self::INIT; 26],
            }
        }

        fn child_node_index(&self, c: &char) -> usize {
            (*c as u8 - b'a') as usize
        }

        fn insert(&mut self, id: usize, mut cs: Chars) {
            self.matched_string_cnt += 1;
            if let Some(c) = cs.next() {
                let i = self.child_node_index(&c);
                if let Some(child) = self.children[i].as_mut() {
                    child.insert(id, cs);
                } else {
                    let mut child = Box::new(TrieNode::new());
                    child.insert(id, cs);
                    self.children[i] = Option::Some(child);
                }
            } else {
                self.ending_str_ids.insert(id);
            }
        }

        fn erase(&mut self, id: usize, mut cs: Chars) -> bool {
            if let Some(c) = cs.next() {
                let i = self.child_node_index(&c);
                if let Some(child) = self.children[i].as_mut() {
                    child.erase(id, cs)
                } else {
                    false
                }
            } else {
                self.ending_str_ids.remove(&id)
            }
        }

        fn find(&self, mut cs: Chars) -> Option<&TrieNode> {
            if let Some(c) = cs.next() {
                let i = self.child_node_index(&c);
                if let Some(child) = self.children[i].as_ref() {
                    child.find(cs)
                } else {
                    None
                }
            } else {
                Some(self)
            }
        }
    }
}
pub use trie::Trie;
// endregion: trie

#[cfg(test)]
mod tests_trie_tree {
    use super::*;

    #[test]
    fn test_insert_and_search() {
        let mut trie = Trie::new();
        trie.insert(0, "apple");

        assert_eq!(trie.search("apple"), Some(0));
        assert_eq!(trie.search("appl"), None);

        trie.insert(1, "app");

        assert_eq!(trie.search("app"), Some(1));
        assert_eq!(trie.search("appl"), None);
        assert_eq!(trie.prefix_cnt("app"), 2);
    }

    #[test]
    fn test_insert_and_erase() {
        let mut trie = Trie::new();
        trie.insert(0, "apple");
        trie.insert(1, "app");

        assert_eq!(trie.erase(0, "app"), false);
        assert_eq!(trie.erase(1, "app"), true);
        assert_eq!(trie.search("app"), None);
    }
}
