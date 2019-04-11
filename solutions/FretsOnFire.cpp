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

// $ cp-batch FretsOnFire | diff FretsOnFire.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FretsOnFire.cpp && ./a.out

/*
 
 4/6/2019
 
 5:34-6:44, 6:55-7:01 AC after contest ended
 
 https://codeforces.com/blog/entry/66411
 
 My complicated solution was looking at complement set.
 Actually it's easier to sum up ∑ { min(D[i],W) }
 
 */

const int MAX_N=1e6+1;
LL S[MAX_N],L[MAX_N],R[MAX_N];
int N,Q;
const LL Inf=(LL)1e20;

void solve() {
  sort(S,S+N);
  vector<LL> ds(N);
  REP(i,N-1) ds[i]=S[i+1]-S[i];
  ds[N-1]=Inf;
  sort(ALL(ds));
  vector<LL> cum(N+1,0);
  REP(i,N) cum[i+1]=cum[i]+ds[i];
  REP(i,Q) {
    LL l=L[i],r=R[i],W=r-l+1;
    int p=lower_bound(ALL(ds),W)-ds.begin();
    LL res=cum[p]+(N-p)*W;
    printf("%lld ",res);
  }
  println("");
}

void solve_org() {
  sort(S,S+N);
  vector<LL> ds(N-1);
  REP(i,N-1) ds[i]=S[i+1]-S[i];
  sort(ALL(ds));
//  dumpc(ds);
  map<LL,int> M;
  vector<LL> X,cum;
  REP(i,SZ(ds)) {
    LL d=ds[i];
    if(M.count(d)==0) M[d]=i;
    X.push_back(d);
  }
  int K=SZ(X);
//  dumpc(X);
  cum=vector<LL>(K+1,0LL);
  REP(i,K) cum[i+1]=cum[i]+X[i];
  REP(i,Q) {
    LL r=R[i]+1,l=L[i];
    LL d=r-l;
    auto it=M.upper_bound(d);
    int lb=it==M.end()?K:it->second;
    LL rr=S[N-1]+r-1,ll=S[0]+l-1;
    LL x=rr-ll,y=(cum[K]-cum[lb])-d*(K-lb);
    LL res=x-y;
//    dump(i,d,ll,rr,lb,x,y,res);
    printf("%lld ",res);
  }
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>S[i];
  cin>>Q;
  REP(i,Q) cin>>L[i]>>R[i];
  solve();
  return 0;
}
