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
 
 5/29/2018
 
 25:13-25:46 ACC
 
 Editorials:
  - https://codeforces.com/blog/entry/59758
  - http://par.hateblo.jp/entry/2018/05/30/105153
  - http://yosupo.hatenablog.com/entry/2018/05/30/034234
 
 Tweets:
  - https://togetter.com/li/1232170
  - https://twitter.com/_TTJR_/status/1001520890360676352
  - https://twitter.com/tempura_pp/status/1001527223382233088
  - https://twitter.com/satanic0258/status/1001522786878144512
 
 Summary:
  - BFS idea is straightforward
 
 */
// 25:13-25:46 submit
// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int A[MAX_N];
int N,M,S,K;
VI E[MAX_N];
int D[105][MAX_N];

LL solve(int u) {
  VI X(K);
  REP(k,K) X[k]=D[k][u];
  sort(X.begin(),X.end());
  LL res=0;
  REP(i,S) res+=X[i];
  return res;
}

const int Inf=1e7;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>K>>S;
  REP(i,N) {
    int x;
    cin>>x;
    A[i]=--x;
  }
  REP(i,M) {
    int u,v;
    cin>>u>>v;
    --u,--v;
    E[u].push_back(v);
    E[v].push_back(u);
  }
  
  REP(k,K)REP(u,N) D[k][u]=Inf;
  
  REP(k,K) {
    queue<II> Q;
    REP(u,N) if(A[u]==k) {
      Q.emplace(0,u);
      D[k][u]=0;
    }
    while(SZ(Q)) {
      int d,u; tie(d,u)=Q.front(); Q.pop();
      FORR(v,E[u]) {
        if(D[k][v]>d+1) {
          D[k][v]=d+1;
          Q.emplace(d+1,v);
        }
      }
    }
  }
  
  REP(u,N-1) cout<<solve(u)<<' ';
  cout<<solve(N-1)<<endl;
  
  return 0;
}
