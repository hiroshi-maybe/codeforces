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

// $ ../batch Cookies | diff Cookies.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Cookies.cpp && ./a.out

/*
 
 1/14/2019
 
 11:00-12:30 give up
 14:12 read editorial and got AC
 
 https://codeforces.com/blog/entry/64331
 
 Same as my approach. However I couldn't figure out how segment tree or BIT works 😞
 Ok. Got it. Cumulative sum is exactly what BIT is internally keeping.
 I didn't have binary search idea against BIT.
 
 */

struct BIT {
public:
  int N;
  vector<LL> T;
  BIT(int N): N(N) {
    T=vector<LL>(N+1,0);
  }
  
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  LL query(int r) {
    ++r; // 0-based index to 1-based index
    LL res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  LL query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, LL x) {
    assert(0<=i&&i<N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // sum[i]=x
  void update(int i, int x) {
    LL v1=query(i)-query(i-1);
    add(i,x-v1);
  }
  
  // compute total inversions
  LL inversions(vector<int> ns) {
    int N=ns.size(); LL res=0;
    for(int i=N-1; i>=0; --i) {
      // Count elements which stays in right side and smaller
      res+=query(ns[i]-1);
      add(ns[i],1LL);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

const int MAX_N=1e5+10;
LL X[MAX_N], T[MAX_N];
LL TLIM;
int N;
vector<pair<int,LL>> G[MAX_N];

const int MAX_T=1e6+10;
BIT timet(MAX_T),cnt(MAX_T);

LL maxcnt(LL trem) {
  int good=MAX_T-5,bad=0;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    (timet.query(m)>trem?good:bad)=m;
  }
  
  dump(good);
  LL res=cnt.query(good-1);
  LL t=trem-timet.query(good-1);
  assert(good!=0);
  res+=min(t/good,cnt.query(good,good));
  return res;
}

LL scores[MAX_N];
void dfs(int u, LL lsum) {
  LL trem=TLIM-2LL*lsum;
  int t=T[u];
  timet.add(t,X[u]*t);
  cnt.add(t,X[u]);
  
  LL mine=maxcnt(trem);
  
  dump4(u,X[u]*t,trem,mine);
  
  scores[u]=mine;
  
  FORR(p,G[u]) {
    int v; LL l; tie(v,l)=p;
    dfs(v,lsum+l);
  }
  
  timet.add(t,-X[u]*t);
  cnt.add(t,-X[u]);
}

LL f(int u) {
  LL mine=scores[u];
  if(SZ(G[u])==0) return mine;
  
  LL m1=0,m2=0;
  FORR(p,G[u]) {
    int v; LL l; tie(v,l)=p;
    LL a=f(v);
    if(a>m2) m2=a;
    if(m2>m1) swap(m1,m2);
  }
  if(u==0) return max(mine,m1);
  return max(mine,m2);
}

void solve() {
  dfs(0,0);
  cout<<f(0)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>TLIM;
  REP(i,N) cin>>X[i];
  REP(i,N) cin>>T[i];
  REP(i,N-1) {
    int p; LL l; cin>>p>>l;
    --p;
    G[p].emplace_back(i+1,l);
  }
  solve();
  
  return 0;
}
