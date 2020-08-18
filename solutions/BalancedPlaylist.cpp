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
// $ cp-batch BalancedPlaylist | diff BalancedPlaylist.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BalancedPlaylist.cpp && ./a.out

/*

 8/15/2020

 17:32-18:40 give up

 8/18/2020

 9:25-11:01 Read editorial and got AC

 https://codeforces.com/blog/entry/70620

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void solve() {
  int mx=*max_element(A,A+N),mn=*min_element(A,A+N);
  if(mx<=2*mn) {
    REP(i,N) cout<<"-1 ";
    cout<<endl;
    return;
  }

  vector<int> as2(1,-1);
  vector<II> AA(3*N);
  REP(i,3*N) AA[i]={A[i%N]*2,i},as2.push_back(A[i%N]*2);
  sort(ALL(as2)),as2.erase(unique(ALL(as2)),as2.end());
  map<int,int> aids;
  REP(i,SZ(as2)) aids[as2[i]]=i;

  const int Inf=1e8;
  auto rmq=makeRmQ(VI(SZ(as2),Inf),Inf);
  VI X(3*N+1,-1);

  for(int i=3*N-1; i>=0; --i) {
    int a=A[i%N];
    int hb=lower_bound(ALL(as2),a)-as2.begin();
    int k=rmq.query(0,hb);

    int lb=upper_bound(ALL(as2),2*a)-as2.begin();
    int j=rmq.query(lb,SZ(as2));

    dump(i,a,lb,hb,j,k);

    rmq.update(aids[2*a],i);
    if(j>k&&k!=Inf) X[i]=k-i;
    else if(j<k&&j!=Inf) X[i]=X[j]+j-i;
  }
  REP(i,N) cout<<X[i]<<" ";
  cout<<endl;
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
