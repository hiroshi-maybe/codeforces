#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/3/2018 ER48 div2
 
 9:15-9:45 gave up
 13:00-13:12 implement all zero approach seen in twitter TL and got AC
 
 I came up with all zero approach. However I made a mistake in verification.
 XOR{A[i]}^XOR{B[j]} = zero guarantees right mx[N-1][M-1]
 
         XOR
 0....01|1
 0....00|0
 0....01|1
 1....1z|x
 -------
 1....1y
 
 As shown above, x=XOR {mx[N-1][j] : j=0..M-1 }, y=XOR {mx[i][M-1] : i=0..N-1 }
 Then x ^ y should be 0
 
 Then there are two cases
 1) x=1,y=1
 2) x=0,y=0
 
 Suppose A=XOR {mx[N-1][j] : j=0..M-2 }, B=XOR {mx[i][M-1] : i=0..N-2 }
 
     A^z=x <=> z=A^x
 AND B^z=y <=> z=B^y
 
 1) x=1,y=1
 
 A=0,B=0 and z should be `1`
 
 2) x=0,y=0
 
 A=1,B=1 and z should be `0`
 
 Editorials:
  - http://codeforces.com/blog/entry/61015
  - http://betrue12.hateblo.jp/entry/2018/08/04/135456
  - https://twitter.com/tempura_pp/status/1025423228276113408
 
 Key:
  - Solve each bit independently
  - XOR {A} ^ XOR {B} should be zero because all the numbers are XORed twice
  - (N-1)x(M-1) matrix can be all zeros
 
 Summary:
  - fill all with zeroes and constructing with small effort is typical approach
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e2+1;
LL A[MAX_N],B[MAX_N];
int N,M;

// 9:45 give up

void assertmx(vector<VI> &mx) {
  REP(i,N) {
    int x=0;
    REP(j,M) x^=mx[i][j];
    assert(x==A[i]);
  }
  REP(j,M) {
    int x=0;
    REP(i,N) x^=mx[i][j];
    assert(x==B[j]);
  }
}

const string yes="YES",no="NO";
void solve() {
  LL x=0;
  REP(i,N)x^=A[i];
  REP(i,M)x^=B[i];
  if(x!=0) {
    cout<<no<<endl;
    return;
  }
  vector<VI> mx(N,VI(M,0));
  REP(i,31) {
    int y1=0;
    REP(r,N-1) {
      int x=(A[r]>>i)&1;
      mx[r][M-1]+=x<<i;
      y1^=x;
    }
    int y2=0;
    REP(c,M-1) {
      int x=(B[c]>>i)&1;
      mx[N-1][c]+=x<<i;
      y2^=x;
    }
    int c=(B[M-1]>>i)&1,r=(A[N-1]>>i)&1;
    mx[N-1][M-1]+=(y1^c)<<i;
    assert((y1^c)==(y2^r));
  }
  assertmx(mx);
  
  cout<<yes<<endl;
  REP(i,N) REP(j,M) cout<<mx[i][j]<<(j==M-1?'\n':' ');
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  REP(i,M) cin>>B[i];

  solve();
  
  return 0;
}
