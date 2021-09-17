#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// $ g++ -std=c++11 -Wall -Ofast scanf.cpp
// time ./a.out < 1e6int.input
//
// ./a.out < 1e6int.input  0.17s user 0.01s system 47% cpu 0.384 total
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; scanf("%d", &n);
    vector<long long> a;
    a.reserve(n);
    for(int i=0; i<n; ++i) scanf("%lld", &a[i]);
    printf("%d\n", n);
}
