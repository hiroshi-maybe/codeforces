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
// $ cp-batch SequenceSorting | diff SequenceSorting.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SequenceSorting.cpp && ./a.out

/*
 
 10/6/2019
 
 8:47-9:33 TLE
 15:30-16:30, 21:20-22:15 AC
 
 I had two misunderstandings :(
 
 1. total number of non-overlap interval sequences
   => max number of non-overlap interval sequences

 Correct answer of A={3,1,2} is not 2 but 1.
 
 2. non-overlap sub-sequences
   => non-overlap "consecutive" sequences
 
 Suppose we have A={1,3,5,2,4}.
 {1,3,5} does not contribute because `2` cannot jump between 1 and 3
 
 https://codeforces.com/blog/entry/70358
 https://twitter.com/hanseilimak/status/1181085695764418560
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int Q,N;

void solve() {
  VV<int> ps(N+1);
  REP(i,N) ps[A[i]].push_back(i);
  VI lbs,rbs;
  int M=0;
  REPE(i,N) if(SZ(ps[i])) {
    lbs.push_back(ps[i].front()),rbs.push_back(ps[i].back()),++M;
  }
  int ma=1,pre=-1,cur=0;
  REP(i,M) {
    int lb=lbs[i],rb=rbs[i];
    if(pre<lb) SMAX(ma,++cur);
    else cur=1;
    pre=rb;
  }
  cout<<M-ma<<endl;
}

void solve_wrong() {
  VV<int> ps(N+1);
  REP(i,N) ps[A[i]].push_back(i);
  BIT<int> bit(N+1);
  VI lbs,rbs;
  int M=0;
  REPE(i,N) if(SZ(ps[i])) {
    lbs.push_back(ps[i].front()),rbs.push_back(ps[i].back()),++M;
  }
  reverse(ALL(lbs)),reverse(ALL(rbs));
  int res=0;
  REP(i,M) {
    int lb=lbs[i],rb=rbs[i];
    int cnt=bit.query(0,rb);
//    dump(i,lb,rb,cnt);
    if(cnt>0)++res;
    bit.add(lb,1);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>Q;
  REP(i,Q) {
    cin>>N;
    REP(i,N)cin>>A[i];
    solve();
  }
  
  return 0;
}
