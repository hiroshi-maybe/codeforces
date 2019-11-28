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

// $ cp-batch InfiniteFence | diff InfiniteFence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address InfiniteFence.cpp && ./a.out

/*
 
 11/27/2019
 
 6:19-6:42 WA
 7:33 WA
 7:50 give up
 
 22:25-22:27 AC by fixing overflow
 
 https://twitter.com/hanseilimak/status/1199940653804732416
 https://codeforces.com/blog/entry/71805
 
 */

int R,B,K;
tuple<int,int,int> extended_euclid(int a, int b) {
  if (b==0) return make_tuple(a, 1, 0);
  
  int d2,x2,y2;
  tie(d2,x2,y2) = extended_euclid(b, a%b);
  return make_tuple(d2,y2,x2-(a/b)*y2);
}
LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL lcm(LL a, LL b) { return a/gcd(a,b)*b; }

bool solve() {
  LL g=gcd(R,B);
  LL r=R/g,b=B/g;
  if(r>b) swap(r,b);
  return !((K-1)*r+1<b);
}

bool solve_org() {
  dump(R,B,K);
  LL g=gcd(R,B);
  LL r=R/g,b=B/g;
  dump(r,b,g);
  if(r>b) swap(r,b);
  auto ecd=extended_euclid((int)r,(int)b);
  int d,x,y; tie(d,x,y)=ecd;
  LL aa,bb;
  if(y<0) {
    aa=(LL)b*abs(y),bb=(LL)b*(abs(y)+1);
  } else if(x<0) {
    bb=1+((LL)abs(x)*r)+lcm(r,b),aa=bb-b;
  } else {
    dump(d,x,y);
    assert(x==0||y==0);
    return b-r<K;
  }
  LL cnt=bb/r-aa/r;
  dump(r,b,d,x,y,cnt);
  assert(d==1);

  return cnt<K;
  //return b/r<K;
}
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
void test() {
  int maxn=100;
  R=genRandNum(1,maxn),B=genRandNum(1,maxn),K=genRandNum(2,10);
//  R=96,B=64,K=4;
  int M=maxn*maxn+1;
  VI X(M,0);
  for(int i=0;i*R<M; ++i) X[i*R]+=1;
  for(int i=0;i*B<M; ++i) X[i*B]+=2;
  vector<II> rl;
  REP(i,M)if(X[i]>0) {
    if(rl.empty()||rl.back().second!=X[i]) rl.emplace_back(0,X[i]);
    rl.back().first+=1;
  }
  bool res=true;
  REP(i,SZ(rl)) if(rl[i].second!=3&&rl[i].first>=K) res=false;
  bool act=solve();
  if(act!=res) {
    dump(R,B,K,act,res);
    dumpc(rl);
  }
  assert(act==res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

//  while(true) test();
  
  int T; cin>>T;
  REP(i,T) {
    cin>>R>>B>>K;
    cout<<(solve()?"OBEY":"REBEL")<<endl;
  }
  
  return 0;
}
