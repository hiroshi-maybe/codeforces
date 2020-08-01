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

// $ cp-batch CaptainFlintAndCrewRecruitment | diff CaptainFlintAndCrewRecruitment.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CaptainFlintAndCrewRecruitment.cpp && ./a.out

/*

 7/30/2020

 7:35-8:04 give up

 7/31/2020

 21:55-22:16 AC by replacing `cout` with `printf`. WTF.

 https://twitter.com/hanseilimak/status/1289424035114127360
 https://codeforces.com/blog/entry/80828

 */

int N;

void solve() {
  if(N<31) {
    println("NO");
    return;
  }
  println("YES");
  int c=14,d=N-30;
  if(d==6||d==10||d==14) {
    c=15,d=N-16-c;
  }
  set<int> S={6,10,c,d};
  assert(SZ(S)==4);
  assert(16+c+d==N);
  assert(c>=0&&d>=0);
  println("%d %d %d %d", 6,10,c,d);
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}

bool isPrime(LL N) {
  if(N<2) return false;
  for(LL p=2; p*p<=N; ++p) if(N%p==0) return false;
  return true;
}
void nearlyprimes() {
  VI ps;
  for(int a=2; a<=100; ++a) if(isPrime(a)) ps.push_back(a);
  VI nps;
  REP(j,SZ(ps)) REP(i,j) {
    nps.push_back(ps[i]*ps[j]);
  }
  sort(ALL(nps));
  dumpc(nps);
}

void test() {
  FORE(n,1,(int)2e5) {
    N=n;
    dump(N);
    solve();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //nearlyprimes();
  //test();

  int t; cin>>t;
  while(t--) {
    cin>>N;
    solve();
  }

  return 0;
}
