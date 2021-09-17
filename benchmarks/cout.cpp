#include <iostream>

using namespace std;

// $ g++ -std=c++11 -Wall -Ofast cout.cpp
// $ time ./a.out &>/dev/null
//
// ./a.out &> /dev/null  0.93s user 0.30s system 97% cpu 1.265 total
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i=0; i<(int)1e6; ++i) {
        cout<<i<<" ";
    }
    for(int i=0; i<(int)1e6; ++i) {
        cout<<i<<endl;
    }
}
