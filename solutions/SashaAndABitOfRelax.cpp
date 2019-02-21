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

// $ cp-batch SashaAndABitOfRelax | diff SashaAndABitOfRelax.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SashaAndABitOfRelax.cpp && ./a.out

/*
 
 2/16/2019
 
 8:58-9:30, 10:50-11:05 give up
 
 2/21/2019
 
 14:20-15:15 read editorials and got AC
 
 https://codeforces.com/blog/entry/65295
 https://twitter.com/hogeover30/status/1096850363221590016
 
 It's obvious that necessary condition of A[l..mid]=A[mid+1..r] is A[l..r]=0
 
 A[l..mid] = A[mid+1..r] => A[l..r] = 0
 
 It's actually sufficient because ∀i, l<=i<=r, A[l..i] = A[i+1..r] holds.
 
 By prefix XOR, we can find # of subsegments s.t. A[l..r]=0 for any `r` in O(1) time.
 (A[0..r]=A[0..l-1] <=> A[l..r] = 0)
 We should check # of `l` whose parity is equal to `r` to satisfy even length condition.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int cnt[1<<20][2];
void solve() {
  LL res=0;
  int cur=0;
  cnt[cur][0]=1;
  FORE(i,1,N) {
    cur^=A[i-1];
    res+=cnt[cur][i%2];
    cnt[cur][i%2]++;
//    dump(i,cur);
  }
  cout<<res<<endl;
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
