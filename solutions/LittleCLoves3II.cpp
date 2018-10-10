#include <iostream>
#include <iomanip>
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
 
 9/21/2018
 
 8:30-9:00 give up
 
 9/28/2018
 
 15:00-17:00 read editorials
 
 https://codeforces.com/blog/entry/61993
 http://drken1215.hatenablog.com/entry/2018/09/23/160700
 http://kmjp.hatenablog.jp/entry/2018/10/08/0930
 https://twitter.com/tempura_pp/status/1043178034356924417
 https://twitter.com/satanic0258/status/1043178682192293889
 https://twitter.com/hamko_intel/status/1043179697541013504
 
 Knight's tour: http://gaebler.us/share/Knight_tour.html
 
 10/3/2018
 
 14:00-14:05 got AC after experiment
 
 Summary:
  - Proof of knight's tour is showing hints
   - Look at corners which has limited options. Narrow down possible patterns from them.
   - Avoid decomposing to NG blocks.
   - Find simple coustructions and glue them to extend to general cases
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
LL f1(LL N) {
  if(N%6==0) return N;
  if(N%6==1) return N-1;
  if(N%6==2||N%6==4) return N-2;
  if(N%6==3) return N-3;
  return N-1;
}
LL f2(LL N) {
  if(N%4==0) return 2LL*N;
  if(N%4==1||N%4==2) return 2LL*(N-N%4);
  return 2LL*(N-1);
}
LL f3(LL N) {
  if(N%4==0||N%4==2) return 3LL*N-2;
  if(N%4==1) return 3LL*N-3;
  return 3LL*N-1;
}
LL solve_wrong(LL N, LL M) {
  if(N%6==0||M%6==0) return N*M;
  if(N%6==5) return N*(M-1)+f1(M);
  if(N%6==2||N%6==4) return N*(M-2)+f2(M);
  return N*(M-3)+f3(M);
}

const int MAX_V=300;
class MaxBipartiteMatching {
public:
  MaxBipartiteMatching(int V) : V(V) {}
  
  void addEdge(int u, int v) {
    assert(u<V&&v<V);
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  int solve() {
    int res=0;
    memset(match, -1, sizeof(match));
    for(int u=0; u<V; ++u) if(match[u]<0) {
      memset(viz,0,sizeof viz);
      res+=dfs(u);
    }
    
    return res;
  }
private:
  int V;
  vector<int> E[MAX_V];
  int match[MAX_V];
  bool viz[MAX_V];
  
  // find augmenting path in residual network
  bool dfs(int u) {
    viz[u]=true;
    for(auto v : E[u]) {
      int w=match[v];
      if(w<0||(!viz[w]&&dfs(w))) {
        match[v]=u;
        match[u]=v;
        return true;
      }
    }
    return false;
  }
};

LL solve(LL N, LL M) {
  if(N>M) swap(N,M);
  int res1[6]={0,1,2,3,2,1};
  if(N==1) return N*M-res1[M%6];
  if(N==2) {
    if(M==2) return 0;
    if(M==3) return 4;
    if(M==7) return 12;
    return N*M;
  }
  if(N%2==1&&M%2==1) return N*M-1;
  return N*M;
}

/*
 m = 1, n = 1, n*m-2*x = 1
 m = 1, n = 2, n*m-2*x = 2
 m = 1, n = 3, n*m-2*x = 3
 m = 1, n = 4, n*m-2*x = 2
 m = 1, n = 5, n*m-2*x = 1
 m = 1, n = 6, n*m-2*x = 0
 m = 1, n = 7, n*m-2*x = 1
 m = 1, n = 8, n*m-2*x = 2
 m = 1, n = 9, n*m-2*x = 3
 m = 1, n = 10, n*m-2*x = 2
 m = 1, n = 11, n*m-2*x = 1
 m = 1, n = 12, n*m-2*x = 0
 m = 1, n = 13, n*m-2*x = 1
 m = 1, n = 14, n*m-2*x = 2
 m = 1, n = 15, n*m-2*x = 3
 m = 1, n = 16, n*m-2*x = 2
 m = 1, n = 17, n*m-2*x = 1
 m = 1, n = 18, n*m-2*x = 0
 m = 1, n = 19, n*m-2*x = 1
 m = 1, n = 20, n*m-2*x = 2

 m = 2, n = 1, n*m-2*x = 2
 m = 2, n = 2, n*m-2*x = 4
 m = 2, n = 3, n*m-2*x = 2
 m = 2, n = 4, n*m-2*x = 0
 m = 2, n = 5, n*m-2*x = 0
 m = 2, n = 6, n*m-2*x = 0
 m = 2, n = 7, n*m-2*x = 2
 m = 2, n = 8, n*m-2*x = 0
 m = 2, n = 9, n*m-2*x = 0
 m = 2, n = 10, n*m-2*x = 0
 m = 2, n = 11, n*m-2*x = 0
 m = 2, n = 12, n*m-2*x = 0
 m = 2, n = 13, n*m-2*x = 0
 m = 2, n = 14, n*m-2*x = 0
 m = 2, n = 15, n*m-2*x = 0
 m = 2, n = 16, n*m-2*x = 0
 m = 2, n = 17, n*m-2*x = 0
 m = 2, n = 18, n*m-2*x = 0
 m = 2, n = 19, n*m-2*x = 0
 m = 2, n = 20, n*m-2*x = 0
 
 m = 1, n = 2, n*m-2*x = 2
 m = 1, n = 3, n*m-2*x = 3
 m = 1, n = 4, n*m-2*x = 2
 m = 1, n = 5, n*m-2*x = 1
 m = 1, n = 6, n*m-2*x = 0
 m = 1, n = 7, n*m-2*x = 1
 m = 1, n = 8, n*m-2*x = 2
 m = 1, n = 9, n*m-2*x = 3
 m = 1, n = 10, n*m-2*x = 2
 m = 2, n = 3, n*m-2*x = 2
 m = 2, n = 4, n*m-2*x = 0
 m = 2, n = 5, n*m-2*x = 0
 m = 2, n = 6, n*m-2*x = 0
 m = 2, n = 7, n*m-2*x = 2
 m = 2, n = 8, n*m-2*x = 0
 m = 2, n = 9, n*m-2*x = 0
 m = 2, n = 10, n*m-2*x = 0
 m = 3, n = 4, n*m-2*x = 0
 m = 3, n = 5, n*m-2*x = 1
 m = 3, n = 6, n*m-2*x = 0
 m = 3, n = 7, n*m-2*x = 1
 m = 3, n = 8, n*m-2*x = 0
 m = 3, n = 9, n*m-2*x = 1
 m = 3, n = 10, n*m-2*x = 0
 m = 4, n = 5, n*m-2*x = 0
 m = 4, n = 6, n*m-2*x = 0
 m = 4, n = 7, n*m-2*x = 0
 m = 4, n = 8, n*m-2*x = 0
 m = 4, n = 9, n*m-2*x = 0
 m = 4, n = 10, n*m-2*x = 0
 m = 5, n = 6, n*m-2*x = 0
 m = 5, n = 7, n*m-2*x = 1
 m = 5, n = 8, n*m-2*x = 0
 m = 5, n = 9, n*m-2*x = 1
 m = 5, n = 10, n*m-2*x = 0
 m = 6, n = 7, n*m-2*x = 0
 m = 6, n = 8, n*m-2*x = 0
 m = 6, n = 9, n*m-2*x = 0
 m = 6, n = 10, n*m-2*x = 0
 m = 7, n = 8, n*m-2*x = 0
 m = 7, n = 9, n*m-2*x = 1
 m = 7, n = 10, n*m-2*x = 0
 m = 8, n = 9, n*m-2*x = 0
 m = 8, n = 10, n*m-2*x = 0
 m = 9, n = 10, n*m-2*x = 0
 */

void experiment() {
  FORE(m,2,2)FORE(n,1,100) {
    MaxBipartiteMatching ma(n*m);
    REP(i,n)REP(j,m) FORE(d1,-3,3)FORE(d2,-3,3) {
      int ii=i+d1,jj=j+d2;
      if(ii<0||ii>=n||jj<0||jj>=m) continue;
      if(abs(i-ii)+abs(j-jj)!=3) continue;
      int u=i*m+j,v=ii*m+jj;
      if(u<v) ma.addEdge(u,v);
    }
    int x=ma.solve();
    dump3(m,n,n*m-2*x);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  experiment();
  
  LL N,M;
  cin>>N>>M;
  cout<<max(solve(N,M),solve(M,N))<<endl;
  return 0;
}
