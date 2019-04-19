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

// $ cp-batch MinimumTriangulation | diff MinimumTriangulation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimumTriangulation.cpp && ./a.out

/*
 
 4/18/2019
 
 14:36-14:55 WA test case #3
 15:25 AC
 
 https://codeforces.com/blog/entry/66147
 https://cinnamo-coder.hatenablog.com/entry/2019/03/23/025507
 
 There is greedy solution. Make all triangles share vertex `1`.
 
 */

const int MAX_N=500+10;
int N;

const LL Inf=1e16;
LL memo[MAX_N][MAX_N];
LL f(int l, int r) {
  LL &res=memo[l][r];
  if(res>=0) return res;
  if(r-l<=1) return res=Inf;
  LL ll=l%N+1,ll2=((l+1)%N+1),rr=r%N+1;
  if(r-l==2) return res=ll*ll2*rr;
  res=ll*ll2*rr+f(l+1,r);
  dump(ll,ll2,rr,res);
  FORE(x,l+2,r-2) {
    LL xx=x%N+1;
    LL a=ll*xx*rr,b=f(l,x)+f(x,r);
    dump(l,x,r,a,b,a+b);
    SMIN(res,a+b);
  }
  dump(l,r,res);
  return res;
}
void solve() {
  MINUS(memo);
  if(N==3) {
    cout<<6<<endl;
    return;
  }
//  f(0,2);
//  f(2,5);

  LL res=1LL*2LL*N+f(2,N-1);
  FORE(j,2,N-2) SMIN(res,f(0,j)+f(j,N));
  /*
  REP(i,N) FORE(j,i+2,N) {
    SMIN(res,f(i,j)+f(j,N));
  }*/
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  solve();
  
  return 0;
}
