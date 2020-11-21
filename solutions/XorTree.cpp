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

// $ cp-batch XorTree | diff XorTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address XorTree.cpp && ./a.out

/*

 11/16/2020

 1:37-2:05 give up

 11/19/2020

 16:25-16:45 read editorials

 11/20/2020

 20:20-20:30 read editorials

 11/21/2020

 14:25-15:35 got AC after looking at @hitonanode's solution

 https://codeforces.com/blog/entry/82067
 https://codeforces.com/contest/1446/submission/98462434

 https://twitter.com/n_vip/status/1328021498443964416
 https://twitter.com/satanic0258/status/1328022050217156608
 https://twitter.com/laycrs/status/1328022938839236609

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

bool ith(int mask, int i) { return (mask>>i)&1; }
void solve() {
  auto dfs=[&](auto &&self, VI &as, int bi) -> int {
    if(SZ(as)<=1) return 0;
    //dump(bi,SZ(as));
    if(bi==-1) return 0;
    VI s1,s0;
    REP(i,SZ(as)) {
      if(ith(as[i],bi)) {
        s1.push_back(as[i]);
      } else {
        s0.push_back(as[i]);
      }
    }

    int x=self(self,s1,bi-1)+(SZ(s0)?(SZ(s0)-1):0);
    int y=self(self,s0,bi-1)+(SZ(s1)?(SZ(s1)-1):0);
    return min(x,y);
  };

  VI as(A,A+N);
  cout<<dfs(dfs, as, 30)<<endl;
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
