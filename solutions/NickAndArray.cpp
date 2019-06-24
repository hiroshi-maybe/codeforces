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

// $ cp-batch NickAndArray | diff NickAndArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NickAndArray.cpp && ./a.out

/*
 
 6/21/2019
 
 10:09-10:39 failed system test
 14:15-14:20 bug fix. very annoying problem.
 
 https://codeforces.com/blog/entry/67891
 
 Before doing case work of special numbers {0,1}, maximize absolute value first.
 That handles annoying `0` case, too.
 Maximize absolute values first by converting A[i]>=0.
 We are sure that there is no `0` and all the values are less than 0.
 If N is odd, convert a value with the largest absolute value.
 Anyway I hate this problem.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

LL f(LL a) { return -a-1; }
void done() {
  REP(i,N) printf("%lld ", A[i]);
  println("");
  exit(0);
}

void solve() {
  REP(i,N) if(A[i]>=0) A[i]=f(A[i]);
  if(N%2==1) {
    int p=0;
    REP(i,N) if(abs(A[i])>abs(A[p])) p=i;
    A[p]=f(A[p]);
  }
  done();
}

int viz[MAX_N];
void solve_org() {
  ZERO(viz);
  int cnt0=0,cntm1=0;
  REP(i,N){
    cnt0+=A[i]==0;
    cntm1+=A[i]==-1;
  }
  if(cnt0==N) {
    if(cnt0%2==0) REP(i,N)A[i]=-1;
    done();
  }
  if(cnt0>0&&cnt0+cntm1==N) {
    if((cnt0%2)==(cntm1%2)) {
      REP(i,N)if(A[i]==0) A[i]=-1;
    }
    done();
  }
  REP(i,N) if(A[i]>=0) A[i]=f(A[i]),viz[i]=1;
  int cntneg=0;
  REP(i,N) cntneg+=A[i]<0;
  if(cntneg%2==1) {
    int maxi=0;
    REP(i,N) if(abs(A[i])>abs(A[maxi])) maxi=i;
    A[maxi]=abs(A[maxi])-1;
  }
  done();
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
