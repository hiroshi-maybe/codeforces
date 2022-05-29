///
/// Geometry
/// =======
///
/// # Use cases
///
/// - `Point` data structure for 2D vector operations
///
/// # Examples
///
/// ```
/// use cp_lib::{Point};
///
/// let p1 = Point::new(1, -1);
/// let p2 = Point::new(10, 100);
///
/// assert_eq!(p1 + p2, Point::new(11, 99));
/// assert_eq!(p1.det(p2), 110);
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/geometry.cpp
///

// region: geometry

#[rustfmt::skip]
#[allow(dead_code)]
pub mod geometry {
    use std::ops::*;

    #[derive(Copy, Clone, Debug, Default, Hash, PartialEq, Eq, PartialOrd, Ord)]
    pub struct Point<T> { pub x: T, pub y: T }
    impl<T> Point<T> {
        pub fn new(x: T, y: T) -> Self { Point { x, y } }
    }
    impl<T: Mul<Output = T> + Sub<Output = T>> Point<T> {
        pub fn det(self, other: Point<T>) -> T { self.x * other.y - self.y * other.x }
    }
    impl<T> From<(T, T)> for Point<T> {
        fn from(t: (T, T)) -> Point<T> { Point::<T>::new(t.0, t.1) }
    }
    impl<U: Into<Point<T>>, T: Add<Output = T>> Add<U> for Point<T> {
        type Output = Self;
        fn add(self, other: U) -> Self {
            let other = other.into();
            Self::new(self.x + other.x, self.y + other.y)
        }
    }
    impl<U: Into<Point<T>>, T: Sub<Output = T>> Sub<U> for Point<T> {
        type Output = Self;
        fn sub(self, other: U) -> Self {
            let other = other.into();
            Self::new(self.x - other.x, self.y - other.y)
        }
    }
    impl<U: Into<Point<T>>, T: Add<Output = T> + Copy> AddAssign<U> for Point<T> {
        fn add_assign(&mut self, other: U) { *self = *self + other; }
    }
    impl<U: Into<Point<T>>, T: Sub<Output = T> + Copy> SubAssign<U> for Point<T> {
        fn sub_assign(&mut self, other: U) { *self = *self - other; }
    }
}
pub use geometry::Point;

// endregion: mod_int

#[cfg(test)]
mod tests_geometry {
    use super::*;

    #[test]
    fn test_new() {
        let (x, y) = (1, -1);
        let p = Point::new(x, y);

        assert_eq!(p.x, x);
        assert_eq!(p.y, y);
    }

    #[test]
    fn test_from() {
        let t = (1, -1);
        let p = Point::from(t);

        assert_eq!(p.x, t.0);
        assert_eq!(p.y, t.1);
    }

    #[test]
    fn test_add() {
        let (x1, y1) = (10, 20);
        let (x2, y2) = (3, 4);

        let p1 = Point::new(x1, y1);
        let p2 = Point::new(x2, y2);

        let p3 = p1 + p2;
        assert_eq!(p3.x, x1 + x2);
        assert_eq!(p3.y, y1 + y2);

        let p3 = p1 + (x2, y2);
        assert_eq!(p3.x, x1 + x2);
        assert_eq!(p3.y, y1 + y2);
    }

    #[test]
    fn test_add_assign() {
        let (x1, y1) = (10, 20);
        let (x2, y2) = (3, 4);

        let p1 = Point::new(x1, y1);
        let p2 = Point::new(x2, y2);

        let mut p3 = p1;
        p3 += p2;
        assert_eq!(p3, p1 + p2);

        let mut p3 = p1;
        p3 += (x2, y2);
        assert_eq!(p3, p1 + p2);
    }

    #[test]
    fn test_sub() {
        let (x1, y1) = (10, 20);
        let (x2, y2) = (3, 4);

        let p1 = Point::new(x1, y1);
        let p2 = Point::new(x2, y2);

        let p3 = p1 - p2;
        assert_eq!(p3.x, x1 - x2);
        assert_eq!(p3.y, y1 - y2);

        let p3 = p1 - (x2, y2);
        assert_eq!(p3.x, x1 - x2);
        assert_eq!(p3.y, y1 - y2);
    }

    #[test]
    fn test_sub_assign() {
        let (x1, y1) = (10, 20);
        let (x2, y2) = (3, 4);

        let p1 = Point::new(x1, y1);
        let p2 = Point::new(x2, y2);

        let mut p3 = p1;
        p3 -= p2;
        assert_eq!(p3, p1 - p2);

        let mut p3 = p1;
        p3 -= (x2, y2);
        assert_eq!(p3, p1 - p2);
    }

    #[test]
    fn test_det() {
        let (x1, y1) = (10, 20);
        let (x2, y2) = (3, 4);

        let p1 = Point::new(x1, y1);
        let p2 = Point::new(x2, y2);

        assert_eq!(p1.det(p2), x1 * y2 - y1 * x2);
    }
}
