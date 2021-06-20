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

// $ cp-batch ChallengingCliffs | diff ChallengingCliffs.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ChallengingCliffs.cpp && ./a.out

/*

 6/18/2021

 8:25-9:05 AC

 https://codeforces.com/blog/entry/91381
 https://twitter.com/torus711/status/1405928843077046274
 https://twitter.com/kiri8128/status/1405927315700293633
 https://twitter.com/kzyKT_M/status/1405927478233767941
 https://twitter.com/laycrs/status/1405927855930834944

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  sort(A,A+N);
  map<LL,VI> xs;
  REP(i,N-1) xs[A[i+1]-A[i]].emplace_back(i);
  int head=-1;
  FORR(i, xs.begin()->second) {
    if(i==0||i==N-2) head=i;
    else if(head==-1) head=i;
  }
  vector<LL> low={A[head]},hi;
  REP(i,N) if(i!=head&&i!=head+1) {
    (A[i]>=A[head]?low:hi).push_back(A[i]);
  }
  hi.push_back(A[head+1]);
  assert(SZ(low)+SZ(hi)==N);
  REP(i,SZ(low)) cout<<low[i]<<" ";
  REP(i,SZ(hi)) cout<<hi[i]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
