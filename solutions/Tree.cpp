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

// $ cp-batch Tree | diff Tree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Tree.cpp && ./a.out

/*
 
 2/7/2019
 
 10:42-11:30 give up
 
 Following basics to drop condition, I tried to solve a problem with fixed root.
 
 Possible approaches:
  - IEP
  - tree dp
 
 #1 IEP
 
 By dfs, we know that some of nodes cannot be in the same group if they are in the same path.
 One way is to subtract ways to put them in the same group (IEP approach).
 However counting union seems to exeed time limit (exponential)
 
 #2 tree dp
 
 One idea of dp state is dp[i][g] where i: # of processed node <=K, g: # of groups <=M
 
 SP1: Sort A by depth from root. dfs from roots of the forest.
 dp[i][g]+=dp[i-1][g-1]
 dp[i][g]+=(g-|{j:j and i are in the same path}|)*dp[i-1][g]
 
 It seems to be possible to precompute {j:j and i are in the same path} for all `j` (SP2).
 However this is still O(K*M) per root. I'm in stuck 😞
 
 2/8/2019
 
 10:55-12:50, 13:50-17:00, 18:00-19:00, 21:50-23:30 read editorials and implement.
 
 2/9/2019
 
 10:15-12:15 AC
 
 https://codeforces.com/blog/entry/64989
 http://kmjp.hatenablog.jp/entry/2019/02/07/0930
 
 Analysis of #2 tree dp above is correct. We need to resolve three problems.
 SP0: Resolve runtime of O(K*M) dp
 SP1: how to sort A by depth from different root in O(K) or O(K*lg K)
 SP2: how to compute {j:j and i are in the same path} for all `j` in O(K) or O(K*lg K)
 
 # SP0
 
 Actually it fits in TL M*∑K≈3x10^7
 
 # SP1 and SP2
 
 SP1 and SP2 are resolved at once by building subset tree by nodes in `A`.
 # of nodes in the new tree rooted by `root` can be computed by below root distance technique.

 dist(u,v) = dist(u,0) + dist(v,0) - 2*dist(LCA(u,v),0) where `0` is root of the original tree
 => dist(u,root) = dist(u,0) + dist(root,0) - 2*dist(LCA(u,root),0)

 For each query, `A` forms a tree with subset nodes.
 If we see distance as # of nodes of original nodes, we can notice that our wanting value is
 
 Instead of distance (# of nodes of all universal nodes), we want to know # of subset nodes in the path to new `root` in O(K) or O(K*lg K) time (O(N) is expensive).
 It's feasible by Euler tour tree + BIT.

 We are replacing dist(u,root) with h(u,root) which represents # of nodes in the subset tree T'(0).
 Formula is almost same as distance version.
 
 h(u,root) = h(u,0) + h(root,0) - 2*h(dist(LCA(u,root),0)
 
 We compute h(i,root), i=A[0]..A[K-1]. Sort them and do DP in depth-wise order.
 
 Reference: Eulerian tour technique https://en.wikipedia.org/wiki/Euler_tour_technique

 */

const int MOD=1e9+7;
struct ModInt {
  unsigned int val;
  ModInt(): val(0) {}
  ModInt(int v) { norm(v%MOD); }
  ModInt(long long v) { norm(v%MOD); }
  ModInt& norm(long long v) {
    v=v<0?v%MOD+MOD:v; // negative
    v=v>=MOD?v-MOD:v; // mod
    val=(unsigned int)v;
    return *this;
  }
  explicit operator bool() const { return val!=0; }
  ModInt operator-() const { return ModInt(0)-*this; }
  ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
  ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
  ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
  ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
  ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
  ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
  ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
  ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
  ModInt pow(long long n) const {
    ModInt x=*this, res=1;
    while(n>0) {
      if(n&1) res*=x;
      x*=x,n>>=1;
    }
    return res;
  }
  ModInt inv() const { return (*this).pow(MOD-2); }
  bool operator==(ModInt that) const { return val==that.val; }
  bool operator!=(ModInt that) const { return val!=that.val; }
  friend ostream& operator<<(ostream& os, const ModInt& that) { return os<<that.val; }
};

const int MAX_N=1e6+1;
LL A[MAX_N];
VV<int> G;
int N,Q,K,M,root;
int mark[MAX_N];
ModInt dp[2][310];

struct BinaryLifting {
public:
  vector<vector<int>> G;
  int V,root;
  int H,t=0;
  vector<vector<int>> P; // parent P[bits][vertices], bits=floor(lg N)+1
  vector<int> D; // depth for LCA query D[vertices]
  vector<int> L,R; // timestamp of Euler tree
  BinaryLifting() {}
  BinaryLifting(int root, int V) : V(V), root(root) {
    G=vector<vector<int>>(V);
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  BinaryLifting(int root, vector<vector<int>> &G) : G(G), root(root) {
    V=G.size();
  }
  void buildLiftingTable() {
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
  // query to find lca(u,v)
  int lca(int u, int v) {
    assert(u<V&&v<V);
    if(D[u]>D[v]) swap(u,v);
    v=ancestor(v,D[v]-D[u]);
    if(u==v) return u;
    for(int i=H-1; i>=0; --i) {
      if(P[i][u]!=P[i][v]) u=P[i][u],v=P[i][v];
    }
    return P[0][u];
  }
private:
  void dfs(int u, int par, int d) {
    P[0][u]=par;
    D[u]=d,L[u]=t++;
    for(int v : G[u]) if(v!=par) dfs(v,u,d+1);
    R[u]=t++;
  }
};

struct BIT {
public:
  int N;
  vector<int> T;
  BIT() {}
  BIT(int N): N(N) { T=vector<int>(N+1,0); }
  // query in [0,r] : ∑ { sum[i] : i=0..r }
  int query(int r) {
    ++r; // 0-based index to 1-based index
    int res=0;
    while(r>0) res+=T[r],r-=lsone(r);
    return res;
  }
  // query ∑ { sum[i] : i=l..r }
  int query(int l, int r) {
    assert(l<=r&&0<=l&&r<N);
    return query(r)-query(l-1);
  }
  // sum[i]+=x
  void add(int i, int x) {
    assert(0<=i&&i<N);
    ++i; // 0-based index to 1-based index
    while(i<=N) T[i]+=x,i+=lsone(i);
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

BinaryLifting T;
BIT bit;

void prepare() {
  T=BinaryLifting(0,G);
  T.buildLiftingTable();
  bit=BIT(2*N);
}

void solve() {
  REP(i,K) {
    int u=A[i];
    mark[u]=true;
    bit.add(T.L[u],1);
    bit.add(T.R[u],-1);
  }

  VI H(K,0);
  REP(i,K) {
    int u=A[i];
    int lca=T.lca(u,root);
    int hu=bit.query(T.L[u])-1,hroot=bit.query(T.L[root]),hlca=bit.query(T.L[lca]);
    int x=hu-hlca,y=hroot-hlca;
    H[i]=x+y+mark[lca];
    assert(H[i]>=0);
  }
  sort(ALL(H));

  REP(i,K) {
    int u=A[i];
    mark[u]=false;
    bit.add(T.L[u],-1);
    bit.add(T.R[u],1);
  }

  REP(i,2)REPE(j,M)dp[i][j]=ModInt(0);
  dp[0][0]=ModInt(1);
  REP(i,K){
    int p1=i%2,p2=1-p1;
    REPE(g,M) dp[p2][g]=ModInt(0);
    for(int g=M; g>=0; --g) {
      int h=H[i];
      dp[p2][g]+=ModInt(max(0,g-h))*dp[p1][g]; // existing group
      if(g>0)dp[p2][g]+=dp[p1][g-1]; // new group
    }
  }
  ModInt res;
  FORE(g,1,M) res+=dp[K%2][g];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q;
  G=VV<int>(N);
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  prepare();
  REP(i,Q) {
    cin>>K>>M>>root;
    --root;
    REP(j,K) cin>>A[j],A[j]--;
    solve();
  }
  
  return 0;
}
