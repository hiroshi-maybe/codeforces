
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

// $ cp-batch PaintingTheFence | diff PaintingTheFence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PaintingTheFence.cpp && ./a.out

/*
 
 4/1/2019
 
 15:24-15:57 AC
 
 https://codeforces.com/blog/entry/65752
 
 Editorial is solving without BIT.
 It's possible because update query is not necessary.
 
 */

const int MAX_N=1e6+1;
LL L[MAX_N],R[MAX_N];
int N,Q;

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

int cum[MAX_N];
void solve_org() {
  BIT<int> bit1(N+10),bit2(N+10);
  REP(i,Q) {
    FORE(j,L[i],R[i]) cum[j]++;
  }
  
  int tot=0;
  REPE(i,N) {
    if(cum[i]==1) bit1.add(i,1);
    if(cum[i]==2) bit2.add(i,1);
    if(cum[i]>0) ++tot;
  }
  
  int res=0;
  REP(i,Q)FOR(j,i+1,Q) {
    int l1=L[i],l2=L[j],r1=R[i]+1,r2=R[j]+1;
    int a=max(l1,l2),b=min(r1,r2);
    int x=0,y=0;
    if(b-a>=0) {
      x=bit2.query(a,b);
      y=bit1.query(min(l1,l2),a)+bit1.query(b,max(r1,r2));
    } else {
      y=bit1.query(l1,r1)+bit1.query(l2,r2);
    }
//    dump(i,j,l1,r1,l2,r2);
//    dump(i,j,tot,x,y,tot-x-y);
    SMAX(res,tot-x-y);
  }
  cout<<res<<endl;
}

int cum2[MAX_N];
void solve() {
  int res=0;
  REP(i,Q) FORE(j,L[i],R[i]) cum[j]++;
  REP(i,Q) {
    FORE(j,L[i],R[i]) cum[j]--;
    REPE(i,N) cum2[i+1]=cum2[i]+(cum[i]==1);
    int sum=0; REPE(i,N) sum+=cum[i]>0;
    int x=MAX_N;
    REP(j,Q)if(i!=j) {
      int r=R[j],l=L[j];
      SMIN(x,cum2[r+1]-cum2[l]);
    }
    SMAX(res,sum-x);
    FORE(j,L[i],R[i]) cum[j]++;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q;
  REP(i,Q) cin>>L[i]>>R[i];
  solve();
  
  return 0;
}
