#include <iostream>

using namespace std;

// $ g++ -std=c++11 -Wall -Ofast printf.cpp
// $ time ./a.out &>/dev/null
//
// ./a.out &> /dev/null  0.27s user 0.01s system 48% cpu 0.557 total
int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i=0; i<(int)1e6; ++i) {
        printf("%d ", i);
    }
    for(int i=0; i<(int)1e6; ++i) {
        printf("%d\n", i);
    }
}
