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
template<typename Val> auto makeRMQ(vector<Val> A, Val id) {
  return SegmentTree<Val>(A,id,[](Val a, Val b) { return max(a,b); });
}

// $ cp-batch TheHardWorkOfPaparazzi | diff TheHardWorkOfPaparazzi.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheHardWorkOfPaparazzi.cpp && ./a.out

/*

 10/10/2020

 8:54-9:18, 10:06-0:20 give up

 10/19/2020

 22:05-22:56 AC after reading tweets

 https://twitter.com/hanseilimak/status/1318433264743272450
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.d8vhkj4c6mmf
 https://codeforces.com/blog/entry/83553

 https://twitter.com/Cinnamon_VR/status/1314986687236169730
 https://twitter.com/kyort0n/status/1314987232134979584
 https://twitter.com/kzyKT_M/status/1314986875568844801
 https://twitter.com/ajis_ka/status/1314987566089736192
 https://twitter.com/n_vip/status/1314987880553406464
 https://twitter.com/laycrs/status/1314988344418344960
 https://twitter.com/ngtkana/status/1314988538648125440

 */

const int MAX_N=1e6+1;
III A[MAX_N];
int R,N;

int dp[MAX_N];
void solve() {
  const int Inf=1e8;
  REP(i,N+1) dp[i]=-Inf;
  dp[0]=0;
  int res=0;
  FOR(i,1,N+1) {
    int t1,x1,y1; tie(t1,x1,y1)=A[i];
    FOR(j, max(0,i-1010), i) {
      int t2,x2,y2; tie(t2,x2,y2)=A[j];
      if((t1-t2)>=(abs(x1-x2)+abs(y1-y2))) {
        SMAX(dp[i],dp[j]+1);
        SMAX(res,dp[i]);
      }
    }
    if(i>=1001) SMAX(dp[i-1000],dp[i-1001]);
  }
  cout<<res<<endl;
}

void solve_wrong() {
  int o=3e5;
  auto rmq1=makeRMQ(VI(2*MAX_N,0),0),rmq2=makeRMQ(VI(2*MAX_N),0);
  int res=0;
  REP(i,N) {
    int t; int x,y; tie(t,x,y)=A[i];
    int z=abs(x+y),w=abs(x-y);
    int a=max(0,t-z+o),b=max(0,t-w+o);

    int aa=rmq1.query(0,a+1),bb=rmq2.query(0,b+1);
    int c=max(aa+1,bb+1);
    SMAX(res,c);
    rmq1.update(a,c),rmq2.update(b,c);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>R>>N;
  REP(i,N) {
    int t,x,y; cin>>t>>x>>y;
    --x,--y;
    A[i+1]={t,x,y};
  }
  solve();

  return 0;
}
