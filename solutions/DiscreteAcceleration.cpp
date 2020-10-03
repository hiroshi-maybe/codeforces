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

// $ cp-batch DiscreteAcceleration | diff DiscreteAcceleration.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DiscreteAcceleration.cpp && ./a.out

/*

 9/30/2020

 8:04-8:18 AC

 https://codeforces.com/blog/entry/83233
 https://twitter.com/hanseilimak/status/1312262072428756992

 */

const int MAX_N=1e6+1;
LL A[MAX_N],L;
int N;

vector<LL> as0,as1;
double dist(double T, vector<LL> &as) {
  double t=T;
  double d=0,s=1;
  for(int i=0; i<N-1&&t>0; ++i) {
    double tt=min(t,(as[i+1]-as[i])/s);
    d+=s*tt,t-=tt,s+=1;
  }
  return d;
}
bool ok(double T) {
  double d1=dist(T,as0),d2=dist(T,as1);
  return d1+d2>=L;
}

void solve() {
  N+=2;
  as0=vector<LL>(A,A+N),as1=vector<LL>(N);
  REP(i,N) as1[i]=L-as0[N-i-1];
  double good=1e9,bad=0;
  REP(_,100) {
    double m=(good+bad)/2;
    bool res=ok(m);
    (res?good:bad)=m;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>L;
    REP(i,N) cin>>A[i+1];
    A[N+1]=L;
    solve();
  }

  return 0;
}
