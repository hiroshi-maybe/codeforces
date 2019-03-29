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

// $ cp-batch ArithmeticProgression | diff ArithmeticProgression.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ArithmeticProgression.cpp && ./a.out

/*
 
 3/28/2019
 
 18:00-18:10, 19:30-20:00 give up
 
 3/29/2019
 
 14:40-14:54 AC
 
 Randomly ask 30 elements and compute gcd of all pairs (no proof)
 
 http://kmjp.hatenablog.jp/entry/2019/03/02/1000
 
 */

int N;

int gcd(int a, int b) { return b==0?a:gcd(b,a%b); }

int ans(int a0, int d) {
  cout<<"! "<<a0<<" "<<d<<endl;
  exit(0);
}

int ask1(int i) {
  cout<<"? "<<i<<endl;
  int a; cin>>a;
  assert(a!=-1);
  if(a==-1) exit(0);
  return a;
}

int ask2(int x) {
  cout<<"> "<<x<<endl;
  int r; cin>>r;
  assert(r!=-1);
  if(r==-1) exit(0);
  return r;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}

void solve() {
  int good=1e9,bad=0;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    int a=ask2(m);
    (a==0?good:bad)=m;
  }
  int maxa=good;
  int cnt=30;
  dump(maxa);
  
  set<int> viz,S; S.emplace(maxa);
  while(cnt--) {
    int i=1;
    while(SZ(viz)<N) {
      int j=genRandNum(1,N+1);
      if(!viz.count(j)) {
        viz.emplace(j);
        i=j;
        break;
      }
    }
    int x=ask1(i);
    S.emplace(x);
  }
  VI as(ALL(S));
  int d=as.back()-as.front();
  int M=SZ(as);
  REP(i,M)FOR(j,i+1,M) d=gcd(d,as[j]-as[i]);
  int a0=maxa-d*(N-1);
  ans(a0,d);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
