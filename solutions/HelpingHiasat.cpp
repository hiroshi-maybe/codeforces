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

// $ cp-batch HelpingHiasat | diff HelpingHiasat.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address HelpingHiasat.cpp && ./a.out

/*
 
 1/21/2019
 
 16:46-17:46 give up
 
 I tried to reproduce constraints by graph.
 My approach was reducing to flow. However no luck.
 I had an idea of "meet in the middle" approach.
 However I coudn't come up with combining it with graph....

 https://codeforces.com/blog/entry/64664
 https://img.atcoder.jp/code-thanks-festival-2017-open/editorial.pdf
 http://noimin.hatenablog.com/entry/2018/10/10/213806
 http://kmjp.hatenablog.jp/entry/2017/12/02/0930
 https://qiita.com/drken/items/7f98315b56c95a6181a4#%E4%B8%80%E8%88%AC%E3%81%AE%E3%82%B0%E3%83%A9%E3%83%95%E3%81%AE%E6%9C%80%E5%A4%A7%E7%8B%AC%E7%AB%8B%E9%9B%86%E5%90%88%E6%9C%80%E5%B0%8F%E7%82%B9%E8%A2%AB%E8%A6%86%E3%82%92%E6%B1%82%E3%82%81%E3%82%8B%E3%82%A2%E3%83%AB%E3%82%B4%E3%83%AA%E3%82%BA%E3%83%A0%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6
 
 18:20 Max clique and independent set... I couldn't make such a graph.
 
 1/22/2019
 
 9:45-11:00, 12:55-17:20, 18:20-19:25, 21:00-22:25 Look back independent set and understand exponential max independent set algorithm. I got AC.
 
 */

int N,M;

int maxIndependentSet(vector<vector<int>> &G) {
  auto ztrans=[&](vector<int> &dp, int N) {
    for(int i=0; i<N; ++i) for(int mask=0; mask<(1<<N); ++mask) {
      if(mask&(1<<i)) dp[mask]&=dp[mask^(1<<i)];
    }
  };
  auto independentset=[&](int l, int r)->vector<int> {
    vector<int> dp(1<<(r-l),1);
    for(int u=l; u<r; ++u) for(auto v : G[u]) if(l<=v&&v<r) {
      dp[(1<<(u-l))|(1<<(v-l))]=false;
    }
    ztrans(dp,r-l);
    for(int mask=0; mask<(1<<(r-l)); ++mask) dp[mask]=dp[mask]?__builtin_popcount(mask):0;
    return dp;
  };
  
  int V=G.size();
  int V1=V/2,V2=V-V1;
  vector<int> fr(1<<V1,(1<<V2)-1);
  vector<int> dp1=independentset(0,V1);
  vector<int> dp2=independentset(V1,V);
  
  for(int u=0; u<V1; ++u) for(auto v : G[u]) if(v>=V1) {
    fr[1<<u]&=((1<<V2)-1)^(1<<(v-V1));
  }
  ztrans(fr,V1);
  
  for(int mask=0; mask<(1<<V2); ++mask) for(int i=0; i<V2; ++i) {
    if((mask&(1<<i))==0) dp2[mask|(1<<i)]=max(dp2[mask|(1<<i)],dp2[mask]);
  }
  int res=0;
  for(int mask=0; mask<(1<<V1); ++mask) {
    res=max(res,dp1[mask]+dp2[fr[mask]]);
  }
  return res;
}

void solve(VV<int> &mx) {
  VV<int> G(M);
  REP(i,M)REP(j,M)if(mx[i][j]) {
    G[i].push_back(j);
  }
  cout<<maxIndependentSet(G)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  VV<int> mx(M,VI(M,0));
  auto f=[&](VI &S) {
    VI vs;
    REP(i,M) if(S[i]) vs.push_back(i);
    REP(i,SZ(vs))REP(j,i) {
      int u=vs[i],v=vs[j];
      mx[u][v]=mx[v][u]=1;
    }
  };
  int p=0;
  VI S(M,0);
  map<string,int> names;
  REP(i,N) {
    int q; cin>>q;
    if(q==1) {
      f(S),S=VI(M,0);
    } else {
      string s; cin>>s;
      int k=0;
      if(!names.count(s)) names[s]=p++;
      k=names[s];
      S[k]=1;
    }
  }
  f(S),S=VI(M,0);
  solve(mx);
  
  return 0;
}
