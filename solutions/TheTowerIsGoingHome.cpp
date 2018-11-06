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
 
 10:52-11:39 system test failed
 
 11/5/2018
 
 16:30-17:47 read editorial and got AC
 
 http://codeforces.com/blog/entry/62985
 
 It turns out that my analysis was COMPLETELY wrong.
 It's also possible to detour some horizontal walls by removing horizontal walls.
 
 Data: Horizontal and vertical walls
 Condition: Horizontal wall blocks X1[i]<=x<=X2[i] and y=Y[i], vertical wall blocks x=X[i]
 Unknown: Minimum # of walls to be removed to reach from (1,1) to (*,1e9)
 
 This is similar to graph problem with weight 1 edge. However shortest path algorithm does not work due to large N and M.
 BFS is not applicable. However it helps the observation that detour can happen.
 
 Several observations are needed to solve
  - (*,1e9) is reachable from one of N+1 columns
  - If column `i`<=N is reachable, `i` vertical walls should have been removed
  - If column `i`<=N is reachable, horizontal walls ranging [1,X[i]] are blockers.
 
 The first observation is the most important to come up with an idea to iterate N columns.
 
 Summary:
  - Confirm that your method is optimal. Prove that your method is optimal.
  - "At least `N` exclusive and exhaustive possibilities" is important. We can dig deeper to figure out what should be known to achieve each of them. It's exactly auxiliary problem
   - How to solve it?
    - You may be obliged to consider auxiliary problems if an immediate connection cannot be found
    - Could you solve a part of the problem? Keep only a part of the condition, drop the other part
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+2;
LL X[MAX_N], A[MAX_N];
int N,M;

void solve() {
  sort(X,X+N+1);
  sort(A,A+M);
  int res=1e6;
  REP(i,N+1) {
    int cnt=(A+M)-lower_bound(A,A+M,X[i]);
    SMIN(res,cnt+i);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int MM;
  cin>>N>>MM;
  REP(i,N) cin>>X[i];
  X[N]=1e9;
  //  dumpc(X,X+N+2);
  REP(i,MM) {
    LL x1,x2,y; cin>>x1>>x2>>y;
    if(x1!=1) continue;
    A[M++]=x2;
  }
  
  solve();
  
  return 0;
}


map<LL,int> imos;
void solve_wrong() {
  LL res=1e6;
  LL cur=0;
  REP(i,N+1) {
    if(imos.count(i)) cur+=imos[i];
//    dump2(i,cur);
    SMIN(res,cur+i);
  }
  cout<<res<<endl;
}

int main_wrong() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  X[0]=0;
  REP(i,N) cin>>X[i+1];
  X[N+1]=1e9;
  sort(X,X+N+2);
//  dumpc(X,X+N+2);
  REP(i,M) {
    LL x1,x2,y; cin>>x1>>x2>>y;
    --x1;
//    dump3(i,x1,x2);
    int l=lower_bound(X,X+N+2,x1)-X;
    if(X[l]!=x1) ++l;
    int r=lower_bound(X,X+N+2,x2)-X;
//    dump2(i,r);
    if(X[r]!=x2) --r;
//    dump3(i,l,r);
    if(l<r) imos[l]++,imos[r]--;
  }
  
  solve();
  
  return 0;
}
