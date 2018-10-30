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
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 10/28/2018
 
 13:57-14:35 give up
 
 10/29/2018
 
 15:10-18:10 read editorial and got AC
 
 http://codeforces.com/blog/entry/62612
 
 Proof by parity
  - https://togetter.com/li/1279466?page=3
  - https://twitter.com/tempura_pp/status/1054022786828578817
  - https://codeforces.com/contest/1071/submission/44661618
 
 How to solve this problem?
  - observation that result is always "YES" if N>=8. Proof is preferred
  - observation that A+{a,b,c,d,e,f} => A' + {0,0,0,0,0,0} is possible in 2 operations
   - this can be guessed from # of maximum operations. try smaller chunks.
  - brute-force is feasible if N is small
  - solve smaller subproblem to solve larger N. Keep processing chunk of 6 elements and solve last 10 elements by brute-force
  - floor(N/3) is showing 1 op for 3 elements, 2 ops for 6 elements, 3 ops for 9 elements,.... We can look for such sufficient operations.
 
 Summary:
  - If it's hard to figure out general solution, solve small problem by brute-force and try to discover something
  - If something is found for small set, we may be able to apply it to chunk of small pieces.
  - Guess from maximal # of operations.
  - Induce from small cases. Reduce it to a large problem.
  - How to solve it?
   - Should you introduce some auxiliary element in order to make its use possible?
   - Could you solve a part of the problem (smaller problem)?
   - If you have solved the problem, what should be feasible?
  - So many missing pieces for me
   - experiment and guess from constraint
   - analysis and proof from constraint
   - construction in small cases by hand
  - I didn't even have a chance to solve by small `d` (=y-x=z-y). Thus I didn't have an idea of experiment. Remember that it may be possible to dig cases with small values. Especially in this problem, we may want to process from left to right. Then using large `d` may be cumbersome.
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[MAX_N];
int N;

void end() {
  cout<<"NO"<<endl;
  exit(0);
}
void solve() {
  vector<III> res;
  auto flip=[&](int x, int d) {
    int y=x+d,z=y+d;
    A[x]^=1,A[y]^=1,A[z]^=1;
    res.emplace_back(x,y,z);
  };
  int i1=0;
  while(i1<N&&A[i1]==0) ++i1;
  int i2=i1+1;
  while(i2<N&&A[i2]==0) ++i2;
  while(i1<N-2) {
    int d=i2-i1;
    if(i1<N-8&&A[i1]==1&&A[i1+1]==1&&A[i1+2]==0) {
      if(A[i1+4]==1&&A[i1+5]==1) {
        d=4;
      } else if(A[i1+3]==0) {
        d=1;
      } else {
        d=3;
      }
    } else if(i2+d<N) {
      d=i2-i1;
    } else {
      d=(N-1-i1)/2;
    }
    flip(i1,d);
    ++i1;
    while(i1<N&&A[i1]==0) ++i1;
    i2=i1+1;
    while(i2<N&&A[i2]==0) ++i2;
  }
  
  if(A[N-1]==1) {
    if(N<7) end();
    flip(N-7,3),flip(N-7,1),flip(N-6,1);
  }
  if(A[N-2]==1) {
    if(N<8) end();
    flip(N-8,3),flip(N-8,1),flip(N-7,1);
  }
  cout<<"YES"<<endl;
  cout<<SZ(res)<<endl;
  REP(i,SZ(res)) {
    int x,y,z; tie(x,y,z)=res[i];
    println("%d %d %d",x+1,y+1,z+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}
