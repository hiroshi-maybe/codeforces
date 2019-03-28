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

#define UNIQUE(A) (A).erase(std::unique((A).begin(), (A).end()), (A).end());

// $ cp-batch FloodFill | diff FloodFill.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FloodFill.cpp && ./a.out

/*
 
 3/27/2019
 
 15:53-16:31 WA on test case #6
 16:56 give up
 
 17:10-17:30 debug
 
 3/28/2019
 
 11:40-12:10 give up
 12:10-13:10 read editorials and got AC
 14:10-17:15 add LCS solution
 
 https://codeforces.com/blog/entry/65136
 
 Editorial solution is showing two points
  1. it's necessary to remember which side of edge color is filled in the interval
  2. choosing edge colors is optimal
 
 OMG. I found out that I misunderstood the problem.
 I thought starting square can be chosen in very turn 😞
 
 # dp1 - remember edge color
 
 Now above two points make sense. Starting square never changes. We could not expand interval without painting by outer colors.
 
 Below SRM problem is close. In that problem, there are only two colors. Chosen color is deterministic.
 http://kmjp.hatenablog.jp/entry/2018/03/31/0900
 
 # dp2 - subtract by maximum palidrome subsequence
 
 Compress a string because size of connected component doesn't matter.
 There are two cases to expand interval
 
 1) merge with one element in a turn
 axb => aab => bbb
 2) merge with two elements in a turn
 axa => aaa
 
 Case #2 saves one turn. Thus we want to maximize occurrence of case #2.
 It is palidrome subsequence which can be solved by LCS problem of A and rev(A).
 
 */

const int MAX_N=5e3+10;
LL A[MAX_N];
int N;

const int Inf=1e5;
int nex[MAX_N],pos[MAX_N];
int memo[MAX_N][MAX_N][2];
int f(int l, int r, int col) {
  int &res=memo[l][r][col];
  if(res>=0) return res;
  if(r-l<=1) return 0;
  res=Inf;
  if(col==0) {
    if(l<N-1) res=f(l+1,r,0)+(A[l]!=A[l+1]);
    SMIN(res,f(l+1,r,1)+(A[l]!=A[r-1]));
  } else {
    if(r>0) res=f(l,r-1,1)+(A[r-1]!=A[r-2]);
    SMIN(res,f(l,r-1,0)+(A[l]!=A[r-1]));
  }
  return res;
}

int f_wrong(int l, int r) {
  int &res=memo[l][r][0];
  if(res>=0) return res;
  if(r-l<=1) return 0;
  res=Inf;
  if(l<N-1&&A[l]==A[l+1]) res=f_wrong(l+1,r);
  //  SMIN(res,1+f(l,r-1));
  SMIN(res,1+f_wrong(l+1,r));
  int x=nex[l];
  if(x!=-1) {
    SMIN(res,1+f_wrong(l+1,x)+f_wrong(x,r));
    //    dump(l,r,x,res,r-l,a,b);
  }
  //  dump(l,r,x,res,r-l);
  //  assert(res<=r-l);
  return res;
}

// remember selected edge color in memoization
int solve_dp1() {
  MINUS(pos);
  MINUS(memo);
  return min(f(0,N,0),f(0,N,1));
}

VI X,Y;
int f(int l, int r) {
  int M=SZ(X);
  int &res=memo[l][r][0];
  if(res>=0) return res;
  res=0;
  if(l<=0&&r>=M-1) return res=0;
  if(l>0&&r<M-1&&X[l-1]==X[r+1]) SMAX(res,1+f(l-1,r+1));
  if(l>0) SMAX(res,f(l-1,r));
  if(r<M-1) SMAX(res,f(l,r+1));
  return res;
}
int solve() {
  X=VI(N); REP(i,N) X[i]=A[i];
  UNIQUE(X);
//  dumpC(A,A+N);
//  Y=X; reverse(ALL(Y));
  int x=0;
  int M=SZ(X);
  MINUS(memo);
  REP(i,M) {
    int y=f(i,i);
    SMAX(x,y);
  }
  return M-1-x;
}

int solve_wrong() {
  MINUS(pos);
  MINUS(nex);
  for(int i=N-1; i>=0; --i) {
    int a=A[i];
    nex[i]=pos[a];
    pos[a]=i;
  }
  MINUS(memo);
  return f_wrong(0,N);
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
  while(true) {
    N=5;
    VI as=genRandSeq(N,1,6);
    REP(i,N)A[i]=as[i];
    int x=solve(),y=solve_wrong();
    if(x!=y) {
      dumpc(as);
      dump(x,y);
    }
    assert(x==y);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
  
  return 0;
}
