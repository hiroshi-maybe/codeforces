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

// $ cp-batch NastyaIsBuyingLunch | diff NastyaIsBuyingLunch.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NastyaIsBuyingLunch.cpp && ./a.out

/*
 
 4/4/2019
 
 15:40-16:43 WA on test #4
 16:45 give up
 17:27 Read editorial and got AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/03/12/033934
 Almost same as my idea. However break is needed to upper-bound runtime by O(M).
 https://codeforces.com/blog/entry/65905
 https://codeforces.com/blog/entry/65905?#comment-499043
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
SETI X[MAX_N];
int N,M;

void solve_org() {
  VI B; B.push_back(A[N-1]);
  int res=0;
  for(int i=N-2; i>=0; --i) {
//    if(i+1<SZ(B)) break;
    int a=A[i];
    bool ok=true;
    FORR(b,B) if(X[a].count(b)==0) {
      ok=false;
      break;
    }
    if(!ok) B.push_back(a);
    else ++res;
  }
  cout<<res<<endl;
}

// In this solution, runtime is clearly O(N+M) time
void solve() {
  SETI P; P.emplace(A[N-1]);
  int res=0;
  for(int i=N-2; i>=0; --i) {
    int a=A[i],cnt=0;
    FORR(y,X[a]) cnt+=P.count(y);
    if(cnt<SZ(P)) P.emplace(a);
    else ++res;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  REP(i,M) {
    int u,v; cin>>u>>v;
    X[u].emplace(v);
  }
  solve();
  
  return 0;
}
