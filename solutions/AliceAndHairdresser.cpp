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
 
 11/11/2018
 
 13:12-13:55 test case #2 doesn't pass. give up
 16:25-16:42 AC after bug fixes (2WA)
 
 https://codeforces.com/blog/entry/63099
 
 Interval determined by indices <=> boolean array
 
 Use map only when coordinate compression is needed
 
 Summary:
  - stupid implementation (two stupid bugs)
  - poor debug
  - DO NOT use unnecessary array which brought a bug
  - Use sentinel if left most or right most boundary needs to be accomodated
 
 */
/*
 
 failed test case:
 
 1 3 1
 1
 0
 1 1 1
 0
 
 --
 
 10 15 10
 12 6 4 7 5 11 15 9 20 10
 0
 1 4 3
 0
 1 4 1
 0
 1 10 2
 0
 1 8 2
 0
 1 3 9
 0
 1 2 10
 0
 1 5 2
 0
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+10;
LL A[MAX_N];
int N,M;
LL L;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int res=0;
  cin>>N>>M>>L;
  REP(i,N) cin>>A[i+1];
  REPE(i,N) if(A[i+1]>L&&A[i]<=L) ++res;
  
  while(M--) {
    int q; cin>>q;
    if(q==0) {
      cout<<res<<endl;
    } else {
      int p; LL d; cin>>p>>d;
      if(A[p]<=L&&A[p]+d>L) {
        if(A[p-1]>L&&A[p+1]>L) --res;
        else if(A[p-1]<=L&&A[p+1]<=L) ++res;
      }
      A[p]+=d;
    }
  }
  
  return 0;
}


int main_orgunko() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>L;
  VI X(N,0);
  REP(i,N) {
    cin>>A[i];
    if(A[i]>L) X[i]=1;
  }
  int G=0;
  dumpAR(X);
  REP(i,N) {
    // two bugs if(i==N-1||(A[i-1]==1&&A[i]==0)) ++G;
    if(X[i]) {
      if(i==N-1||X[i+1]==0) ++G;
    }
  }
  REP(i,M) {
    int q; cin>>q;
    if(q==0) {
      dumpAR(X);
      cout<<G<<endl;
    } else {
      int p; LL d; cin>>p>>d;
      --p;
      A[p]+=d;
      if(X[p]||A[p]<=L) continue;
      X[p]=1;
      if(p>0&&X[p-1]&&p<N-1&&X[p+1]) {
        --G;
        continue;
      }
      if(p>0&&X[p-1]) continue;
      if(p<N-1&&X[p+1]) continue;
      ++G;
      /*
      if(A[p]>L) {
        auto it=X.upper_bound(p);
        if(it==X.end()) {
          X[p]=p;
        } else if(it==X.begin()) {
          if(it->first==p+1) {
            int r=it->second;
            X.erase(it);
            X[p]=r;
          } else {
            X[p]=p;
          }
        } else {
          --it;
          int l=it->first,r=it->second;
          if(l<=)
        }
      }*/
    }
  }
  
  return 0;
}
