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

// $ cp-batch WrongAnswer | diff WrongAnswer.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WrongAnswer.cpp && ./a.out

/*
 
 2/24/2019
 
 9:30-9:50 give up
 
 3/2/2019
 
 17:50-18:15, 21:50-22:19 WA (incorrect output format)
 22:28 got AC though I saw some twitter comments after the contest.
 
 Making simplest example is nice first step to construct expected resutlt.
 We may expand the case to more complex cases.
 
 {-1,a} makes different result because of length of segment.
 p = a, q=2*(a-1) => q-p=a-2
 a<=1e6. Thus {-1,a} works if a<=1e6-2.
 If we want to expand this construction to satisfy 1e6-1<=K<=1e9, we can add elements with 1e6.
 
 {-1,a,1e6,..,1e6} (`x` 1e6 elements)
 p=(1e6*x+a)*(x+1), q=(1e6*x+a-1)*(x+2)
 
     q-p=(1e6-1)*x+a-2=K
 <=> x=(K+2)/(1e6-1), a=K+2-(1e6-1)*x
 
 https://codeforces.com/blog/entry/65520
 
 */

int K;

void solve() {
  LL x=(K+2)/(1e6-1);
  assert(x<=2000);
  LL a=K+2-(1e6-1)*x;
  vector<LL> res(x+2,-1);
  res[1]=a;
  REP(i,x) res[i+2]=1e6;
  
//  dumpc(res);
  LL p=(1e6*x+a)*(x+1),q=(1e6*x+a-1)*(x+2);
//  dump(p,q);
  assert(q-p==K);
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%lld ", res[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>K;
  solve();
  
  return 0;
}
