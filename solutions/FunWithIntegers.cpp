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
 
 11/16/2018
 
 17:42-18:00, 18:15-18:30 AC (no proof)
 
 https://codeforces.com/blog/entry/63199
 
 There are two points to be proved
  1. there exists Euler circuits
    Otherwise we need to find longest path in weighted graph from some starting vertex, which is NP hard
  2. All the vertices with edges are connected
    Otherwise, we need to compute sum of weights of each connected component and pick maximal one
 
 #1 can be proved that degree of vertices (-n,-n+1,..,-3,-2,2,3,..,n-1,n) with edges is even (weight for positive `x` and negative `x`), which is necessary and sufficient to form Eulerian circuit
 
 Proof of #2:
 
 Generally a*x=b <=> a, x and b are connected like a<->b<->x
 If a is 2, (2,a,b(=2*a)) are in the same component.
 If a>2 and a*x=b<=N, they are still in the same component like a<->b<->x
 a>2 that means there exists 2*x=b'(<=b). Thus a<->b<->x<->2 holds.
 Therefore a(>2) and 2 are eventually in the same component.
 This can be applied to any vertices with nonzero degree.
 All the vertices with nonzero degree are in the same component.
 
 Summary:
  - I just guessed the result and submit code without proof. It spoils chance of training 😡
 
 */

// 18:00 pause
// 18:30 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG FunWithIntegers.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[MAX_N];
int N;

LL f(LL N) {
  LL res=0;
  for(LL p=2; p*p<=N; ++p) if(N%p==0) {
    res+=4LL*p;
    if(p!=N/p) res+=4LL*N/p;
  }
  return res;
}

void solve() {
  LL res=0;
  FORE(n,2,N) res+=f(n);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  solve();
  
  return 0;
}
