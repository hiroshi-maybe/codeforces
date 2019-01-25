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

// $ cp-batch MakeItConnected | diff MakeItConnected.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MakeItConnected.cpp && ./a.out

/*
 
 1/23/2019
 
 21:23-22:28 WA on test case #5
 
 1/24/2019
 
 8:30-9:56 got AC after fixing two implementation bugs
 
 - wrong update of min vertex weight
 - unnecessary merge of same connected component
 
 https://codeforces.com/blog/entry/64130
 https://betrue12.hateblo.jp/entry/2018/12/28/152148
 
 There are two solutions introdued in the official editorial.
 My original code is following the first one. However second one is much simpler...
 
 Imagine processing Kruskal's algorithm.
 Apparently we cannot keep all the pairs of A[i]+A[j], i!=j.
 However greedily we should use min A + A[i].
 
 */

struct UF {
public:
  int N,G;
  vector<LL> W;
  UF() {}
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1),W=vector<LL>(N,0);
    for(int i=0; i<N; ++i) par[i]=i,rank[i]=0,cnt[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int count(int x) { return cnt[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    G--,cnt[x]=cnt[y]=cnt[x]+cnt[y];
    int p=x,c=y;
    if(rank[p]>rank[c]) swap(p,c);
    else rank[p]+=rank[p]==rank[c];
    par[c]=p;
    W[p]=min(W[x],W[y]);
    return p;
  }
private:
  vector<int> par,rank,cnt;
};

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,M;
tuple<LL,int,int> E[MAX_N];

LL solve() {
  UF uf(N);
  REP(i,N)uf.W[i]=A[i];
  
  vector<pair<LL,int>> vs;
  REP(i,N) vs.emplace_back(A[i],i);
  sort(ALL(vs));
  LL mina=vs[0].first;
  sort(E,E+M);
  
  LL res=0;
  
  REP(i,M) {
    int u,v; LL w; tie(w,u,v)=E[i];
    u=uf.find(u),v=uf.find(v);
    if(u==v) continue;
    if(max(uf.W[u],uf.W[v])+mina>=w) {
      res+=w;
      uf.unite(u,v);
//      dump4(u,v,w,uf.W[uf.find(u)]);
    }
  }
  vector<LL> X;
  REP(u,N) if(uf.find(u)==u) X.emplace_back(uf.W[u]);
  sort(ALL(X));
  
  assert(X[0]==mina);
  FOR(i,1,SZ(X)) res+=X[0]+X[i];
  return res;
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
LL genRandNum(LL lb, LL ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  LL x = rnd() % (LL)(ub - lb);
  return x + lb;
}
vector<LL> genRandSeq(int size, LL lb, LL ub) {
  if (size==0) return {};
  vector<LL> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  const int maxn=100;
  const LL maxa=1e10;
  N=genRandNum(1,maxn);
  M=N==1?0:genRandNum(0,N*(N-1)/2);
  vector<LL> S=genRandSeq(N,1,maxa);
  REP(i,N)A[i]=S[i];
  map<II,LL> es;
  REP(i,M) {
    int u=genRandNum(0,N),v=genRandNum(0,N); LL w=genRandNum(1,maxa);
    if(u>v) swap(u,v);
    if(u!=v) {
      es[{u,v}]=w;
    }
  }
  M=SZ(es);
  dump2(N,M);
  int i=0;
  FORR(kvp,es) E[i++]={kvp.second,kvp.first.first,kvp.first.second};
  
  dump2(N,M);
  dumpAR(S);
  FORR(kvp,es) dump3(kvp.first.first,kvp.first.second,kvp.second);
  
  LL act=solve();
  
  LL mx[maxn][maxn];
  REP(i,N)REP(j,N) mx[i][j]=i==j?1e15:A[i]+A[j];
  REP(i,M) {
    int u,v; LL w; tie(w,u,v)=E[i];
    SMIN(mx[u][v],w),SMIN(mx[v][u],w);
  }
  vector<tuple<LL,int,int>> eses;
  REP(i,N)REP(j,N)if(i<j) eses.emplace_back(mx[i][j],i,j);
  sort(ALL(eses));
  LL exp=0;
  UF uf(N);
  i=0;
  while(uf.G>1) {
    int u,v; LL w; tie(w,u,v)=eses[i++];
    if(uf.find(u)!=uf.find(v)) {
      uf.unite(u,v),exp+=w;
    }
  }
  if(act!=exp) {
    dumpAR(S);
    FORR(kvp,es) dump3(kvp.first.first,kvp.first.second,kvp.second);
    dump2(act,exp);
  }
  assert(act==exp);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  REP(j,M) {
    int u,v; LL w; cin>>u>>v>>w;
    --u,--v;
    E[j]={w,u,v};
  }
  cout<<solve()<<endl;
  
  return 0;
}
