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

// $ cp-batch PavelAndTriangles | diff PavelAndTriangles.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PavelAndTriangles.cpp && ./a.out

/*
 
 4/7/2019
 
 16:27-17:01 WA on test #5
 18:02 WA on test #8
 18:15 give up
 
 Greedy from larger value didn't pass system test
 
 4/10/2019
 
 19:10-20:10, 21:40-22:06 Read editorial, found a bug in my original solution and got AC
 
 @tourist's solution is greedy from larger
 https://codeforces.com/contest/1119/submission/52388780
 
 https://codeforces.com/blog/entry/66411
  1. maxmize pairs (i,j,j)
  2. make (j,j,j)
  3. adjust extra items
 http://drken1215.hatenablog.com/entry/2019/04/07/141800
 https://cinnamo-coder.hatenablog.com/entry/2019/04/07/003917
 
 There are two greedy choices
 1. make (a,a,a) as many as possible
 2. make (a,b,b) as many as possible
 
 However #1 is not optimal. Suppose we have ax4,bx4,cx4 (a<b<c).
 If we make (a,a,a) first, Only three tuples {(a,a,a),(b,b,b),(c,c,c)} are made.
 However we can make four tuples {(a,b,b),(a,b,b),(a,c,c),(a,c,c)}.
 Thus we make (a,b,b) (a<b) as many as possible.
 
 If more than two `a`s remain, we can make (a,a,a) too.
 1) three tuples (a,b,b),(a,c,c),(a,d,d) can be made
  (a,a,a),(b,c,c),(b,d,d) is not worse
 2) two tuples (a,b,b),(a,c,c) can be made (one `a` is discarded)
  (a,a,a),(b,c,c) is not worse
 3) one tuple (a,b,b) can be made (two `a`s are discarded)
  (a,a,a) is not worse
 Thus we can greedily make (a,a,a) if it remains after making (x,a,a) (x<a)
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL solve() {
  LL res=0,extra=0;
  REP(i,N) {
    LL a=A[i];
    LL x=min(extra,a/2);
    res+=x,a-=2LL*x,extra-=x;
    res+=a/3;
    extra+=a%3;
//    dump(i,a,x,res,extra);
  }
  return res;
}

LL cum[MAX_N];
LL solve_org() {
  LL res=0,need=0;
  reverse(A,A+N);
  REP(i,N) cum[i+1]=cum[i]+A[i];
//  dumpC(A,A+N);
//  dumpC(cum,cum+N+1);

  REP(i,N) {
    LL a=A[i];
    LL rem=cum[N]-cum[i+1];
    LL x=min(a/2,(rem+a-need)/3);
    LL y=max(0LL,3LL*x-a);
    
    // Even if pair cannot be made, # of needed should be reduced.
    if(x<=0&&need>0) need-=min(need,a);
    
    if(x<0) continue;
    res+=x,need+=y;
//    dump(i,x,y,res,need);
  }
  return res;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=5;
  VI X=genRandSeq(N,1,5);
  REP(i,N)A[i]=X[i];
  LL a=solve_org(); reverse(A,A+N);
  LL b=solve();
  if(a!=b) {
    dump(a,b); dumpc(X);
  }
  assert(a==b);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
