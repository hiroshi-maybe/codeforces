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
// $ cp-batch Searchlights | diff Searchlights.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Searchlights.cpp && ./a.out

/*

 9/30/2020

 8:18-:9:51 give up
 22:30-23:07 Look at editorial and @hitonanode's solution

 10/3/2020

 8:55-9:15 AC

 https://twitter.com/hanseilimak/status/1312426184215425025
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.3i6kntoduuuy
 https://codeforces.com/blog/entry/83233

 https://twitter.com/laycrs/status/1311355550525878273
 https://twitter.com/kzyKT_M/status/1311355241523081217
 https://twitter.com/ngtkana/status/1311357824820154368
 https://twitter.com/satanic0258/status/1311358748506554368
 https://twitter.com/n_vip/status/1311355455638130688

 */

const int MAX_N=1e6+1;
II A[MAX_N],C[MAX_N];
int N,M;

void solve() {
  vector<II> X;
  REP(i,N) {
    int x,y; tie(x,y)=A[i];
    REP(j,M) {
      int xx,yy; tie(xx,yy)=C[j];
      X.emplace_back(max(xx-x+1,0), max(yy-y+1,0));
    }
  }
  sort(X.rbegin(),X.rend());
  //dumpc(X);

  int maxy=0,res=1e9;
  FORR(p,X) {
    int x,y; tie(x,y)=p;
    SMIN(res,x+maxy);
    SMAX(maxy,y);
  }
  SMIN(res,maxy);
  cout<<res<<endl;

  /*
  sort(ALL(D));
  dumpc(D);
  multiset<int> Q;
  REP(i,N) Q.emplace(-D[i].second);
  int res=-(*Q.begin());
  dump(res);
  REP(i,N) {
    int ans=D[i].first;
    auto it=Q.begin();
    if(it!=Q.end()) ans+=-(*it);
    SMIN(res,ans);
    Q.erase(it);
  }
  SMIN(res,D.back().first);
  cout<<res<<endl;*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) {
    int a,b; cin>>a>>b;
    A[i]={a,b};
  }
  REP(i,M) {
    int a,b; cin>>a>>b;
    C[i]={a,b};
  }
  solve();

  return 0;
}
