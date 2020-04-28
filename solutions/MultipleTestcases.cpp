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

// $ cp-batch MultipleTestcases | diff MultipleTestcases.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MultipleTestcases.cpp && ./a.out

/*
 
 4/26/2020
 
 8:26-9:15 AC
 
 https://codeforces.com/blog/entry/76633
 
 */

const int MAX_N=1e6+1;
int M[MAX_N],C[MAX_N];
int N,K;

VV<int> ans;
bool ok(int X) {
  VV<int> res(X);
  REP(i,N) res[i%X].push_back(M[i]);
  REP(i,X) {
    VI A=res[i];
    reverse(ALL(A));
//    dump(X,i);
//    dumpc(A);
    while(SZ(A)) {
      int cnt=SZ(A);
//      dump(cnt,A.back(),C[A.back()]);
      if(cnt>C[A.back()]) return false;
      A.pop_back();
    }
  }
  ans=res;
  return true;
}

void solve() {
  sort(M,M+N);
  int good=N,bad=0;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    bool res=ok(mid);
    (res?good:bad)=mid;
  }
  ok(good);
  cout<<SZ(ans)<<endl;
  REP(i,SZ(ans)) {
    cout<<SZ(ans[i])<<" ";
    REP(j,SZ(ans[i])) cout<<ans[i][j]<<" ";
    cout<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) cin>>M[i];
  REP(i,K) cin>>C[i+1];
  solve();
  
  return 0;
}
