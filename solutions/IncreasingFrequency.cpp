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

// $ ../batch IncreasingFrequency | diff IncreasingFrequency.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address IncreasingFrequency.cpp && ./a.out

/*
 
 12/21/2018
 
 17:56-18:50 give up
 
 12/22/2018
 
 15:30-16:50 read editorials and got AC
 
 https://codeforces.com/blog/entry/63544
 
 Ideas
  - cumulative sum => yes to query appearance of `c`
  - priority queue or sort + map => I digged this. However I couldn't move forward
  - symmetry property => not relevant
  - formula transformation => First key in editorial solution. Anyway idea to reduce to max subsegment sum is necessary
  - segment tree => not relevant
 
 Summary:
  - I couldn't catch any keys
   - Formula transformation to reduce to a problem of single interval
   - Number of appearance can be reduced to subsegment sum
  - Sum of # of segments of all the values is linear in an array. It's worth solving focusing on fixed value.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,C;
LL cum[MAX_N];

//const int Inf=1e7;
int f(VI &X) {
//  dumpAR(X);
  int N=SZ(X);
  int res=0,cur=0;
  REP(i,N) {
    cur=max(X[i],cur+X[i]);
    SMAX(res,cur);
  }
  return res;
}

void solve() {
  cum[0]=0;
  REP(i,N) cum[i+1]=cum[i]+(A[i]==C);
  map<int,pair<VI,int>> M;
  REP(i,N) if(A[i]!=C) {
    int a=A[i],b=cum[i]-cum[M[a].second];
//    dump3(i,a,b);
    M[a].first.push_back(-b);
    M[a].second=i+1;
    M[a].first.push_back(1);
  }
  LL res=cum[N];
  FORR(kvp,M) SMAX(res,cum[N]+f(kvp.second.first));
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>C;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
