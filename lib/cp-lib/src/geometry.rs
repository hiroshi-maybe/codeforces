///
/// Geometry
/// =======
///
/// # Use cases
///
/// - `Point` data structure for 2D vector operations
///
/// # Cross product
///
/// ## Cross product u×v
///
/// u×v = det(u,v)
///  = u.x * v.y - u.y * v.x
///  = |u|*|v|*sin𝛩
///  = area of parallelogram formed by u and v
///
/// 1) u×v = det(u,v) = 0
///    u and v are colinear from origin
/// 2) u×v = det(u,v) > 0
///    u is clockwise from v
/// 3) u×v = det(u,v) < 0
///    u is counter-clockwise from v
///
/// ## Cross product det (o->p1, o->p2)
///
///  1) det(o,p1,p2) = 0
///     o, p1 and p2 are co-linear (o->p1 is colinear with o->p2)
///  2) det(o,p1,p2) > 0
///     o->p2 is counter-clockwise from o->p1
///     (p1->p2->o is counter-clockwise order)
///  3) det(o,p1,p2) < 0
///     o->p2 is clockwise from o->p1
///     (p1->p2->o is clockwise order)
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
/// assert!(p1.det(p2) > 0);
///
/// let p3 = Point::new(2, -2);
/// assert_eq!(p1.det(p3), 0); // co-linear
///
/// let p0 = Point::from((0, 0));
/// assert_eq!(p0.det_origin(p1, p3), 0) // co-linear
///
/// ```
///
/// # References:
///
/// * https://github.com/hiroshi-maybe/topcoder/blob/master/lib/geometry.cpp
///
/// # Used problems:
/// 
/// * https://github.com/hiroshi-maybe/atcoder/blob/6eb6fe23b63b17409b0b20b205ac5ec8586876e4/solutions/kcolinear_line.rs#L19
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
    impl<T: Mul<Output = T> + Sub<Output = T> + Copy> Point<T> {
        pub fn det<U: Into<Point<T>>>(&self, other: U) -> T {
            let other = other.into();
            self.x * other.y - self.y * other.x
        }
        pub fn det_origin<U1: Into<Point<T>>, U2: Into<Point<T>>>(self, other1: U1, other2: U2) -> T {
            let (u, v) = (other1.into() - self, other2.into() - self);
            u.det(v)
        }
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

// endregion: geometry

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
        assert_eq!(p1.det((x2, y2)), p1.det(p2));

        let p1 = Point::from((1, 0));
        let p2 = Point::from((0, -1));
        assert!(p1.det(p2) < 0);
        assert_eq!(p1.det((2, 0)), 0);

        let p3 = Point::new(3, 0);
        assert_eq!(p1.det_origin((2,0), p3), 0);
    }
}
