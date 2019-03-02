#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch AsyaAndKittens | diff AsyaAndKittens.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AsyaAndKittens.cpp && ./a.out

/*
 
 2/23/2019
 
 3:39-4:20 give up
 
 3/2/2019
 
 11:00-12:06 TLE
 12:10 got AC after restoring path compression in UF library.
 
 https://codeforces.com/blog/entry/65487
 https://naoyat.hatenablog.jp/entry/CodeforcesRound541Div2
 
 */

struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1);
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
    return p;
  }
private:
  vector<int> par,rank,cnt;
};

vector<int> tsort(vector<vector<int>> &G) {
  int N=G.size();
  dump(N);
  vector<int> D(N,0);
  for(int u=0; u<N; ++u) for(auto v : G[u]) D[v]++;
  vector<int> res;
  deque<int> Q;
  
  for(int u=0; u<N; ++u) if(D[u]==0) Q.push_back(u);
  while(Q.size()) {
    int u=Q.front(); Q.pop_front();
    res.push_back(u);
    dump(u);
    for(auto v : G[u]) {
      dump(u,v);
      assert(v<SZ(D));
      D[v]--;
      if(D[v]==0) Q.push_front(v);
    }
  }
  return res;
}

const int MAX_N=2e5+1;
int N;

/*
void solve_wrong() {
  UF uf(N);
  REP(i,N) {
    int u,v; cin>>u>>v;
    --u,--v;
    uf.unite(u,v);
  }
  VV<int> G(N);
  REP(i,N) {
    if(uf.par[i]!=i) G[i].push_back(uf.par[i]);
  }
  VI res=tsort(G);
  REP(i,N) {
    printf("%d ", res[i]+1);
  }
  println("");
}*/

VI G[MAX_N];

VI res;
void dfs(int u) {
  res.push_back(u);
  FORR(v,G[u]) dfs(v);
}

// union-find tree and tree traversal
void solve_org() {
  UF uf(N);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    int pu=uf.find(u),pv=uf.find(v);
    int p=uf.unite(u,v);
    if(p==pu) G[p].push_back(pv);
    else G[p].push_back(pu);
  }
  dfs(uf.find(0));
  assert(SZ(res)==N);
  REP(i,N) printf("%d ", res[i]+1);
  println("");
}

// union-find tree and list splice
list<int> ls[MAX_N];
void solve_uf_list() {
  UF uf(N);
  REP(i,N) ls[i].emplace_back(i);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    int pu=uf.find(u),pv=uf.find(v);
    int p=uf.unite(u,v);
    if(p==pu) ls[p].splice(ls[p].end(),ls[pv]);
    else ls[p].splice(ls[p].end(),ls[pu]);
  }
  list<int> res=ls[uf.find(0)];
  assert(SZ(res)==N);
  REP(i,N) printf("%d ", res.front()+1),res.pop_front();
  println("");
}

// typical technique of merging sets
void solve() {
  VV<int> S(N);
  VI ids(N);
  REP(i,N) ids[i]=i,S[i].push_back(i);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    int p1=ids[u],p2=ids[v];
    if(SZ(S[p1])>SZ(S[p2])) swap(p1,p2);
    // merge p1 to p2
    FORR(u,S[p1]) {
      ids[u]=p2;
      S[p2].push_back(u);
    }
    S[p1].clear();
  }
  VI res=S[ids[0]];
  assert(SZ(res)==N);
  REP(i,N) printf("%d ", res[i]+1);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
