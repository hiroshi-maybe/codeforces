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
 
 8/17/2018
 
 8:40-9:30 time is up
 
 I messed up query implementation. Also I missed the last query in the result.
 
 8/20/2018
 
 20:30-22:20 read editorials
 
 Editorials:
 - http://codeforces.com/blog/entry/61356
 - http://betrue12.hateblo.jp/entry/2018/08/18/181413
 
 Tweets:
  - https://togetter.com/li/1257672
  - https://twitter.com/_olphe/status/1030498603704283137
  - https://twitter.com/my316g/status/1030503849453178881
  - https://twitter.com/natsugir/status/1030533897753219072
  - https://twitter.com/satanic0258/status/1030501833825894400
  - https://twitter.com/n_vip/status/1030499615055831040
 
 Summary:
  - Very typical RMQ problem. I should have come up with segment tree.
  - Tons of bugs 😡
   - Segment tree library had a bug
   - No `Q` case was not handled
   - Q exists but A[0]=0 case was not handled
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+10;
int N,Q;
int A[MAX_N];
const string yes="YES",no="NO";
int L[MAX_N],R[MAX_N];
const int Inf=1e6;

bool ok(int l1, int r1, int l2, int r2) {
  if(l2<l1&&r1<r2) return false;
  if(l1<r2&&r2<r1&&l2<l1) return false;
  if(l1<l2&&l2<r1&&r2>r1) return false;
  return true;
}

void solve_wrong() {
  REPE(i,Q)L[i]=Inf,R[i]=-Inf;
  REP(i,N) {
    SMIN(L[A[i]],i),SMAX(R[A[i]],i);
  }
  
  map<int,int> X;
  for(int i=Q; i>=1; --i) {
    if(X.empty()) {
      X[L[i]]=R[i];
      continue;
    }
    int l1=L[i],r1=R[i];
    
    dump3(i,L[i],R[i]);
    
    if(R[i]<L[i]) continue;
    
    auto it1=X.lower_bound(l1);
    if(it1!=X.begin()) {
      auto it11=it1; --it11;
      int l2,r2; tie(l2,r2)=*it11;
      
      dump4(l1,l2,r1,r2);
      
      if(!ok(l1,r1,l2,r2)) {
        cout<<no<<endl;
        return;
      }
    }
    
    auto it2=X.lower_bound(r1);
    if(it2!=X.begin()) {
      auto it22=it2; --it22;
      int l2,r2; tie(l2,r2)=*it22;
      
      dump4(l1,l2,r1,r2);
      
      if(!ok(l1,r1,l2,r2)) {
        cout<<no<<endl;
        return;
      }
    }
    VI Y;
    for(auto it=it1; it!=it2&&it!=X.end(); ++it) {
      Y.push_back(it->first);
//      dump2(it->first,it->second);
//      dump(distance(it,X.end()));
//      X.erase(it);
//      dump("foo");
    }
    FORR(y,Y) X.erase(y);
    X[l1]=r1;
  }
  int cur=L[Q]==Inf?Q:1;
  REP(i,N) {
    if(A[i]==0) A[i]=cur;
    else cur=A[i];
  }
  cout<<yes<<endl;
  REP(i,N) cout<<A[i]<<(i==N-1?'\n':' ');
}

struct Node {
  static const int Inf=1e9;
  int val;
  Node(int val=Inf): val(val) {}
  static Node IDE; // Identity element in monoid
};
// Merge operation should be associative A`op`(B`op`C) == (A`op`B)`op`C
Node Node::IDE=Node();
Node merge(const Node &a, const Node &b) {
  return Node(min(a.val,b.val));
}
// 🛠 Customize node of segment tree

struct SegmentTree {
public:
  int N__;
  // Put tree array outside the struct to avoid seg fault due to memory allocation of large size array
  Node Tree[4*MAX_N]; // Tree[0..2*N__-1] has values (Tree[0]: all, Tree[1]: left half, Tree[2]: right half, ..)
  SegmentTree(int N) {
    int n=1;
    // Init by power of 2
    while(n<N) n<<=1;
    for(int i=0; i<2*n-1; ++i) Tree[i]=Node::IDE;
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

void solve() {
  SegmentTree RMQ(N);
  vector<Node> ns;
  REP(i,N) {
    ns.push_back(A[i]>0?A[i]:Inf);
  }
  RMQ.build(ns);
  REPE(i,Q)L[i]=Inf,R[i]=-Inf;
  REP(i,N) {
    SMIN(L[A[i]],i),SMAX(R[A[i]],i);
  }
  FORE(q,1,Q) if(L[q]<Inf) {
    int minn=RMQ.query(L[q],R[q]+1).val;
    if(minn<q) {
      cout<<no<<endl;
      return;
    }
  }
  REP(i,N) if(A[i]==0&&L[Q]==Inf) {
    A[i]=Q;
    break;
  }
  int cur=1;
  REP(i,N) {
    if(A[i]==0) A[i]=cur;
    else cur=A[i];
  }
  int cnt=count(A,A+N,Q);
  if(cnt==0) {
    cout<<no<<endl;
  } else {
    cout<<yes<<endl;
    REP(i,N) cout<<A[i]<<(i==N-1?'\n':' ');
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Q;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
