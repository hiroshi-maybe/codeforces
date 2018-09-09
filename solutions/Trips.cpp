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
 
 8:46-9:35 give up
 
 9/8/2018
 
 24:00-25:30 read editorials and add solution
 
 https://codeforces.com/blog/entry/61606
 http://betrue12.hateblo.jp/entry/2018/09/04/012544
 https://twitter.com/a3VtYQo/status/1036292404725207040
 
 It's interesting that by removing vertices with degrees less than K, we eventually get cycles with at least K-degree. That's why it's preferred to process queries backwards.
 
 Key:
  - Process edges backward to keep invariant that all the vertices in current graph has at least K-degree
  - Remove unnecessary edges and propagete the changes. Then only cycle remains by itself
 
 Summary:
  - Interesting problem. This is the first time to process queries in reverse order
  - Similar to topological sort. Keep removing edges until we obtain wished properties
 
 */

const int MAX_N=2e5+10;
int N,M,K;
SETI S;
SETI D[MAX_N];
int rem[MAX_N];
vector<II> es;

void clean(set<int> &Q) {
  while(SZ(Q)) {
    int u=*(Q.begin()); Q.erase(u);
    FORR(eid,D[u]) {
      int x,y; tie(x,y)=es[eid];
      int v=x==u?y:x;
      rem[eid]=true;
      D[v].erase(eid);
      if(SZ(D[v])<K) Q.emplace(v);
    }
    D[u].clear();
    S.erase(u);
  }
}

void solve() {
  ZERO(rem);
  es.clear(),S.clear();
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    es.emplace_back(u,v);
    D[u].emplace(i),D[v].emplace(i);
  }
  set<int> Q;
  REP(u,N) {
    if(SZ(D[u])<K) Q.emplace(u);
    else S.emplace(u);
  }
  clean(Q);
  vector<int> res(M);
  for(int i=M-1; i>=0; --i) {
    res[i]=SZ(S);
    if(!rem[i]) {
      set<int> Q;
      int u,v; tie(u,v)=es[i];
      rem[i]=true;
      D[u].erase(i),D[v].erase(i);
      if(SZ(D[v])<K) Q.emplace(v);
      if(SZ(D[u])<K) Q.emplace(u);
      clean(Q);
    }
  }
  REP(i,M) cout<<res[i]<<endl;
}

/*
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
struct BIT {
public:
  int N;
  vector<int> T; // T[1..N] has values (1-based index)
  BIT(int N): N(N) {
    T.resize(N+1,0);
  }
  
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) {
      res+=T[r];
      r-=lsone(r);
    }
    return res;
  }
  
  // query ∑ { sum[i] : i=l..r }
  int query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<=N);
    ++i; // 0-based index to 1-based index
    while(i<=N) {
      T[i]+=x;
      i+=lsone(i);
    }
  }
  
  // sum[i]=x
  void update(int i, int x) {
    int v1=query(i)-query(i-1);
    add(i,x-v1);
  }
  
  // compute total inversions
  int inversions(vector<int> ns) {
    int N=ns.size(),res=0;
    for(int i=N-1; i>=0; --i) {
      // Count elements which stays in right side and smaller
      res+=query(ns[i]-1);
      add(ns[i],1);
    }
    return res;
  }
private:
  int lsone(int i) { return i&-i; }
};

struct UF {
public:
  int groupNum;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }
  
  int find(int i) {
    return uf[i]==i?i:uf[i]=find(uf[i]);
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return;
    groupNum--;
    
    if (rank[x]==rank[y]) {
      uf[x]=y;
      rank[y]++;
      return;
    }
    
    if (rank[x]<rank[y]) {
      uf[x]=y;
    } else {
      uf[y] =x;
      if(rank[x]==rank[y]) ++rank[x];
    }
  }
private:
  vector<int> rank;
  vector<int> uf;
};

int sumE[MAX_N];

void solve_wrong() {
  ZERO(D);
  BIT bit(N);
  UF uf(N);
  
  auto updateD = [&](int u, int delta) {
    if(D[u]>0) bit.add(D[u],delta);
  };
  
  REP(_,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    updateD(u,-1);
    D[u]++;
    updateD(u,+1);
    
    updateD(v,-1);
    D[v]++;
    updateD(v,+1);

    dump4(u,v,D[u],D[v]);
    
    uf.unite(u,v);
    
    int x=bit.query(K,N-1);
    if(x<K+1) x=0;
    cout<<x<<endl;
  }
}
*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>K;
  solve();
  return 0;
}
