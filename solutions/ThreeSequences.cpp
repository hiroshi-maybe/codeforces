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

// $ cp-batch ThreeSequences | diff ThreeSequences.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeSequences.cpp && ./a.out

/*

 9/12/2020

 7:48-10:10 give up

 12:50-13:35, 14:45-17:20 read tweets and editorial and got AC

 https://codeforces.com/blog/entry/82560
 https://twitter.com/hanseilimak/status/1304961518753050624

 https://twitter.com/laycrs/status/1304808493703069701
 https://twitter.com/kotatsugame_t/status/1304814768549634049
 https://twitter.com/kzyKT_M/status/1304808460408614913
 https://twitter.com/ei1333/status/1304808619733479425

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

const LL Inf=1e18;
void solve() {
  vector<LL> B(N-1);
  LL K=0;
  REP(i,N-1) B[i]=A[i+1]-A[i];
  REP(i,N-1) K+=max(B[i],0LL);
  auto f=[&]() -> LL {
    LL res=(A[0]+K)/2;
    return max(res,A[0]+K-res);
  };
  cout<<f()<<endl;
  int Q; cin>>Q;
  while(Q--) {
    int l,r; LL x; cin>>l>>r>>x;
    --l;
    //dump(Q,l,r);
    if(l==0) A[0]+=x;
    else {
      l-=1;
      K-=max(B[l],0LL);
      B[l]+=x;
      K+=max(B[l],0LL);
    }
    r-=1;
    if(r<N-1) {
      K-=max(B[r],0LL);
      B[r]-=x;
      K+=max(B[r],0LL);
    }
    //dump(A[0],K);
    cout<<f()<<endl;
  }
}

void solve_wrong() {
  BIT<LL> po(N),ne(N);
  REP(i,N-1) {
    if(A[i]<=A[i+1]) po.add(i,A[i+1]-A[i]);
    else ne.add(i,A[i]-A[i+1]);
  }

  auto calc=[&]() -> LL {
    LL suma=po.query(0,N),sumb=ne.query(0,N);
    vector<LL> ss={A[0]+suma,A[N-1]+sumb};
    dump(suma,A[0],ss[0],sumb,A[N-1],ss[1]);
    LL res=-Inf;
    REP(i,2) SMAX(res,(ss[i]+1)/2);
    return res;
  };
  cout<<calc()<<endl;

  int Q; cin>>Q;
  while(Q--) {
    int l,r; LL x; cin>>l>>r>>x;
    --l;
    if(l==0) A[0]+=x;
    if(r==N) A[N-1]+=x;
    VI is={l-1,r-1};
    dump(Q);
    FORR(i,is) {
      LL xx=i==l-1?x:-x;
      if(i<0) continue;
      if(i>=N-1) continue;
      LL cur=po.query(i,i+1)-ne.query(i,i+1);
      dump(i,cur);
      (cur>=0?po:ne).update(i,-abs(cur));
      if(cur>=0&&xx<=0) po.update(i,cur+abs(xx));
      else if(cur<=0&&xx>=0) ne.update(i,abs(cur)+xx);
      else {
        LL cur2=abs(cur)-abs(xx);
        if(cur2<0) (cur>=0?ne:po).update(i,abs(cur2));
        else (cur>=0?po:ne).update(i,abs(cur2));
      }
    }
    cout<<calc()<<endl;
  }
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
