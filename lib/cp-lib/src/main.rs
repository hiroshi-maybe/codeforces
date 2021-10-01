use cp_lib::{Com, ModInt1000000007};

fn main() {
    let com = Com::<ModInt1000000007>::new(3_000_000);
    println!("{}", com.choose(100, 50));
}
