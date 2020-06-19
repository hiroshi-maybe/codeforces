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

// $ cp-batch CodeforcesSubsequences | diff CodeforcesSubsequences.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CodeforcesSubsequences.cpp && ./a.out

/*

 6/18/2020

 8:03-8:18 WA
 8:27 pause
 10:02-10:14 AC

 https://codeforces.com/blog/entry/79027
 https://twitter.com/hanseilimak/status/1274079279899226112

 https://scrapbox.io/snuke/Codeforces_Global_Round_8

 */

LL K;

void solve() {
  VI cnt(10,1);
  LL cur=1;
  int i=0;
  while(cur<K) {
    LL a=cnt[i];
    cur/=a,cur*=a+1;
    cnt[i]++;
    i=(i+1)%10;
  }
  string res;
  const string a="codeforces";
  REP(i,10) res+=string(cnt[i],a[i]);
  cout<<res<<endl;
}

void solve_wrong() {
  LL aa=1,bb=K;
  for(LL a=1; a*a<=K; ++a) {
    LL b=(K+a-1)/a;
    dump(a,b,a+b,a*b);
    assert(a*b>=K);
    if(a+b<aa+bb) aa=a,bb=b;
  }
  dump(aa,bb);
  string pre(aa,'c'),suf(bb,'s');
  cout<<pre<<"odeforce"<<suf<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>K;
  solve();

  return 0;
}
