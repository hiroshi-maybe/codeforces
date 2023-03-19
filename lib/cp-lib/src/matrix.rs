///
/// Matrix
/// =======
///
/// # Use cases
///
/// * Matrix operations
///
/// # Examples
///
/// ```
/// use cp_lib::{Matrix};
///
/// let mx1 = Matrix::<i64>::from(&vec![vec![1, 2], vec![3, 4], vec![5, 6]]);
/// let mx2 = Matrix::<i64>::from(&vec![vec![1, 2, 3], vec![4, 5, 6]]);
/// let res = mx1 * mx2;
/// assert_eq!(
///     res,
///     Matrix::<i64>::from(&vec![vec![9, 12, 15], vec![19, 26, 33], vec![29, 40, 51]])
/// );
///
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/matrix.cpp
///

// region: matrix

// #[rustfmt::skip]
#[allow(dead_code)]
pub mod matrix {
    use std::ops::{Add, AddAssign, Index, Mul, MulAssign};

    pub trait MatrixElement {
        type InternalValue: Clone + Copy;
        const ZERO: Self::InternalValue;
        const ONE: Self::InternalValue;
    }
    impl MatrixElement for i64 {
        type InternalValue = Self;
        const ZERO: Self::InternalValue = 0;
        const ONE: Self::InternalValue = 1;
    }

    #[derive(Debug, Default, Hash, PartialEq, Eq)]
    pub struct Matrix<Element: MatrixElement> {
        n: usize,
        m: usize,
        dat: Vec<Vec<Element::InternalValue>>,
    }
    impl<Element: MatrixElement> Matrix<Element> {
        pub fn new(n: usize, m: usize) -> Self {
            let dat = vec![vec![Element::ZERO; m]; n];
            Matrix { n, m, dat }
        }
    }
    impl<Element: MatrixElement> Matrix<Element>
    where
        Matrix<Element>: MulAssign<Self>,
    {
        /// res = A^n, O(N^3*lg n) time
        pub fn pow(&self, mut exp: u64) -> Self {
            assert_eq!(self.n, self.m);
            let mut res = Matrix::<Element>::new(self.n, self.n);
            for i in 0..self.n {
                res.dat[i][i] = Element::ONE;
            }
            let mut a = self.clone();
            while exp > 0 {
                if exp & 1 == 1 {
                    res *= a.clone();
                }
                a *= a.clone();
                exp >>= 1;
            }
            res
        }
    }
    impl<Element: MatrixElement> Clone for Matrix<Element> {
        fn clone(&self) -> Self {
            Self {
                n: self.n.clone(),
                m: self.m.clone(),
                dat: self.dat.clone(),
            }
        }
    }
    impl<Element: MatrixElement> Index<usize> for Matrix<Element> {
        type Output = Vec<Element::InternalValue>;

        fn index(&self, index: usize) -> &Self::Output {
            &self.dat[index]
        }
    }
    impl<Element: MatrixElement> From<&Vec<Vec<Element::InternalValue>>> for Matrix<Element> {
        fn from(v: &Vec<Vec<Element::InternalValue>>) -> Self {
            let (n, m) = (v.len(), v[0].len());
            let mut matrix = Matrix::new(n, m);
            for i in 0..n {
                matrix.dat[i] = v[i].clone();
            }
            matrix
        }
    }
    impl<Element, Rhs> AddAssign<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Add<Output = Element::InternalValue>,
    {
        fn add_assign(&mut self, rhs: Rhs) {
            let rhs = rhs.into();
            assert_eq!(self.n, rhs.n);
            assert_eq!(self.m, rhs.m);
            for i in 0..self.n {
                for j in 0..self.m {
                    self.dat[i][j] = self[i][j] + rhs[i][j];
                }
            }
        }
    }
    impl<Element, Rhs> MulAssign<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Mul<Output = Element::InternalValue> + AddAssign,
    {
        fn mul_assign(&mut self, rhs: Rhs) {
            let rhs = rhs.into();
            assert_eq!(self.m, rhs.n);
            let mut new_mx = Matrix::<Element>::new(self.n, rhs.m);
            for i in 0..self.n {
                for j in 0..rhs.m {
                    for k in 0..self.m {
                        new_mx.dat[i][j] += self[i][k] * rhs[k][j];
                    }
                }
            }
            *self = new_mx;
        }
    }
    impl<Element, Rhs> Add<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Add<Output = Element::InternalValue>,
    {
        type Output = Self;
        fn add(self, rhs: Rhs) -> Self {
            let mut res = self.clone();
            res += rhs;
            res
        }
    }
    impl<Element, Rhs> Mul<Rhs> for Matrix<Element>
    where
        Element: MatrixElement,
        Rhs: Into<Matrix<Element>>,
        Element::InternalValue: Mul<Output = Element::InternalValue> + AddAssign,
    {
        type Output = Self;
        fn mul(self, rhs: Rhs) -> Self::Output {
            let mut res = self.clone();
            res *= rhs;
            res
        }
    }
}
pub use matrix::Matrix;

// endregion: matrix

#[cfg(test)]
mod tests_matrix {
    use super::*;

    #[test]
    fn test_new() {
        let mx = Matrix::<i64>::new(2, 3);
        for i in 0..2 {
            for j in 0..3 {
                assert_eq!(mx[i][j], 0);
            }
        }
    }

    #[test]
    fn test_from() {
        let vec = vec![vec![1, 2, 3], vec![4, 5, 6]];
        let mx = Matrix::<i64>::from(&vec);
        for i in 0..vec.len() {
            for j in 0..vec[0].len() {
                assert_eq!(mx[i][j], vec[i][j]);
            }
        }
    }

    #[test]
    fn test_add() {
        let mx1 = Matrix::<i64>::from(&vec![vec![1, 2, 3], vec![4, 5, 6]]);
        let mx2 = Matrix::<i64>::from(&vec![vec![10, 20, 30], vec![40, 50, 60]]);
        let res = mx1 + mx2;
        assert_eq!(
            res,
            Matrix::<i64>::from(&vec![vec![11, 22, 33], vec![44, 55, 66]])
        );
    }

    #[test]
    fn test_mul() {
        let mx1 = Matrix::<i64>::from(&vec![vec![1, 2], vec![3, 4], vec![5, 6]]);
        let mx2 = Matrix::<i64>::from(&vec![vec![1, 2, 3], vec![4, 5, 6]]);
        let res = mx1 * mx2;
        assert_eq!(
            res,
            Matrix::<i64>::from(&vec![vec![9, 12, 15], vec![19, 26, 33], vec![29, 40, 51]])
        );
    }

    #[test]
    fn test_pow() {
        let a = Matrix::<i64>::from(&vec![vec![1, 2], vec![3, 4]]);
        let expected = a.clone() * a.clone() * a.clone();

        assert_eq!(a.pow(3), expected);
    }
}
