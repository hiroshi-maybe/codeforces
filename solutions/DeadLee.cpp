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

// $ cp-batch DeadLee | diff DeadLee.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DeadLee.cpp && ./a.out

/*

 6/23/2020

 8:33-9:05 give up

 6/24/2020

 8:45-9:45, 21:35-22:43 read editorials and submit solutions, and got AC

 https://codeforces.com/blog/entry/79235
 https://twitter.com/hanseilimak/status/1276022660619632641
 https://codeforces.com/contest/1369/submission/84812899

 https://twitter.com/laycrs/status/1275460149683970048

 */

const int MAX_N=1e6+1;
int W[MAX_N],X[MAX_N][2],viz[MAX_N];
set<int> A[MAX_N];
int N,M;

void solve() {
  REP(i,M) REP(j,2) A[X[i][j]].emplace(i);
  queue<int> Q;
  VI res;
  REP(i,N) {
    if(SZ(A[i])<=W[i]) {
      FORR(p,A[i]) Q.emplace(p);
    }
  }
  while(SZ(Q)) {
    int p=Q.front(); Q.pop();
    if(viz[p]) continue;
    viz[p]=1;
    res.push_back(p);
    REP(i,2) A[X[p][i]].erase(p);
    REP(i,2) if(SZ(A[X[p][i]])<=W[X[p][i]]) {
      FORR(pp,A[X[p][i]]) Q.emplace(pp);
    }
  }
  //dumpc(res);

  if(SZ(res)<M) {
    cout<<"DEAD"<<endl;
    return;
  }

  cout<<"ALIVE"<<endl;
  reverse(ALL(res));
  FORR(a,res) cout<<a+1<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>W[i];
  REP(i,M) REP(j,2) cin>>X[i][j],X[i][j]--;
  solve();

  return 0;
}
