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

// $ cp-batch XeniaAndColorfulGems | diff XeniaAndColorfulGems.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XeniaAndColorfulGems.cpp && ./a.out

/*
 
 4/15/2020
 
 8:31-8:46 AC
 
 https://codeforces.com/blog/entry/76099
 
 */

const int MAX_N=1e6+1;
LL A[3][MAX_N];
int ns[3];

LL Inf=9223372036854775807;
void solve() {
  REP(i,3) sort(A[i],A[i]+ns[i]);
  LL res=Inf;
  REP(i,3)REP(j,ns[i]) {
    LL a=A[i][j];
    vector<LL> as={a};
    REP(ii,3)if(ii!=i) {
      int p=lower_bound(A[ii],A[ii]+ns[ii],a)-A[ii];
      LL b=-Inf;
      if(p<ns[ii]) b=A[ii][p];
      if(p-1>=0&&abs(b-a)>abs(A[ii][p-1]-a)) b=A[ii][p-1];
      assert(b!=-Inf);
      as.push_back(b);
    }
    LL ans=0;
    assert(SZ(as)==3);
    REP(j,3)REP(i,j) ans+=abs(as[j]-as[i])*abs(as[j]-as[i]);
    SMIN(res,ans);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    REP(i,3)cin>>ns[i];
    REP(i,3)REP(j,ns[i]) cin>>A[i][j];
    solve();
  }
  
  return 0;
}
