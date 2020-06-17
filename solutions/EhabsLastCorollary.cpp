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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif
struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int size(int x) { return sz[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    int p=x,c=y;
    if(sz[p]<sz[c]) swap(p,c);
    G--,sz[p]=sz[c]=sz[p]+sz[c];
    par[c]=p;
    return p;
  }
private:
  vector<int> par,sz;
};

struct LCA {
public:
  vector<vector<int>> G;
  int V,root;
  int H,t=0;
  vector<vector<int>> P; // parent P[bits][vertices], bits=floor(lg N)+1
  vector<int> D; // depth for LCA query D[vertices]
  vector<int> L,R; // timestamp of Euler tree
  LCA() {}
  LCA(int root, int V) : V(V), root(root) {
    G=vector<vector<int>>(V);
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  LCA(int root, vector<vector<int>> &G) : G(G), root(root) {
    V=G.size();
  }
  void build() {
    D=vector<int>(V,0),L=vector<int>(V,0),R=vector<int>(V,0);
    H=1;
    while((1<<H)<=V) ++H;
    P=vector<vector<int>>(H,vector<int>(V,-1));
    dfs(root,-1,0);
    for(int i=0; i<H-1; ++i) {
      for(int j=0; j<V; ++j) {
        if(P[i][j]!=-1) P[i+1][j]=P[i][P[i][j]];
      }
    }
  }
  // query to find an ancestor with `d` distance
  int ancestor(int u, int d) {
    int cur=u;
    for(int i=H-1; i>=0; --i) if(cur>=0&&(d>>i)&1) cur=P[i][cur];
    return cur;
  }
  int query(int u, int v) { // query to find lca(u,v)
    assert(0<=u&&u<V&&0<=v&&v<V);
    assert(!P.empty()); // call lca.build();
    if(D[u]>D[v]) swap(u,v);
    v=ancestor(v,D[v]-D[u]);
    if(u==v) return u;
    for(int i=H-1; i>=0; --i) {
      if(P[i][u]!=P[i][v]) u=P[i][u],v=P[i][v];
    }
    return P[0][u];
  }
  int dist(int u, int v) { // distance between u and v
    assert(0<=u&&u<V&&0<=v&&v<V);
    int p=query(u,v);
    dump(u,v,D[u],D[v],D[p]);
    return D[u]+D[v]-2*D[p];
  }
  vector<int> path(int u, int v) {
    dump(u,v);
    int p=query(u,v);
    VI a,b;
    while(u!=p) a.push_back(u),u=P[0][u];
    while(v!=p) b.push_back(v),v=P[0][v];
    VI res=a;
    res.push_back(p);
    reverse(b.begin(),b.end());
    for(auto u : b) res.push_back(u);
    return res;
  }
private:
  void dfs(int u, int par, int d) {
    dump(par,u,d);
    P[0][u]=par;
    D[u]=d,L[u]=t++;
    for(int v : G[u]) if(v!=par) dfs(v,u,d+1);
    R[u]=t++;
  }
};
// $ cp-batch EhabsLastCorollary | diff EhabsLastCorollary.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabsLastCorollary.cpp && ./a.out

/*

 6/13/2020

 8:55-10:02 system test failed
 10:35 AC after bug fix

 https://codeforces.com/blog/entry/78781
 https://twitter.com/hanseilimak/status/1272569488005672960

 https://twitter.com/kyort0n/status/1271852048238010368
 https://twitter.com/armeria_betrue/status/1271852367265148929
 https://twitter.com/n_vip/status/1271853131681239040

 6/16/2020

 Got AC by LCA solution

 */

const int MAX_N=1e6+1;
int N,M,K;

VI res1[2];
VI G[MAX_N];
int viz[MAX_N];

void dfs(int u, VI &cur) {
  if(viz[u]!=-1) {
    int len=SZ(cur)-viz[u];
    if(3<=len&&len<=K) {
      cout<<2<<endl;
      cout<<SZ(cur)-viz[u]<<endl;
      FOR(i,viz[u],SZ(cur)) cout<<cur[i]+1<<" ";
      cout<<endl;
      exit(0);
    }
    return;
  }
  viz[u]=SZ(cur);
  cur.push_back(u);
  FORR(v,G[u]) dfs(v,cur);
  cur.pop_back();
}

void dfs1(int u, int col) {
  if(viz[u]) return;
  res1[col].push_back(u);
  viz[u]=1;
  FORR(v,G[u]) {
    dfs1(v,col^1);
  }
}
void solve() {
  VI cur;
  MINUS(viz);
  dfs(0,cur);

  ZERO(viz);
  dfs1(0,0);

  //dumpc(res1);
  VI ans=res1[0];
  if(SZ(res1[1])>SZ(ans)) ans=res1[1];
  assert(SZ(ans)>=(K+1)/2);
  cout<<1<<endl;
  REP(i,(K+1)/2) cout<<ans[i]+1<<" ";
  cout<<endl;
}

int main_org() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>K;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }

  solve();

  return 0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>K;
  LCA lca(0,N);
  UF uf(N);
  vector<II> es(M);
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    es[i]={u,v};
    if(!uf.sameset(u,v)) {
      lca.addEdge(u,v);
      uf.unite(u,v);
    }
  }
  lca.build();
  int minc=1e6,u0=-1,u1=-1;
  for(auto p : es) {
    int u,v; tie(u,v)=p;
    int d=lca.dist(u,v);
    dump(u,v,d);
    if(2<=d&&d<minc) minc=d,u0=u,u1=v;
  }

  dump(minc,u0,u1);
  VI res;
  if(u0==-1) {
    VV<int> vs(2);
    REP(i,N) vs[lca.D[i]%2].push_back(i);
    res=SZ(vs[0])>SZ(vs[1])?vs[0]:vs[1];
  } else {
    VI ps=lca.path(u0,u1);
    if(minc>=K) {
      for(int i=0; i<K; i+=2) res.push_back(ps[i]);
    } else res=ps;
  }

  dumpc(res);
  if(minc<K) {
    cout<<2<<endl;
    cout<<SZ(res)<<endl;
    REP(i,SZ(res)) cout<<res[i]+1<<" ";
    cout<<endl;
  } else {
    cout<<1<<endl;
    REP(i,(K+1)/2) cout<<res[i]+1<<" ";
    cout<<endl;
  }

  return 0;
}
