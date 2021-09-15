#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// $ g++ -std=c++11 -Wall -Ofast cin.cpp
// time ./a.out < 1e6int.input
//
// ./a.out < 1e6int.input  3.15s user 0.08s system 92% cpu 3.495 total
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n; cin>>n;
    vector<long long> a;
    a.reserve(n);
    for(int i=0; i<n; ++i) cin>>a[i];
    cout<<n<<endl;
}
