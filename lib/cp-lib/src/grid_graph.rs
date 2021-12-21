///
/// Grid graph
/// =======
///
/// # Use cases
///
/// * Provide iterators for adjacent cells
///
/// # Examples
///
/// ```
/// use cp_lib::GridGraph;
///
/// let g = GridGraph::new(10, 10);
///
/// let (i, j) = (1, 2);
/// for (ii, jj) in g.adj_cells4(i, j) {
///     assert_eq!((ii as i32 - i as i32).abs() + (jj as i32 - j as i32).abs(), 1);
/// }
///
/// ```
///
/// # References:
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/cpp-macro.h#L25
///

// region: grid_graph

#[rustfmt::skip]
#[allow(dead_code)]
mod grid_graph {
    pub struct GridGraph { h: usize, w: usize, }
    impl GridGraph { pub fn new(h: usize, w: usize) -> GridGraph { GridGraph { h, w } } }
    macro_rules! impl_adjacent_cells {
        ($method: ident, $iterator: ident, $moves: expr) => {
            impl GridGraph {
                pub fn $method(&self, i: usize, j: usize) -> $iterator {
                    assert!(i < self.h && j < self.w);
                    $iterator { cur: 0, i: i as i64, j: j as i64, w: self.w as i64, h: self.h as i64 }
                }
            }
            pub struct $iterator { cur: usize, i: i64, j: i64, w: i64, h: i64 }
            impl Iterator for $iterator {
                type Item = (usize, usize);
                fn next(&mut self) -> Option<Self::Item> {
                    for &(di,dj) in $moves[self.cur..].iter() {
                        self.cur += 1;
                        let (ii, jj) = (self.i + di, self.j + dj);
                        if (0..self.h).contains(&ii) && (0..self.w).contains(&jj) {
                            return Some((ii as usize, jj as usize));
                        }
                    }
                    None
                }
            }
        }
    }
    impl_adjacent_cells!(adj_cells4, AdjacentCells4, vec![(1,0),(0,1),(-1,0),(0,-1)]);
    impl_adjacent_cells!(adj_cells2, AdjacentCells2, vec![(1,0),(0,1)]);
}
pub use grid_graph::GridGraph;

// endregion: grid_graph

#[cfg(test)]
mod tests_grid_graph {
    use super::*;

    #[test]
    fn test_adj_cells4() {
        let g = GridGraph::new(10, 10);

        assert_eq!(
            g.adj_cells4(1, 1).collect::<Vec<_>>(),
            vec![(2, 1), (1, 2), (0, 1), (1, 0)]
        );

        assert_eq!(g.adj_cells4(0, 0).collect::<Vec<_>>(), vec![(1, 0), (0, 1)]);

        let g = GridGraph::new(1, 1);
        assert_eq!(g.adj_cells4(0, 0).collect::<Vec<_>>(), vec![]);
    }

    #[test]
    fn test_adj_cells2() {
        let g = GridGraph::new(10, 10);

        assert_eq!(
            g.adj_cells2(1, 1).collect::<Vec<_>>(),
            vec![(2, 1), (1, 2)]
        );

        assert_eq!(g.adj_cells2(9, 9).collect::<Vec<_>>(), vec![]);

        let g = GridGraph::new(1, 1);
        assert_eq!(g.adj_cells2(0, 0).collect::<Vec<_>>(), vec![]);
    }

    #[test]
    #[should_panic]
    fn test_invalid_cell() {
        let g = GridGraph::new(1, 1);
        let _it = g.adj_cells4(1, 0);
    }
}
