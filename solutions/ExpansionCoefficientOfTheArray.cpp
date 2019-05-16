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

// $ cp-batch ExpansionCoefficientOfTheArray | diff ExpansionCoefficientOfTheArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ExpansionCoefficientOfTheArray.cpp && ./a.out

/*
 
 5/12/2019
 
 7:53-8:25 AC
 
 https://codeforces.com/blog/entry/66993
 
 I solved by binary search though, hmmm formula transformation in the editorial is pretty tough.
 If `k` is maximal which satisfies f(x) for all `x`, `k` is upper-bounded minimum value of f(x).
 Also original formula f(x) = min(A[i],A[j])/abs(i-j).
 Which can be decomposed to min(A[i]/abs(i-j),A[j]/abs(i-j)).
 j s.t. A[i]/abs(i-j) is minimized is clearly N-i or i.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  LL res=1e10;
  REP(i,N) SMIN(res,A[i]/max(i,N-1-i));
  cout<<res<<endl;
}

vector<II> X;
VI Y;
bool ok(LL K) {
  REP(i,N-1) {
    LL a=Y[i],b=X[i].first;
//    dump(i,a,K,b,a*K>b);
    if(a*K>b) return false;
  }
  return true;
}
void solve_org() {
  X=vector<II>(N);
  REP(i,N) X[i]={A[i],i};
  sort(ALL(X));
  Y=VI(N);
  set<int> S; REP(i,N)S.emplace(i);
  REP(j,N-1) {
    int a,i; tie(a,i)=X[j];
    S.erase(i);
    Y[j]=max(abs(*S.begin()-i),abs(*(S.rbegin())-i));
//    dump(j,a,Y[j]);
  }
  LL good=0,bad=1e12;
  while(abs(good-bad)>1) {
    LL m=(good+bad)/2;
    (ok(m)?good:bad)=m;
//    dump(m,good,bad);
  }
//  dump(ok(1),ok(2),ok(3));
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
