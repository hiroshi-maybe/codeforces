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
template <typename Val, typename Delay>
struct LazySegmentTree {
  int N_/* adjusted N*/,head/* head of leaf */;
  vector<Val> tree;
  vector<Delay> delay;
  Val id;
  Delay delayId;
  using Merge = function<Val(Val,Val)>;
  using Apply = function<Val(Val,Delay)>;
  using MergeDelay = function<Delay(Delay,Delay)>;
  Merge merge;
  Apply apply;
  MergeDelay mergeDelay;
public:
  LazySegmentTree(int N, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) { prep(N,id,delayId,merge,apply,mergeDelay); }
  LazySegmentTree(vector<Val> A, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) { prep(A.size(),id,delayId,merge,apply,mergeDelay),this->build(A); }
  LazySegmentTree& prep(int N, Val id, Delay delayId, Merge merge, Apply apply, MergeDelay mergeDelay) {
    this->id=id,this->delayId=delayId;
    this->merge=merge,this->apply=apply,this->mergeDelay=mergeDelay;
    int n=1; while(n<N) n<<=1; // Init by power of 2
    this->tree=vector<Val>(2*n-1,id),this->delay=vector<Delay>(2*n-1,delayId);
    this->N_=n,this->head=N_-1;
    return *this;
  }
  void build(const vector<Val> &ns) {
    for(int i=0; i<ns.size(); ++i) tree[i+N_-1]=ns[i];
    for(int i=N_-2; i>=0; --i) mergeAt(i);
  } // Initialize tree with `ns`
  void update(int ql, int qr, const Delay &delay) { updateTree(ql,qr,delay,0,0,N_); }
  Val query(int ql, int qr) { return queryTree(ql,qr,0,0,N_); } // query in range [ql,qr)
private:
  Val mergeAt(int i) { return tree[i]=merge(tree[2*i+1],tree[2*i+2]); }
  Val queryTree(const int ql, const int qr, int i, int tl, int tr) {
    if(tr<=ql||qr<=tl) return id; // out of range
    applyDelay(i);
    if(ql<=tl&&tr<=qr) { assert(delay[i]==delayId); return tree[i]; } // all covered
    int mid=tl+(tr-tl)/2; // partially covered
    return merge(queryTree(ql,qr,2*i+1, tl,mid),
                 queryTree(ql,qr,2*i+2,mid, tr));
  }
  void updateTree(const int ql, const int qr, Delay d, int i, int tl, int tr) {
    if(ql<=tl&&tr<=qr) mergeDelayAt(i,d),applyDelay(i); // all covered
    else if(ql<tr&&tl<qr) { // partially coverd
      int mid=tl+(tr-tl)/2;
      applyDelay(i),updateTree(ql,qr,d,2*i+1,tl,mid),updateTree(ql,qr,d,2*i+2,mid,tr),mergeAt(i);
    } else applyDelay(i);
  }
  void applyDelay(int i) {
    if(delay[i]==delayId) return;
    if(i<head) pushdownAt(i);
    tree[i]=apply(tree[i],delay[i]),delay[i]=delayId;
  }
  void pushdownAt(int i) { mergeDelayAt(2*i+1,delay[i]),mergeDelayAt(2*i+2,delay[i]); }
  void mergeDelayAt(int i, Delay d) { delay[i]=mergeDelay(delay[i],d); }
};
template <typename T> struct BIT {
public:
  int N;
  vector<T> A;
  BIT() {}
  BIT(int N) { init(N); }
  void init(int N) {
    this->N=N;
    A=vector<T>(N+1,0);
  }
  // query ∑ { sum[i] : i=l..<r }
  T query(int l, int r) {
    assert(l<=r&&0<=l&&r<=N);
    return query(r)-query(l);
  }
  // min index s.t. dat[0..i]>x
  int upperbound(T x) {
    int good=N+1,bad=0;
    while(abs(good-bad)>1) {
      int m=(good+bad)/2;
      (query(m)>x?good:bad)=m;
    }
    return good-1;
  }
  // sum[i]+=x
  void add(int i, T x) {
    assert(0<=i&&i<N);
    ++i;
    while(i<=N) A[i]+=x,i+=lsone(i);
  }
  // sum[i]=x
  void update(int i, T v) {
    T pre=query(i+1)-query(i);
    add(i,v-pre);
  }
private:
  int lsone(int i) { return i&-i; }
  // query in [0,r) : ∑ { sum[i] : i=0..r-1 }
  T query(int r) {
    assert(0<=r&&r<=N);
    T res=0;
    while(r>0) res+=A[r],r-=lsone(r);
    return res;
  }
};
// $ cp-batch Editor | diff Editor.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Editor.cpp && ./a.out

/*
 
 11/29/2019
 
 7:55-9:00 give up
 9:50 AC
 
 17:30-19:30 apply my own lazy segment tree. It TLEs due to test cases added after contest though :(
 
 */

int N;
string S;
void solve() {
  string cur(N,' ');
  auto merge=[](II a, II b) { return make_pair(min(a.first,b.first),max(a.second,b.second)); };
  auto apply=[](II a, int addition) { return make_pair(a.first+addition,a.second+addition); };
  auto add=[](int a, int b) { return a+b; };
  LazySegmentTree<II,int> T(N+1,make_pair(0,0),0,merge,apply,add);
  auto f=[&]() ->int {
    auto p=T.query(0,N),q=T.query(N-1,N);
//    dump(q.first,q.second);
//    assert(q.first==q.second);
    if(q.second!=0||p.first<0) {
      return -1;
    }
    int res=p.second;
    assert(res>=0);
    return res;
  };
  
  int p=0,res=0;
  REP(i,N) {
    int newv=0;
    if(S[i]=='R') {
      ++p;
    } else if(S[i]=='L') {
      --p;
      p=max(p,0);
    } else {
      char c=cur[p];
      int pre=0;
      if(c=='(') pre=1;
      else if(c==')') pre=-1;
      
      if(S[i]=='(') newv=1;
      else if(S[i]==')') newv=-1;
      else newv=0;
      cur[p]=S[i];
      T.update(p,N,newv-pre);
      res=f();
    }
    printf("%d ", res);
  }
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
