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

// $ cp-batch TakeYourPlaces | diff TakeYourPlaces.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TakeYourPlaces.cpp && ./a.out

/*

 8/29/2021

 7:46-8:08 AC

 https://codeforces.com/blog/entry/94384

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

const LL Inf=1e16;
LL f(VI B) {
  LL res=0;
  VV<int> difs(2);
  for(int i=N-1; i>=0; --i) {
    if(A[i]!=B[i]) difs[A[i]].push_back(i);
  }
  if(SZ(difs[0])!=SZ(difs[1])) return Inf;
  REP(i,SZ(difs[0])) res+=abs(difs[0][i]-difs[1][i]);
  return res;
}

int solve() {
  if(N==1) return 0;
  VI cnts(2);
  REP(i,N) cnts[A[i]]++;
  if(abs(cnts[0]-cnts[1])>1) return -1;

  LL res=Inf;
  if(N%2) {
    VI B(N);
    int head=cnts[1]>cnts[0]?1:0;
    REP(i,N) B[i]=(i%2==0?head:(1-head));
    SMIN(res,f(B));
  } else {
    REP(p,2) {
      VI B(N);
      REP(i,N) B[i]=(i%2?p:(1-p));
      SMIN(res,f(B));
    }
  }
  if(res>=Inf) res=-1;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i],A[i]%=2;
    cout<<solve()<<endl;
  }

  return 0;
}
