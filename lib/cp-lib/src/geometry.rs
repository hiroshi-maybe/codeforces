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
/// * https://qiita.com/tydesign/items/7cb4d189451095b4d667
///   * for circle intersection
///
/// # Used problems:
///
/// * https://github.com/hiroshi-maybe/atcoder/blob/6eb6fe23b63b17409b0b20b205ac5ec8586876e4/solutions/kcolinear_line.rs#L19
/// * https://github.com/hiroshi-maybe/atcoder/blob/8b76c86b81d85047419d048fe7aa3f6628531451/solutions/counterclockwise_rotation.rs#L30
///   * 2D rotation
/// * https://github.com/hiroshi-maybe/atcoder/blob/6d455dc8e6163b38be71c0aa9df99e93b6d13ec9/solutions/circumferences.rs#L58
///   * Circle intersection
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
    impl<T: Mul<Output = T> + Add<Output = T> + PartialOrd + Copy> Point<T> {
        pub fn dist(&self) -> T {
            self.x * self.x + self.y * self.y
        }
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

    pub fn deg2rad(deg: f64) -> f64 { deg * std::f64::consts::PI / 180.0 }
    impl<T: Into<f64> + Copy> Point<T> {
        pub fn rotate(&self, degree: f64) -> Point<f64> {
            let rad = deg2rad(degree);
            let (c, s) = (rad.cos(), rad.sin());
            let (x, y) = (self.x.into(), self.y.into());
            Point::<f64>::new(x * c - y * s, x * s + y * c)
        }
    }

    const EPS: f64 = 1e-6;
    impl Point<f64> {
        pub fn equal_with_eps(&self, other: &Self) -> bool {
            (self.x-other.x).abs() <= EPS && (self.y-other.y).abs() <= EPS
        }
    }

    pub struct Circle<T> { pub origin: Point<T>, pub radius: T }
    impl<T> Circle<T> {
        pub fn new<U: Into<Point<T>>>(point: U, radius: T) -> Circle<T> {
            Circle { origin: point.into(), radius }
        }
    }
    impl<T: Sub<Output = T> + Mul<Output = T> + Add<Output = T> + PartialOrd + Copy> Circle<T> {
        pub fn is_on_arc(&self, point: Point<T>) -> bool {
            (point - self.origin).dist() == self.radius * self.radius
        }
        pub fn is_inside(&self, point: Point<T>) -> bool {
            (point - self.origin).dist() <= self.radius * self.radius
        }
        pub fn has_intersection(&self, other: &Circle<T>) -> bool {
            let d = (self.origin - other.origin).dist();
            (self.radius - other.radius) * (self.radius - other.radius) <= d
            && d <= (self.radius + other.radius) * (self.radius + other.radius)
        }
    }
}
pub use geometry::{Circle, Point};

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
        assert_eq!(p1.det_origin((2, 0), p3), 0);
    }

    #[test]
    fn test_rotate() {
        let p = Point::new(5.0, 0.0);
        assert!(p
            .rotate(120.0)
            .equal_with_eps(&Point::new(-2.49999999999999911182, 4.33012701892219364908)));
    }

    #[test]
    fn test_circle_inside() {
        let c = Circle::new((2, 0), 2);
        assert!(c.is_inside(Point::new(1, 1)));
    }

    #[test]
    fn test_circle_intersection() {
        let c1 = Circle::new((0, 0), 2);
        let c2 = Circle::new((3, 0), 2);
        assert!(c1.has_intersection(&c2));

        let c3 = Circle::new((3, 3), 1);
        assert!(c2.has_intersection(&c3));
    }
}
