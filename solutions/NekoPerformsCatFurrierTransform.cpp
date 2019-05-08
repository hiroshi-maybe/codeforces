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

// $ cp-batch NekoPerformsCatFurrierTransform | diff NekoPerformsCatFurrierTransform.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NekoPerformsCatFurrierTransform.cpp && ./a.out

/*
 
 4/24/2019
 
 7:39-8:07 AC
 
 https://codeforces.com/blog/entry/66696
 https://cinnamo-coder.hatenablog.com/entry/2019/04/25/031403

 Keep transfering left most `0` with operation A.
 It's possible to show that left-most `0` never moves left.
 
 */

//const int MAX_N=1e6+1;
int X;

void solve() {
  int n=0;
  REP(i,20) if((X>>i)&1) n=i;
  dump(n);
  int cnt=0;
  VI res;
  int x=X;
  int full=(1<<(n+1))-1;
  for(int i=n-1; i>=0; --i) if(!((x>>i)&1)) {
    res.push_back(i+1),++cnt;
    x^=(1<<(i+1))-1;
    if(x==full) break;
    x+=1,++cnt;
  }
  dump(x,full);
  assert(x==full);
  cout<<cnt<<endl;
  REP(i,SZ(res))cout<<res[i]<<" \n"[i==SZ(res)-1];
}

void test() {
  FORE(x,1,1000000) {
    X=x;
//    dump(X);
    solve();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>X;
  solve();
  
  return 0;
}
