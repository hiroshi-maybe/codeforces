///
/// Cyclic detection
/// =======
///
/// # Use cases
///
/// * Detect cyclic in directed graph
///
/// # Examples
///
/// ```
/// use cp_lib::has_cyclic;
///
/// let g = vec![vec![1], vec![2], vec![0]];
/// println!("{}", if has_cyclic(&g) { "Yes" } else { "No" });
///
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/graph.cpp#L631
///
/// # Used problems:
/// * https://github.com/hiroshi-maybe/atcoder/blob/39399f69f5fe0cbffcc974c1a2e9d75eaaed4a12/solutions/pair_of_balls.rs#L37
///

// region: graph_has_cyclic

#[allow(dead_code)]
mod graph_has_cyclic {
    fn dfs(u: usize, g: &Vec<Vec<usize>>, viz: &mut Vec<usize>) -> bool {
        match viz[u] {
            0 => {
                viz[u] = 1;
                let res = g[u].iter().fold(false, |res, &v| res || dfs(v, g, viz));
                viz[u] = 2;
                res
            }
            1 => true,
            2 => false,
            _ => unreachable!(),
        }
    }
    pub fn has_cyclic(g: &Vec<Vec<usize>>) -> bool {
        let n = g.len();
        let mut viz = vec![0; n];
        (0..n).fold(false, |res, u| res | dfs(u, &g, &mut viz))
    }
}
pub use graph_has_cyclic::has_cyclic;

// endregion: graph_has_cyclic

#[cfg(test)]
mod tests_graph {
    use super::*;

    #[test]
    fn test_has_cyclic() {
        let g = vec![vec![1], vec![2], vec![0]];
        assert_eq!(has_cyclic(&g), true);

        let g = vec![vec![0], vec![]];
        assert_eq!(has_cyclic(&g), true);

        let g = vec![vec![1, 2, 3], vec![2, 4], vec![4], vec![], vec![]];
        assert_eq!(has_cyclic(&g), false);
    }
}
