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

// $ cp-batch PlanetLapituletti | diff PlanetLapituletti.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PlanetLapituletti.cpp && ./a.out

/*

 3/6/2021

 6:18-6:48 AC

 https://twitter.com/hanseilimak/status/1368374762498527233
 https://codeforces.com/blog/entry/88422

 */

int H,M;
string S;
VI cp={0,1,5,-1,-1,2,-1,-1,8,-1};

II reflect(int x) {
  int d1=x/10,d2=x%10;
  return {cp[d2],cp[d1]};
}

int dig(char c) { return c-'0'; }
int parse(string s) {
  int h=dig(s[0])*10+dig(s[1]);
  int m=dig(s[3])*10+dig(s[4]);
  return h*M+m;
}
string tos(int h, int m) {
  string res(5,':');
  res[0]='0'+h/10,res[1]='0'+h%10,res[3]='0'+m/10,res[4]='0'+m%10;
  return res;
}

void solve() {
  vector<pair<int,string>> ts;
  int baset=parse(S);
  REP(t,H*M) {
    int h=t/M,m=t%M;
    auto mm=reflect(h),hh=reflect(m);
    if(mm.first==-1||mm.second==-1) continue;
    if(hh.first==-1||hh.second==-1) continue;
    int mmm=mm.first*10+mm.second,hhh=hh.first*10+hh.second;
    if(hhh>=H||mmm>=M) continue;
    int d=t-baset+H*M;
    ts.emplace_back(d%(H*M),tos(h,m));
  }
  //sort(ALL(ts));
  //dumpc(ts);
  assert(SZ(ts)>0);
  auto res=*min_element(ALL(ts));
  cout<<res.second<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>H>>M>>S;
    solve();
  }

  return 0;
}
