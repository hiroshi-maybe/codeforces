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

// $ cp-batch SaveTheNature | diff SaveTheNature.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SaveTheNature.cpp && ./a.out

/*
 
 10/6/2019
 
 8:18-8:47 AC
 
 https://codeforces.com/blog/entry/70358
 
 */

const int MAX_N=1e6+1;
LL P[MAX_N],K;
int Q,N,X,Y,A,B;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }
LL LCM(LL a, LL b) { return a/gcd(a,b)*b; }
bool ok(int M) {
  LL lcm=LCM(A,B);
  LL sum=0;
  int a=M/lcm;
  int ub=min(a,N+1);
  REP(i,ub) sum+=P[i]/100*(X+Y);
  int b=M/A-a;
  int ub2=min(ub+b,N+1);
  FOR(i,ub,ub2) sum+=P[i]/100*X;
  int c=M/B-a;
  int ub3=min(ub2+c,N+1);
  FOR(i,ub2,ub3) sum+=P[i]/100*Y;
  return sum>=K;
}

void solve() {
  if(X<Y) swap(A,B),swap(X,Y);
  sort(P,P+N); reverse(P,P+N);
  int good=N+1,bad=0;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    bool res=ok(mid);
    (res?good:bad)=mid;
  }
  int res=-1;
  if(good<=N) res=good;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>Q;
  REP(i,Q) {
    cin>>N;
    REP(i,N)cin>>P[i];
    cin>>X>>A>>Y>>B>>K;
    solve();
  }
  
  return 0;
}
