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

// $ cp-batch TokitsukazeAndDiscardItems | diff TokitsukazeAndDiscardItems.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TokitsukazeAndDiscardItems.cpp && ./a.out

/*
 
 7/12/2019
 
 8:04-8:30 WA
 8:47 AC
 
 Checking if A[i] is same page
  - https://codeforces.com/contest/1190/submission/56891978 by @kmjp
 
 Page of A[i] is calculated by (A[i]-rem)/K.
 Thus we can proceed i+1 as long as (A[i]-rem)/K=(A[i+1]-rem)/K
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int M;
LL N,K;

LL page(int i, LL rem) {
  return (A[i]-rem)/K;
}
void solve() {
  LL rem=0;
  LL res=0;
  int i=0;
  while(i<M) {
    LL cnt=1;
    LL p=page(i,rem);
    while(i+cnt<M&&page(i+cnt,rem)==p) ++cnt;
    ++res,rem+=cnt,i+=cnt;
//    dump(i,p,cnt,rem);i
  }
  cout<<res<<endl;
}

void solve_org() {
  sort(A,A+M);
  LL off=0;
  LL res=0;
  int i=0;
  while(true) {
    LL cur=(A[i]-off)%K;
    LL hb=A[i]+(K-cur);
    int cnt=0;
    while(i<M&&A[i]<hb) ++cnt,++i;
    //      dump(A[i-cnt],off,hb,cnt);
    if(cnt>0) ++res,off+=cnt;
    else break;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  REP(i,M) {
    cin>>A[i];
    --A[i];
  }
  solve();
  
  return 0;
}
