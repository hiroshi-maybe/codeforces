///
/// bipartite_matching
/// =======
///
/// # Use cases
///
/// * Solver of bipartite matching problem by Ford-Fulkerson method, O(V*E) time
///
///  !!!! ⚠️ USE Dinic's algorithm for large E and V, which works in O(√V*E) time ⚠️ !!!!
///
///  - compute max flow of bipartite graph with capacity 1
///  - no need to add edges with source or sink
///  - in bipartite graph, maximum matching = vertex cover number (Ant book 3-5 network flow)
///   - generally size of maximum independent set + vertex cover number = V
///   - thus in bipartite graph size of maximum independent set = V - maximum matching
///
/// Properties of bipartite graph
///  - 2-coloring is possible
///  - Length of cycle is odd
///
/// References:
///  - Ant book 3-5 Network flow
///  - CLRS 26.3 Maximum bipartite matching
///  - https://en.wikipedia.org/wiki/Matching_(graph_theory)#In_unweighted_bipartite_graphs
///  - http://topcoder.g.hatena.ne.jp/agw/20120716/1342405575
///  - vertex cover: https://ja.wikipedia.org/wiki/%E9%A0%82%E7%82%B9%E8%A2%AB%E8%A6%86
///  - independent set: https://ja.wikipedia.org/wiki/%E7%8B%AC%E7%AB%8B%E9%9B%86%E5%90%88
///  - https://qiita.com/drken/items/7f98315b56c95a6181a4
///
/// # Examples
///
/// ```
/// use cp_lib::max_bipartite_matching;
/// let g = vec![
///     vec![5],
///     vec![5, 7],
///     vec![6, 7, 8],
///     vec![7],
///     vec![7],
///     vec![],
///     vec![],
///     vec![],
///     vec![],
/// ];
///
/// assert_eq!(max_bipartite_matching(&g), 3);
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/flow.cpp
///
/// # Used problems:
/// *
///

// region: bipartite_matching

#[allow(dead_code)]
mod bipartite_matching {
    fn dfs(
        u: usize,
        g: &Vec<Vec<usize>>,
        viz: &mut Vec<bool>,
        matched: &mut Vec<Option<usize>>,
    ) -> bool {
        viz[u] = true;
        for &v in &g[u] {
            if match matched[v] {
                None => true,
                Some(w) => !viz[w] && dfs(w, g, viz, matched),
            } {
                matched[v] = Some(u);
                matched[u] = Some(v);
                return true;
            }
        }
        false
    }
    pub fn max_bipartite_matching(g: &Vec<Vec<usize>>) -> usize {
        let n = g.len();
        let mut res = 0;
        let mut matched = vec![None; n];
        for u in 0..n {
            if matched[u].is_none() {
                let mut viz = vec![false; n];
                if dfs(u, &g, &mut viz, &mut matched) {
                    res += 1;
                }
            }
        }
        res
    }
}
pub use bipartite_matching::max_bipartite_matching;

// endregion: bipartite_matching

#[cfg(test)]
mod tests_bipartite_matching {
    use super::*;

    #[test]
    fn test_max_bipartite_matching() {
        let g = vec![
            vec![5],
            vec![5, 7],
            vec![6, 7, 8],
            vec![7],
            vec![7],
            vec![],
            vec![],
            vec![],
            vec![],
        ];

        assert_eq!(max_bipartite_matching(&g), 3);
    }
}
