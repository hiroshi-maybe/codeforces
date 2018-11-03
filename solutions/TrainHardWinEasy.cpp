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
 
 11/2/2018
 
 14:40-15:19 analysis
 15:54 AC
 
 http://kmjp.hatenablog.jp/entry/2018/10/30/0900
 http://codeforces.com/blog/entry/62797
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
LL X[MAX_N],Y[MAX_N],P[MAX_N],cumX[MAX_N],cumY[MAX_N];
int N,M;

void solve() {
  vector<pair<LL,int>> xy(N); REP(i,N) xy[i]={X[i]-Y[i],i};
  sort(ALL(xy));
  REP(i,N) cumX[i+1]=cumX[i]+X[xy[i].second];
  REP(i,N) cumY[i+1]=cumY[i]+Y[xy[N-i-1].second];
  
  vector<LL> res(N);
  REP(i,N) {
    auto p=upper_bound(ALL(xy),make_pair(X[i]-Y[i]-1,N+10))-xy.begin();
    dump2(i,p);
    LL x=cumX[p]+X[i]*(N-p-1);
    dump4(i,cumX[p],N-p-1,X[i]*(N-p-1));
    LL y=cumY[N-p]+Y[i]*(p-1);
    dump4(i,cumY[N-p],p-1,Y[i]*(p-1));
    res[i]=x+y-P[i];
    dump4(i,x,y,P[i]);
  }
  REP(i,N) printf("%lld ",res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  scanf("%d %d",&N,&M);
  REP(i,N) scanf("%lld %lld",&X[i],&Y[i]);
  REP(i,M) {
    int u,v; scanf("%d %d",&u,&v);
    --u,--v;
    LL x=min(X[u]+Y[v],X[v]+Y[u]);
    P[u]+=x,P[v]+=x;
  }
  
  solve();
  
  return 0;
}
