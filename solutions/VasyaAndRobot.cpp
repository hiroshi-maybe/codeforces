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
 
 10/25/2018 ER53
 
 7:58-9:20 give up
 
 10/31/2018
 
 16:00-18:25 read editorials, submit and got WA
 
 https://codeforces.com/blog/entry/62742
 http://betrue12.hateblo.jp/entry/2018/10/26/200331
 
 I had no idea how to solve this problem.
 
 data: Target position, command sequence
 condition: Target position is reachable by replacing subsegment of commands
 unknown: minimum length of subsegment
 
 This is a problem to find optimal value in terms of some range.
 As usual, I fixed right boundary and tried to find nearest left boundary.
 However I couldn't achieve it.
 
 Suppose we are replacing S[l..r]. Then S[r+1..N-1] should reach target position.
 We know the place that robot should stay at S[r].
 I couldn't figure out formula to find `l` so that S[0..l-1] + S[l..r] (arbitrary) + S[r+1..N-1] reaches target position.
 
 I cannot understand monotonicity of left boundary and right boundary. I proved it by myself.
 
 Suppose left boundary is fixed. Current right boundary is `i`.
 Now L[i]<d[i] where L[i] = length of subsegment, d[i] = sum of delta x and y.
 We want to achieve L[i]>=d[i]. Thus we want to minimize d[i]-L[i].
 
 If we move right boundary to i+1 by one, then..
 
 L[i+1]=L[i]+1
 d[i+1]=d[i]+1 or d[i]-1
 
 a) d[i+1]=d[i]+1
 
 d[i+1] - L[i+1] = d[i]+1 - (L[i]+1) = d[i]-L[i]
 
 Thus the situation is the same.
 
 b) d[i+1]=d[i]-1
 
 d[i+1] - L[i+1] = d[i]-1 - (L[i]+1) = d[i]-L[i] - 2
 
 In this case situation got better.
 
 So by moving right boundary, we never get worse situation. There is monotone property for right boundary.
 Thus binary search works for fixed left boundary.
 
 11/1/2018
 
 10:40-10:53 bug fix and got AC
 
 How to solve it?
  - Look at the unknown! And try to think of a familiar problem having the same or similar unknown
   - how to solve min subsegment?
    - dp
    - binary search
    - two pointers
    - precomputed hashmap
  - Could you restate the problem? Could you restate it still differently?
   - This is necessary to understand the condition in more details. Usutally it is transformation of conditions and data
 
 Summary:
  - Analysis of maximum difference of `d` in boudary move was missing during the contest.
  - I was confused about parity. If it's valid in initial check, no need to recheck later due to parity invariant
  - Binary search was completely out of my mind

 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=2e5+1;
string S;
int N;
LL TX,TY;
map<char,pair < int, int > >  moves = { {'R',{1,0}},{'D',{0,-1}},{'L',{-1,0}},{'U',{0,1}}};
map<char,pair < int, int > >  rmoves = { {'L',{1,0}},{'U',{0,-1}},{'R',{-1,0}},{'D',{0,1}}};

LL solve() {
  if(N<abs(TX)+abs(TY)) return -1;
  if(N%2!=(abs(TX)+abs(TY))%2) return -1;
  
  vector<II> X(N+1);
  X[N]={TX,TY};
  for(int i=N; i>0; --i) {
    int x=X[i].first,y=X[i].second;
    X[i-1]=make_pair(x+rmoves[S[i-1]].first,y+rmoves[S[i-1]].second);
  }
  
  const int Inf=1e8;
  int res=Inf;
  int x=0,y=0;
  REP(i,N) {
    int good=N+1,bad=i-1;
    auto ok=[&](int r) {
      int L=r-i;
      if(r<0||r>N) return false;
      int d=abs(x-X[r].first)+abs(y-X[r].second);
      return d<=L;
    };
    while(abs(good-bad)>1) {
      int r=(good+bad)/2;
//      if(i==37)dump4(r,X[r].first,X[r].second,abs(x-X[r].first)+abs(y-X[r].second));
//      if(i==37)dump4(good,bad,r,ok(r));
      (ok(r)?good:bad)=r;
    }
//    if(i==37)dump2(i,good);
    if(ok(good)) SMIN(res,good-i);
    
    x+=moves[S[i]].first,y+=moves[S[i]].second;
  }
  assert(res!=Inf);
  
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>S>>TX>>TY;
  cout<<solve()<<endl;
  
  return 0;
}
