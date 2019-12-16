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

// $ cp-batch ShawarmaTent | diff ShawarmaTent.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ShawarmaTent.cpp && ./a.out

/*
 
 12/15/2019
 
 1:55-2:13 AC
 
 https://twitter.com/hanseilimak/status/1206387490682048514
 
 */

using PII=pair<LL,LL>;
const int MAX_N=1e6+1;
PII A[MAX_N];
LL sx,sy;
int N;

int cnt[4];
void solve() {
  ZERO(cnt);
  REP(i,N) {
    if(A[i].first<sx) cnt[0]++;
    if(A[i].first>sx) cnt[1]++;
    if(A[i].second<sy) cnt[2]++;
    if(A[i].second>sy) cnt[3]++;
  }
  int ri=max_element(cnt,cnt+4)-cnt;
  cout<<cnt[ri]<<endl;
  if(ri==0) {
    println("%lld %lld", sx-1,sy);
  } else if(ri==1) {
    println("%lld %lld", sx+1,sy);
  } else if(ri==2) {
    println("%lld %lld", sx,sy-1);
  } else if(ri==3) {
    println("%lld %lld", sx,sy+1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>sx>>sy;
  REP(i,N) {
    cin>>A[i].first>>A[i].second;
  }
  solve();
  
  return 0;
}
