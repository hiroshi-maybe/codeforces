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

#define UNIQUE(A) sort((A).begin(),(A).end()),(A).erase(std::unique((A).begin(), (A).end()), (A).end());
// $ cp-batch TokitsukazeCSLAndStoneGame | diff TokitsukazeCSLAndStoneGame.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TokitsukazeCSLAndStoneGame.cpp && ./a.out

/*
 
 7/12/2019
 
 8:48-9:31 4WA
 21:20-22:00 read editorials
 
 7/13/2019
 
 9:10-10:00 read editorials
 
 One necessary condition is that player should take `x` if cnt(x)>1.
 If such multiple `x` exist, it's LOSE state.
 
 By some of case work, we reach a state of {0,1,..,N-1}.
 Then this is LOSE state, too.
 
 https://codeforces.com/blog/entry/68314
 https://twitter.com/beet_aizu/status/1149718950478897152
 https://twitter.com/satanic0258/status/1149721596564627456
 https://twitter.com/hanseilimak/status/1149924002611118080
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

bool solve() {
  int cnt0=count(A,A+N,0);
  if(cnt0==N) return false;
  if(cnt0>1) return false;
  map<LL,int> cnt;
  REP(i,N) cnt[A[i]]++;
  FORR(kvp,cnt) if(kvp.second>2) return false;
  
  int cnt2=0,cnt3=0;
  set<int> S2;
  bool ok=true;
  FORR(kvp,cnt) {
    LL a=kvp.first;
    if(a>0)ok&=(cnt.count(a-1)>0);
    if(kvp.second>2) cnt3++;
    if(kvp.second==2) {
      cnt2++;
      S2.emplace(kvp.first);
    }
  }
  if(ok) return false;
  if(cnt3>=1) return false;
  if(cnt2>1) return false;
  if(cnt2==1) {
    int a=*S2.begin();
    if(cnt.count(a-1)) return false;
  }
  LL sum=0;
  REP(i,N) sum+=A[i]-i;
  return sum%2LL!=0;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<(solve()?"sjfnb":"cslnb")<<endl;
  
  return 0;
}
