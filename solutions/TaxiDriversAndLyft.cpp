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
 
 11/4/2018 Lyft 5 Final
 
 10:19-10:51 AC
 
 http://codeforces.com/blog/entry/62985
 
 Actually no need to make M buckets to output M values.
 I made things too complicated.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL X[2*MAX_N],L[2*MAX_N],R[2*MAX_N],T[2*MAX_N];
int N,M;

void solve() {
  VI res(M,0);
  int k=0;
  REP(i,N+M) {
    if(T[i]==1) T[i]=k++;
    else T[i]=-1;
  }
//  dumpc(T,T+N+M);
  int l=-1;
  REP(i,N+M) {
    if(T[i]==-1) L[i]=l;
    else l=i;
  }
  int r=-1;
  for(int i=N+M-1; i>=0; --i) {
    if(T[i]==-1) R[i]=r;
    else r=i;
  }
//  dumpc(L,L+N+M);
//  dumpc(R,R+N+M);

  const LL Inf=1e10;
  REP(i,N+M) if(T[i]==-1) {
    int l=L[i],r=R[i];
    LL dl=l<0?Inf:X[i]-X[l];
    LL dr=r<0?Inf:X[r]-X[i];
    int x=dl<=dr?l:r;
//    dump4(i,l,r,x);
//    dump3(i,dl,dr);
    res[T[x]]++;
  }
  REP(i,M) printf("%d ",res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N+M) cin>>X[i];
  REP(i,N+M) cin>>T[i];

  solve();
  
  return 0;
}
