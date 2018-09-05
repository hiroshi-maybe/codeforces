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
 
 9/2/2018
 
 8:10-8:23 got 1WA and figured out bug
 8:45 bug fix and got AC
 
 https://codeforces.com/blog/entry/61606
 http://betrue12.hateblo.jp/entry/2018/09/04/012544
 https://twitter.com/my316g/status/1036291911303147520
 https://twitter.com/satanic0258/status/1036292959438757888
 https://twitter.com/_olphe/status/1036292250211237888
 
 */

// 8:23 1WA
// 8:45 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+10;
int N;
SETI E[MAX_N];
int A[MAX_N];
int D[MAX_N];

void dfs(int u, int d, int pre) {
  if(D[u]>=0) return;
  D[u]=d;
  FORR(v,E[u]) dfs(v,d+1,u);
}

bool solve_wrong() {
  MINUS(D);
  dfs(0,0,-1);
//  REP(i,N) dump2(i,D[i]);
  REP(i,N-1) {
    int d1=D[A[i]-1],d2=D[A[i+1]-1];
    if(d1<=d2&&d2-d1<=1) continue;
    return false;
  }
  return true;
}

bool solve() {
  
  if(A[0]!=0) {
//    REP(i,N)dump2(i,A[i]);
    return false;
  }
  queue<int> Q; Q.emplace(0);
  
  int p=1;
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
//    dump4(SZ(Q),u,p,A[p]);
    int M=SZ(E[u]);
    REP(d,M) {
      if(p+d>=N) return false;
      int v=A[p+d];
      if(E[u].count(v)) {
        Q.push(v);
        E[v].erase(u),E[u].erase(v);
      } else {
        return false;
      }
    }
    if(SZ(E[u])) return false;
    p+=M;
  }
  return p==N;
}

const string yes="Yes",no="No";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    E[u].emplace(v),E[v].emplace(u);
  }
  REP(i,N) cin>>A[i],A[i]--;
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
