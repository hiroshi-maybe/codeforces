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
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/25/2018
 
 23:18-24:10 AC
 
 http://codeforces.com/blog/entry/61876
 http://betrue12.hateblo.jp/entry/2018/09/17/015954
 http://kmjp.hatenablog.jp/entry/2018/09/17/0900
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
int cnt[MAX_N];
VI G[MAX_N];
int N;

void end() {
  printf("NO\n");
  exit(0);
}
void solve() {
//  FOR(i,1,N) dump2(i,cnt[i]);
  
  for(int i=N-1; i>0; --i) if(cnt[i]==0) {
    bool ok=false;
    for(int j=N-1; j>i; --j) if(SZ(G[j])<cnt[j]-1) {
      G[j].push_back(i);
      ok=true;
      break;
    }
    if(!ok) end();
  }
  
  vector<II> E;
  FORE(i,1,N-1) if(cnt[i]>0) {
//    dump4(i,SZ(G[i]),cnt[i]-1,SZ(G[i])<cnt[i]-1);
    if(SZ(G[i])<cnt[i]-1) end();
    int u=N;
    REP(j,SZ(G[i])) {
      int v=G[i][j];
//      dump2(u,v);
      E.emplace_back(u,v);
      u=v;
    }
    E.emplace_back(u,i);
//    dump2(u,i);
  }
//  dump(SZ(E));
  if(SZ(E)!=N-1) end();
  printf("YES\n");
  REP(i,SZ(E)) printf("%d %d\n",E[i].first,E[i].second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N-1) {
    int u,v;
    cin>>u>>v;
    if(v!=N) end();
    cnt[u]++;
  }
  solve();
  
  return 0;
}
