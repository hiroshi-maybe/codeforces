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
template <typename Val>
struct SegmentTree {
  int N_; // adjusted N
  vector<Val> tree;
  Val id;
  using Merge = function<Val(Val,Val)>;
  Merge merge;
public:
  SegmentTree(int N, Val id, Merge merge) { prep(N,id,merge); }
  SegmentTree(vector<Val> A, Val id, Merge merge) { prep(A.size(),id,merge), this->build(A); }
  SegmentTree& prep(int N, Val id, Merge merge) {
    this->id=id,this->merge=merge;
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id), this->N_=n;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int i, const Val &x) { i+=N_-1,tree[i]=x; while(i>0) i=(i-1)/2,tree[i]=mergeAt(i); } // Update k-th (0-indexed) value
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if (tr<=ql||qr<=tl) return id; // out of range
    if (ql<=tl&&tr<=qr) return tree[i]; // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
};
template<typename Val> auto makeRmQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return min(a,b); });
}
template<typename Val> auto makeRMQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return max(a,b); });
}
// $ cp-batch YetAnotherYetAnotherTask | diff YetAnotherYetAnotherTask.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address YetAnotherYetAnotherTask.cpp && ./a.out

/*

 5/28/2020

 8:41-9:40 give up

 5/29/2020

 8:30-9:37 read tweets and got AC

 https://codeforces.com/blog/entry/78116
 https://twitter.com/hanseilimak/status/1266842259388903424

 https://twitter.com/n_vip/status/1266049705680621568?s=20

 https://twitter.com/kzyKT_M/status/1266045672962195456?s=20
 https://twitter.com/laycrs/status/1266045441205874688?s=20
 https://twitter.com/tsutaj/status/1266046617351643136?s=20
 https://twitter.com/n_vip/status/1266049705680621568?s=20

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

const int Inf=1e9;
void solve() {
  LL res=0;
  const LL Inf=1e13;
  FORE(k,0,30) {
    vector<LL> B(N,-Inf),cum(N+1,0);
    REP(i,N)if(A[i]<=k) B[i]=A[i];
    LL mins=0;
    REP(i,N) {
      cum[i+1]=cum[i]+B[i];
      SMAX(res,cum[i+1]-mins-k);
      //dump(k,i,res);
      SMIN(mins,cum[i+1]);
    }
  }
  cout<<res<<endl;
}

void solve_rmq() {
  int res=0;
  VI as(A,A+N);
  VI cuml(N+1);
  REP(i,N) cuml[i+1]=cuml[i]+A[i];
  auto rmq=makeRmQ(cuml,Inf);
  REPE(k,30) {
    int sum=0;
    VI ps(31,-1);
    REP(i,N) {
      sum+=A[i];
      if(A[i]>=0)ps[A[i]]=i;
      int lb=-1;
      FORE(kk,k+1,30) if(ps[kk]>=0) SMAX(lb,ps[kk]);
      int mincum=rmq.query(lb+1,i+1);
      //if(k==5&&i==3) dump(k,i,lb,mincum,sum);
      SMAX(res,sum-mincum-k);
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  int res=0;
  VI as(A,A+N);
  VI cuml(N+1);
  REP(i,N) cuml[i+1]=cuml[i]+A[i];
  auto rmq=makeRmQ(cuml,Inf);
  VI ps(31,-1);
  int sum=0;
  REP(i,N) {
    sum+=A[i];
    if(A[i]>0) {
      ps[A[i]]=i;
      int x=Inf;
      FOR(a,1,31) if(ps[a]>=0) {
        int cum=ps[a]==0?0:rmq.query(0,ps[a]);
        SMIN(x,sum-cum-a);
        //dump(i,sum,a,ps[a],cum,sum-cum-a);
      }
      SMAX(res,x);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
