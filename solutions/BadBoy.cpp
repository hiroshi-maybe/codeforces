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

// $ cp-batch BadBoy | diff BadBoy.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BadBoy.cpp && ./a.out

/*

 6/18/2021

 7:45-8:25 AC

 https://codeforces.com/blog/entry/91381
 https://twitter.com/torus711/status/1405928698591645696
 https://twitter.com/kiri8128/status/1405927315700293633
 https://twitter.com/kzyKT_M/status/1405927478233767941
 https://twitter.com/laycrs/status/1405927776654303238

 */

LL N,M,I,J;

void solve() {
  vector<pair<LL,LL>> ps;
  for(LL r : vector<LL>{0LL,N-1}) for(LL c : vector<LL>{0LL, M-1}) {
    ps.emplace_back(r,c);
  }

  pair<LL,LL> p0={I,J};
  auto dist=[&](pair<LL,LL> p1, pair<LL,LL> p2) -> LL {
    return abs(p1.first-p2.first)+abs(p1.second-p2.second);
  };
  LL maxd=-1; pair<LL,LL> a,b;
  REP(j,SZ(ps))REP(i,j) {
    auto p1=ps[i],p2=ps[j];
    dump(p1.first,p1.second,p2.first,p2.second);
    LL d=dist(p0,p1)+dist(p1,p2)+dist(p2,p0);
    dump(d);
    if(d>maxd) {
      maxd=d,a=p1,b=p2;
    }
  }
  dump(maxd);
  cout<<a.first+1<<" "<<a.second+1<<" "<<b.first+1<<" "<<b.second+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>M>>I>>J;
    --I,--J;
    solve();
  }

  return 0;
}
