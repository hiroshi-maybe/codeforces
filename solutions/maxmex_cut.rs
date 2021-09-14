#[allow(unused_imports)]
use std::cmp::*;
#[allow(unused_imports)]
use std::collections::*;
use std::io::{Write, BufWriter};
// https://qiita.com/tanakh/items/0ba42c7ca36cd29d0ac8
macro_rules! input {
    ($($r:tt)*) => {
        let stdin = std::io::stdin();
        let mut bytes = std::io::Read::bytes(std::io::BufReader::new(stdin.lock()));
        let mut next = move || -> String{
            bytes.by_ref().map(|r|r.unwrap() as char)
                .skip_while(|c|c.is_whitespace())
                .take_while(|c|!c.is_whitespace())
                .collect()
        };
        input_inner!{next, $($r)*}
    };
}

macro_rules! input_inner {
    ($next:expr) => {};
    ($next:expr,) => {};
    ($next:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($next, $t);
        input_inner!{$next $($r)*}
    };
}

macro_rules! read_value {
    ($next:expr, ( $($t:tt),* )) => { ($(read_value!($next, $t)),*) };
    ($next:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($next, $t)).collect::<Vec<_>>()
    };
    ($next:expr, chars) => {
        read_value!($next, String).chars().collect::<Vec<char>>()
    };
    ($next:expr, usize1) => (read_value!($next, usize) - 1);
    ($next:expr, [ $t:tt ]) => {{
        let len = read_value!($next, usize);
        read_value!($next, [$t; len])
    }};
    ($next:expr, $t:ty) => ($next().parse::<$t>().expect("Parse error"));
}

// $ rs-cp-batch maxmex_cut | diff maxmex_cut.out -
// $ cargo run maxmex_cut

///
/// 9/12/2021
///
/// 8:10-8:30 AC
///
/// https://codeforces.com/blog/entry/94803
///

fn is01(mx: &Vec<Vec<char>>, i: usize) -> bool {
    (mx[0][i]=='1'&&mx[1][i]=='0')||(mx[0][i]=='0'&&mx[1][i]=='1')
}

fn is_x(mx: &Vec<Vec<char>>, i: usize, c: char) -> bool {
    mx[0][i]==c&&mx[1][i]==c
}

fn main() {
    let out = std::io::stdout();
    let mut out = BufWriter::new(out.lock());
    macro_rules! puts {($($format:tt)*) => (let _ = write!(out,$($format)*););}
    input! {
        t: usize,
        a: [(usize, [chars; 2]); t],
    }

    for (n, mx) in a {
        let mut res=0;
        let mut i=0;

        // let is01=|i: usize| (mx[0][i]=='1'&&mx[1][i]=='0')||(mx[0][i]=='0'&&mx[1][i]=='1');
        // let is_x=|i: usize, c:char| mx[0][i]==c&&mx[1][i]==c;

        while i<n {
            if is01(&mx, i) {
                res+=2;
                i+=1;
            } else if is_x(&mx,i,'0') && (i<n-1&&is_x(&mx,i+1,'1')) {
                res+=2;
                i+=2;
            } else if is_x(&mx,i,'1') && (i<n-1&&is_x(&mx,i+1,'0')) {
                res+=2;
                i+=2;
            } else {
                res+=if is_x(&mx,i,'1') { 0 } else { 1 };
                i+=1;
            }
        }

        puts!("{}\n", res);
    }


}
