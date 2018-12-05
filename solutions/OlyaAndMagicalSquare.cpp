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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 12/3/2018
 
 12:32-12:50, 14:05-15:00, 15:20-16:03 AC
 
 https://codeforces.com/blog/entry/63436
 
 Summary:
  - tough math problem
  - N is small (<=31). No need to clarify general term of the sequence
 
 */

// $ ../batch OlyaAndMagicalSquare | diff OlyaAndMagicalSquare.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address OlyaAndMagicalSquare.cpp && ./a.out
int T;
LL N,K;

LL P4[32],P2[63];
void solve() {
  P4[0]=P2[0]=1;
  REP(i,31)P4[i+1]=P4[i]*4LL;
  REP(i,62)P2[i+1]=P2[i]*2LL;
  const LL Inf=(LL)4e18;

  FORE(x,1,min(31,(int)N)) {
    dump(x);
    LL ub=P4[x];
    ub=(ub-1)/3;
    if(N-x>=32) ub=Inf;
    else {
      dump4(2*x,x,N,N-x);
      LL a=P2[2*x]-P2[x+1]+1;
      LL b=(P4[N-x]-1)/3;
      ub+=a*b;
    }
    
    LL lb=P2[x+1]-x-2;
    dump4(x,lb,K,ub);
    if(lb<=K&&K<=ub) {
      println("YES %lld", N-x);
      return;
    }
  }
  println("NO");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>T;
  REP(i,T) {
    cin>>N>>K;
    solve();
  }
  
  return 0;
}
