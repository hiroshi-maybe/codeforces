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

/*
 
 11/16/2018
 
 20:15-21:10 give up
 21:30 pause
 
 22:00-22:50 read editorial
 
 11/17/2018
 
 12:20-13:20, 14:35-17:11 got AC (1 hour debug to find RE due to binary lifting bug)
 
 https://codeforces.com/blog/entry/63199
 
 Drop a special condition (removal of one vertex) and seek for how to solve it.
 
 Finding LCA of a set of vertices directly is not easy to search.
 Only query of a vertex LCA(u) is possible in O(lg N)
 I should have digged deeply how to find constant number of candidates.
 
 Once we can figuer out that left most or right most vertices are candidates,
 then vertex timestamping in the dfs comes up.
 
 */

const int MAX_N=1e5+1;
struct Node {
  static const int Inf=1e9;
  int val;
  int key;
  Node(int val=Inf, int key=-1): val(val), key(key) {}
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  int v,k;
  if(a.val<b.val) v=a.val,k=a.key;
  else v=b.val,k=b.key;
  return Node(v,k);
}
// 🛠 Customize node of segment tree

struct SegmentTree {
public:
  int N__;
  vector<Node> Tree;
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    this->Tree=vector<Node>(2*n,Node::IDE);
    this->N__=n;
  }
  
  // Initialize tree with `ns`
  void build(const vector<Node> &ns) {
    buildTree(ns,0,0,N__);
  }
  
  // Update k-th (0-indexed) value
  void update(int i, const Node &x) {
    updateTree(i,x,0,0,N__);
  }
  
  // query in range [L,R)
  Node query(int L, int R) {
    return queryTree(L,R,0,0,N__);
  }
private:
  void buildTree(const vector<Node> &ns, int i, int l, int r) {
    if (l==r-1) {
      if(l<ns.size()) Tree[i]=ns[l];
      return;
    }
    
    int mid=l+(r-l)/2;
    buildTree(ns,2*i+1,  l,mid); // left child
    buildTree(ns,2*i+2,mid,  r); // right child
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  void updateTree(int p, const Node &x, int i, int l, int r) {
    if (l==r-1) { Tree[i]=x; return; }
    
    int mid=l+(r-l)/2;
    if(p<mid) updateTree(p,x,2*i+1,  l,mid);
    else      updateTree(p,x,2*i+2,mid,  r);
    
    Tree[i]=merge(Tree[2*i+1],Tree[2*i+2]);
  }
  
  Node queryTree(int L, int R, int i, int l, int r) {
    // out of range
    if (r<=L||R<=l) return Node::IDE;
    
    // all covered
    if (L<=l&&r<=R) return Tree[i];
    
    // partially covered
    int mid=l+(r-l)/2;
    Node a=queryTree(L,R,2*i+1,  l,mid);
    Node b=queryTree(L,R,2*i+2,mid,  r);
    Node res=merge(a,b);
    return res;
  }
};

template <class T> struct RMQ {
public:
  T Inf;
  vector<T> A;
  int SIZE; // normalized size of original array
  RMQ(int N, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(N);
    this->A=vector<T>(2*SIZE,Inf);
  }
  // O(N) initialization
  RMQ(vector<T> &X, T Inf) : Inf(Inf) {
    this->SIZE=calcsize(X.size());
    this->A=vector<T>(2*SIZE,Inf);
    for(int i=0; i<X.size(); ++i) A[i+SIZE-1]=X[i];
    for(int i=SIZE-2; i>=0; --i) {
      A[i]=min(A[2*i+1],A[2*i+2]);
    }
  }
  void update(int i, T v) {
    i+=SIZE-1;
    A[i]=v;
    while(i>0) {
      i=(i-1)/2;
      A[i]=min(A[2*i+1],A[2*i+2]);
    }
  }
  // half-open range [ql,qr)
  T query(int ql, int qr) {
    return qu(ql,qr,0,0,SIZE);
  }
private:
  // i: node index (<SIZE if not leaf)
  T qu(int ql, int qr, int i, int l, int r) {
    if(qr<=l||r<=ql) return Inf;
    if(ql<=l&&r<=qr) return A[i];
    int m=(l+r)/2;
    
    return min(qu(ql,qr,2*i+1,l,m),qu(ql,qr,2*i+2,m,r));
  }
  int calcsize(int N) {
    int n=1; while(n<N) n<<=1;
    return n;
  }
};

struct BinaryLifting {
public:
  vector<vector<int>> G;
  int V,root;
  int H;
  vector<vector<int>> P; // parent P[bits][vertices], bits=floor(lg N)+1
  vector<int> D; // depth for LCA query D[vertices]
  
  BinaryLifting(int root, int V) : V(V), root(root) {
    G=vector<vector<int>>(V);
    D=vector<int>(V,0);
  }
  void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  BinaryLifting(int root, vector<vector<int>> &G) : G(G), root(root) {
    V=G.size();
    D=vector<int>(V,0);
  }
  void buildLiftingTable() {
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
  // query to find an ancestor `d` vertices above
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
    D[u]=d;
    for(int v : G[u]) if(v!=par) {
      dfs(v,u,d+1);
    }
  }
};

// $ ../batch Company | diff Company.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG Company.cpp && ./a.out
//const int MAX_N=1e5+1;
VI G[MAX_N];
int N,Q;
BinaryLifting bl(0,MAX_N);
int tin[MAX_N],tout[MAX_N];
SegmentTree inq(MAX_N),outq(MAX_N);

void solve_segtree(int l, int r) {
  Node L=inq.query(l,r);
  Node R=outq.query(l,r);
  
//  dump4(l,r,L.key,R.key);
//  dump4(l,r,L.val,R.val);
  
  auto rem = [&](int l, int r, int a) -> II {
    Node LA=inq.query(l,a),RA=outq.query(l,a);
    Node LB=inq.query(a+1,r),RB=outq.query(a+1,r);
    
    II la={LA.val,LA.key},ra={RA.val,RA.key},lb={LB.val,LB.key},rb={RB.val,RB.key};
    
    II ll=min(la,lb),rr=min(ra,rb);
    
    int x=bl.lca(ll.second,rr.second);
//    dump4(a,ll.second,x,bl.D[x]);
    return {bl.D[x],a};
  };
  
  II res=rem(l,r,L.key);
  SMAX(res,rem(l,r,R.key));
  println("%d %d",res.second+1,res.first);
}

void dfs(int u, int pre, int &t) {
  tin[u]=t++;
  FORR(v,G[u])if(v!=pre)dfs(v,u,t);
  tout[u]=t;
}

void solve(int l, int r, RMQ<II> &iq, RMQ<II> &oq) {
  II L=iq.query(l,r);
  II R=oq.query(l,r);
  
  //  dump4(l,r,L.key,R.key);
  //  dump4(l,r,L.val,R.val);
  
  auto rem = [&](int l, int r, int a) -> II {
    II LA=iq.query(l,a),RA=oq.query(l,a);
    II LB=iq.query(a+1,r),RB=oq.query(a+1,r);
    
    II la={LA.first,LA.second},ra={RA.first,RA.second},lb={LB.first,LB.second},rb={RB.first,RB.second};
    
    II ll=min(la,lb),rr=min(ra,rb);
    
    int x=bl.lca(ll.second,rr.second);
    //    dump4(a,ll.second,x,bl.D[x]);
    return {bl.D[x],a};
  };
  
  II res=rem(l,r,L.second);
  SMAX(res,rem(l,r,R.second));
  println("%d %d",res.second+1,res.first);
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> gen_tree(int N) {
  vector<int> P(N-1,0);
  printf("%d\n",N-1);
  for(int u=1; u<=N-1; ++u) {
    P[u-1]=genRandNum(0,u);
    printf("%d %d\n",u,P[u-1]);
  }
  // parent of u+1 = P[u] (P[u]<u+1)
  return P;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  /*
  VI x=gen_tree(1e5);
  cout<<1e5<<endl;
  FORR(y,x) cout<<y+1<<" ";
  cout<<endl;*/
  
  cin>>N>>Q;
  bl=BinaryLifting(0,N);
  REP(i,N-1) {
    int p; cin>>p;
    --p;
    G[p].push_back(i+1);
    bl.addEdge(p,i+1);
  }
  bl.buildLiftingTable();
  int t=0;
  dfs(0,-1,t);
  
  /*
  vector<Node> ms(N);
  REP(i,N) ms[i]=Node(tin[i],i);
  inq.build(ms);
  
  vector<Node> Ms(N);
  REP(i,N) Ms[i]=Node(-tout[i],i);
  outq.build(Ms);*/
  
  vector<II> ms(N),Ms(N);
  REP(i,N) ms[i]={tin[i],i};
  REP(i,N) Ms[i]={-tout[i],i};
  RMQ<II> iq(ms,{1e8,-1}),oq(Ms,{1e8,-1});
  
  REP(i,Q) {
    int l,r; cin>>l>>r;
    --l;
    solve(l,r,iq,oq);
  }
  
  return 0;
}
