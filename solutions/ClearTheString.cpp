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

// $ cp-batch ClearTheString | diff ClearTheString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ClearTheString.cpp && ./a.out

/*
 
 4/1/2019
 
 15:59-16:41 TLE on test #4
 16:55 WA on test #5
 17:05 give up
 
 4/3/2019
 
 14:50-15:30, 16:00-16:20 read editorial and got AC
 
 https://codeforces.com/blog/entry/65752
 
 a***a***a
 ^       ^
 
 It may be optimal to delete first and third `a` at the same time (Second `a` is deleted by itself)
 
 */

const int MAX_N=510+1;
string S;
int N;

//const int Inf=1e5;
int memo[MAX_N][MAX_N];

int f(int l, int r) {
  int &res=memo[l][r];
  if(res>=0) return res;
  if(r<=l) return res=0;
  assert(l<N);
  res=1+f(l+1,r);
  FOR(x,l+1,r) if(S[x]==S[l]) SMIN(res,f(l+1,x)+f(x,r));
  //  dump(l,r,x,res);
  return res;
}

void solve() {
  MINUS(memo);
  int res=f(0,N);
  cout<<res<<endl;
}

int jump[26][MAX_N];
int f_wrong(int l, int r) {
  int &res=memo[l][r];
  if(res>=0) return res;
  if(r<=l) return res=0;
  assert(l<N);
  res=1+f(l+1,r);
  int x=jump[S[l]-'a'][l];
  assert(x>l);
  if(x<r)SMIN(res,f(l+1,x)+f(x,r));
  
//  dump(l,r,x,res);
  return res;
}

void solve_wrong() {
  MINUS(memo);
  REP(c,26) jump[c][N]=N;
  for(int i=N; i>=1; --i) {
    REP(c,26) jump[c][i-1]=jump[c][i];
    if(i<N)jump[S[i]-'a'][i-1]=i;
  }
  int res=f(0,N);
//  int res=f(498,500,26);
  cout<<res<<endl;
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
  VI A=genRandSeq(500,0,26);
  N=SZ(A);
  S=string(N,'?');
  REP(i,N)S[i]='a'+A[i];
  
  cout<<N<<endl;
  cout<<S<<endl;
  
  exit(0);
  
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>S;
  solve();
  
  return 0;
}
