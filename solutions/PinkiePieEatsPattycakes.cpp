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

// $ cp-batch PinkiePieEatsPattycakes | diff PinkiePieEatsPattycakes.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PinkiePieEatsPattycakes.cpp && ./a.out

/*

 8/7/2020

 8:50-9:17 TLE
 9:28 AC

 https://twitter.com/hanseilimak/status/1292580907954536448
 https://codeforces.com/blog/entry/81216

 https://twitter.com/laycrs/status/1291775004644794370
 https://twitter.com/ei1333/status/1291775261864628224
 https://twitter.com/kzyKT_M/status/1291775101034041345

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

bool ok(VI &xs, int x) {
  VI B(N,-1);
  REP(i,SZ(xs)) {
    int cnt=xs[i];
    REP(t,cnt) {
      int p=i+(x+1)*t;
      if(p>=N) return false;
      if(B[p]!=-1) return true;
      B[p]=i;
    }
  }
  REP(i,N) if(B[i]==-1) return false;
  return true;
}

void solve() {
  map<int,int> cnt;
  REP(i,N) cnt[A[i]]++;
  vector<II> ps;
  FORR(kvp,cnt) ps.emplace_back(kvp.second,kvp.first);
  sort(ps.rbegin(),ps.rend());
  VI xs;
  REP(i,SZ(ps)) if(ps[i].first>0) xs.emplace_back(ps[i].first);

  //dumpc(xs);
  int good=0,bad=1e6;
  while(abs(good-bad)>1) {
    int m=(good+bad)/2;
    bool res=ok(xs, m);
    //dump(m,res);
    (res?good:bad)=m;
  }
  cout<<good<<endl;
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*
  N=(int)1e5;
  REP(i,N) A[i]=genRandNum(0,N/2);
  solve();*/

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i],A[i]--;
    solve();
  }

  return 0;
}
