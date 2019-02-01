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

// $ cp-batch VasyaAndMaximumProfit | diff VasyaAndMaximumProfit.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VasyaAndMaximumProfit.cpp && ./a.out

/*
 
 1/31/2019
 
 15:18-16:12 give up
 16:12-17:37,17:50-19:26 read editorials
 21:10-23:00 read editorial (understand segment merge part)

 Gap is activated when corresponding length>=2.
 Try to map merged segment with current minimum gap.
 Invariant is that segment whose length>=2 is active, whose length=1 is pending gap.
 
 2/1/2019
 
 10:30-11:30 read editorial (understand segment tree part) and got AC
 
 Segment tree is applicable when we can "merge" result of left half and right half (divide-and-conquer)
 
 https://codeforces.com/blog/entry/64847
 https://codeforces.com/blog/entry/64833
 
 Key:
  - Combine profit by P[i]=A-C[i]
  - gap(l,r) of some D[i+1]-D[i] covers a segment [l,r) s.t. D[l]-D[l-1]>D[i+1]-D[i] and D[r]-D[r-1]>D[i+1]-D[i]
  - query max profit in the segment [l,r)
   - "Finding subsegments with the maximal sum" in https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-7
  - expand the segment [l,r) with larger gap
 
 */

struct Node {
  static const int id=0;
  LL ans,sum,pref,suf;
  Node(LL val=0LL) : sum(val) {
    LL v=max(val,0LL);
    ans=v,pref=v,suf=v;
  }
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  Node res;
  res.sum=a.sum+b.sum;
  res.ans=max({a.ans,b.ans,a.suf+b.pref});
  res.pref=max(a.pref,a.sum+b.pref);
  res.suf=max(b.suf,b.sum+a.suf);
  return res;
}

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

const int MAX_N=1e6+1;
LL D[MAX_N],C[MAX_N];
LL A;
int N;

void solve() {
  vector<Node> P(N);
  REP(i,N)P[i]=Node(A-C[i]);
  SegmentTree Q(N); Q.build(P);
  vector<pair<LL,int>> DD;
  REP(i,N-1) DD.emplace_back(D[i+1]-D[i],i);
  sort(ALL(DD));
  dumpc(DD);
  set<II> S;
  REP(i,N) S.emplace(i,i+1);
  
  LL res=0;
  REP(i,N) SMAX(res,A-C[i]);
  REP(i,N-1) {
    LL d; int j; tie(d,j)=DD[i];
    auto it=S.upper_bound({j,MAX_N});
    assert(it!=S.begin());
    II R=*it,L=*(--it);
    
    if(L.first==1&&R.second==4) {
      dump(d,j,Q.query(L.first,R.second).ans,d*d);
    }
    dump(L.first,L.second,R.first,R.second);
    SMAX(res,Q.query(L.first,R.second).ans-d*d);
    S.erase(L),S.erase(R);
    S.emplace(L.first,R.second);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>A;
  REP(i,N) cin>>D[i]>>C[i];
  solve();
  
  return 0;
}
