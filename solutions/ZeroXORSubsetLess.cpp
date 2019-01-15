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

// $ ../batch ZeroXORSubsetLess | diff ZeroXORSubsetLess.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ZeroXORSubsetLess.cpp && ./a.out

/*
 
 1/12/2019
 
 16:06-16:45 give up
 
 1/14/2019
 
 18:15-19:30, 21:30-22:50 read wikipedia and editorial and got AC
 
 https://codeforces.com/blog/entry/64483
 https://codeforces.com/blog/entry/64483?#comment-484135
 https://qiita.com/kuuso1/items/778acaa7011d98a3ff3a

 https://en.wikipedia.org/wiki/Basis_(linear_algebra)#Definition
 
 For every finite subset {b_1,..,b_n} of B and every a_1,..,a_n in 𝐅,
 if a_1*b_1 + .. + a_n*b_n = 0, then a_1 = .. = a_n = 0
 
 In this problem, we work on vector space with 32 dimensions with 𝐙/2𝐙 field.
 https://en.wikipedia.org/wiki/GF(2)
 
 Any subset of b_1,..,b_n is represented by co-efficient a_1,..,a_n because of 𝐙/2𝐙 field.
 
 V = a_1*b_1 + .. + a_n*b_n
 
 Let each segment form basis {b_1,..,b_n} of vector space A.
 Because {b_1,.., b_n} is independent, V = 0 <=> a_1 = .. = a_n = 0
 Therefore, any "non-empty" subset of basis does not form 0-vector which is outcome of XOR.
 
 However I still don't understand why XOR of consecutive elements can be equivalent to linear independent basis.
 
 https://codeforces.com/blog/entry/64483?#comment-484135
 ```
  Oh, I agree! Of thought of prefix XORs for so long that I missed the thing the prefix XOR is a linear combination of the numbers in it itself.
 ```
 🤔🤔🤔🤔🤔🤔
 
 Key:
  - XOR of any "non-empty" subset !=0 <=> vectors are basis (linear independent)
 
 */

template<class T> void gf2_GE(vector<T>& V) {
  // gaussian elimination in GF(2)
  int N=V.size();
  for(int i=0; i<N; ++i) {
    sort(V.begin()+i,V.end(),greater<T>());
    if(V[i]==0) break;
    T msb=1;
    while((msb<<1)<=V[i]) msb<<=1;
    for(int j=i+1; j<N; ++j) if(V[j]&msb) V[j]^=V[i];
  }
}
template<class T> int gf2_rank(vector<T>& V) {
  gf2_GE<T>(V);
  return (int)V.size()-count(V.begin(),V.end(),0);
}

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  int x=0;
  REP(i,N) x^=A[i];
  if(x==0) {
    cout<<-1<<endl;
    return;
  }
  
  vector<int> V;
  REP(i,N) V.push_back(A[i]);
  int res=gf2_rank(V);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
