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

// $ cp-batch EhabTheXorcist | diff EhabTheXorcist.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabTheXorcist.cpp && ./a.out

/*
 
 3/14/2020
 
 8:42-10:04 WA
 
 3/15/2020
 
 11:25-12:30, 13:00-14:24 read editorials and got AC
 
 https://twitter.com/laycrs/status/1238866349725601792
 https://twitter.com/kzyKT_M/status/1238866670887686144
 https://codeforces.com/blog/entry/74235
 https://twitter.com/hanseilimak/status/1239268942524252160
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.vfrqt0s3y95c
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.ty328k8rloxm
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.t6h8dfb47bq0
 
 */

LL U,V;

void nope() {
  println("-1");
  exit(0);
}

void solve() {
  if((U&1)!=(V&1)) nope();
  if(U==V) {
    if(U==0) {
      println("0");
    } else {
      println("1");
      println("%lld", U);
    }
    return;
  }
  if(U>V) nope();
  LL x=(V-U)/2;
  vector<LL> res;
  if((x&U)!=0LL) {
    res={U,x,x};
  } else {
    res={x+U,x};
  }
  
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%lld ", res[i]);
  println("");
}

void solve_wrong() {
  vector<LL> res={0,0,0};
  int cc=0;
  for(int i=61; i>=0; --i) {
    int a=(U>>i)&1,b=(V>>i)&1;
    dump(i,a,b,cc);
    if(a==0&&b==0) {
      if(cc==1) res[0]|=1LL<<i,res[1]|=1LL<<i;
      cc=0;
    }
    if(a==0&&b==1) {
      if(cc==1) res[0]|=1LL<<i,res[1]|=1LL<<i;
      cc=1;
    }
    if(a==1&&b==0){
      res[1]|=1LL<<i;
      if(cc!=1) nope();
      cc=1;
    }
    if(a==1&&b==1) {
      if(cc==1) res[0]|=1LL<<i,res[1]|=1LL<<i,res[2]|=1LL<<i;
      else res[0]|=1LL<<i;
      cc=0;
    }
  }
  if(cc!=0) nope();
  while(SZ(res)&&res.back()==0) res.pop_back();
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%lld ", res[i]);
  println("");
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}

void test() {
  V=genRandNum(1,32),U=genRandNum(0,V);
  U|=1,V|=1;
  dump(U,V);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>U>>V;
  solve();
  
  return 0;
}
