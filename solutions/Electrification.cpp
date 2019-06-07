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

// $ cp-batch Electrification | diff Electrification.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Electrification.cpp && ./a.out

/*
 
 6/5/2019
 
 9:01-9:27 WA
 10:17-11:10 give up
 11:20-11:50 read twitter timeline and got AC
 11:50-12:16 add binary search solution inspired by @betrue12
 
 NO unimodal property. Ternary search NEVER works. PROVE before moving forward 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 fix `x` -> furthest among `k` closest points
 
 https://codeforces.com/blog/entry/67484
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,K;

pair<int,int> g(LL X) {
  REP(i,N) {
    int p=upper_bound(A+i,A+N,A[i]+X*2)-A;
    if(p-i>=K+1) return {true,i};
  }
  return {false,-1};
}
void solve() {
  LL good=1e10,bad=-1;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    auto res=g(mid);
    (res.first?good:bad)=mid;
  }
  int i=g(good).second;
//  dump(i,A[i],good);
  cout<<(A[i]+good)<<endl;
}

void solve_bruteforce() {
  int p=0;
  REP(i,N-K) {
    if(A[i+K]-A[i]<A[p+K]-A[p]) p=i;
  }
  cout<<(A[p]+A[p+K])/2<<endl;
}

LL f(LL x) {
  vector<LL> D(N);
  REP(i,N) D[i]=abs(A[i]-x);
  sort(ALL(D));
  return D[K];
}
void solve_wrong() {
  vector<LL> X;
  REP(i,N) {
    X.push_back(A[i]);
    if(i==N-1) continue;
    LL a=(A[i]+A[i+1])/2;
    if(a!=X.back()) X.push_back(a);
    if(a+1!=A[i+1]) X.push_back(a+1);
  }
  int M=SZ(X);
  LL l=0,r=M-1;
  while(abs(r-l)>2) {
    LL ll=l+(r-l)/3,rr=r-(r-l)/3;
    LL a=f(X[ll]),b=f(X[rr]);
//    dump(ll,a,rr,b);
    if(a<b) r=rr;
    else if(a>b) l=ll;
    else l=ll,r=rr;
  }
  LL res=l;
  FOR(i,l,l+3) if(i<M&&f(X[i])<f(X[res])) res=i;
  cout<<X[res]<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N>>K;
    REP(j,N) cin>>A[j];
    solve();
  }
  
  return 0;
}
