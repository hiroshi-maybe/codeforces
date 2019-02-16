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

// $ cp-batch LunarNewYearAndFoodOrdering | diff LunarNewYearAndFoodOrdering.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LunarNewYearAndFoodOrdering.cpp && ./a.out

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

/*
 
 2/15/2019
 
 11:40-12:23 WA
 12:34 give up
 13:45-14:14 AC (I was misunderstanding problem statement. fucking poor sample🖕)
 
 14:36 got AC by BIT solution
 
 https://codeforces.com/blog/entry/64928
 https://misteer.hatenablog.com/entry/CF536
 https://naoyat.hatenablog.jp/entry/CodeforcesRound536Div2
 https://mumumucoder.hatenablog.com/entry/2019/02/02/105554
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],C[MAX_N];
int N,M;
vector<tuple<LL,int,LL>> X;
MAPII typem;
BIT<LL> bit;

int l=0;
void solve__(int T, LL cnt) {
  LL cost,cap; int i; tie(cost,i,cap)=X[typem[T]];
  int x=min(cnt,cap);
  LL res=cost*x; X[typem[T]]={cost,i,cap-x};
  dump(T,cnt,typem[T],x,cap,cap-x);
  cnt-=x;
  for(; l<N&&cnt>0; ++l) {
    LL cost,cap; int i; tie(cost,i,cap)=X[l];
    int x=min(cnt,cap);
    res+=cost*x,X[l]={cost,i,cap-x};
    dump(T,cnt,l,x,cap-x);
    cnt-=x;
    if(cnt==0) break;
  }
  
  REP(i,N) {
    LL cost,cnt; int j; tie(cost,j,cnt)=X[i];
    dump(cost,j,cnt);
  }
  
  if(cnt>0) {
    cout<<0<<endl;
  } else {
    cout<<res<<endl;
  }
}

void solve(int T, LL cnt) {
  LL res=0;
  int i=typem[T];
  dump(T,cnt,i,res);
  LL x=bit.query(i,i+1);
  x=min(x,cnt);
  LL cost=get<0>(X[i]);
  res+=x*cost;
  bit.add(i,-x);
  cnt-=x;
  dump(T,cnt,i,x,res);
  int l=bit.upperbound(0);
  dump(l);
  for(int i=l; cnt>0&&i<N; ++i) {
    dump(i);
    LL x=bit.query(i,i+1);
    x=min(x,cnt);
    res+=get<0>(X[i])*x;
    bit.add(i,-x);
    cnt-=x;
  }
  if(cnt>0) res=0;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>C[i];
  
  X.resize(N);
  REP(i,N) X[i]={C[i],i,A[i]};
  sort(ALL(X));
  bit=BIT<LL>(N);
  REP(i,N) {
    bit.add(i,get<2>(X[i]));
    typem[get<1>(X[i])]=i;
  }
  REP(i,N) {
    LL cost,cnt; int j; tie(cost,j,cnt)=X[i];
    dump(cost,j,cnt);
  }
  
  REP(i,M) {
    int cnt,T; cin>>T>>cnt;
    --T;
    solve(T,cnt);
  }
  
  return 0;
}
