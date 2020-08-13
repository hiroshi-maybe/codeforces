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

// $ cp-batch BoboniuPlaysChess | diff BoboniuPlaysChess.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BoboniuPlaysChess.cpp && ./a.out

/*

 8/12/2020

 7:47-8:18 AC

 https://twitter.com/hanseilimak/status/1293787118309793792
 https://codeforces.com/blog/entry/81355

 */

int N,M,SX,SY;

void solve() {
  VV<int> viz(N,VI(M,0));
  int i=SX-1,j=SY-1;
  vector<II> res;
  auto go=[&](int i, int j) {
    //dump(i,j);
    assert(i>=0&&j>=0);
    assert(i<N&&j<M);
    if(viz[i][j]==1) return false;
    res.emplace_back(i,j),viz[i][j]=1;
    return true;
  };
  assert(go(i,j));
  // right
  j+=1; assert(j<M);
  assert(go(i,j));
  // down
  while(i+1<N) i+=1,assert(go(i,j));
  // up
  i=SX-2; assert(go(i,j));
  while(i-1>=0) i-=1,assert(go(i,j));
  // right
  j=(j+1)%M;
  go(i,j);
  int dir=1;
  while(SZ(res)<N*M) {
    i+=dir;
    if(i<0) i=0,j+=1,dir=1;
    else if(i>=N) i=N-1,j+=1,dir=-1;
    j=(j+M)%M;
    go(i,j);
  }
  //dumpc(res);
  set<II> S(ALL(res));
  //dump(SZ(S));
  assert(SZ(S)==N*M);
  FORR(p,res) cout<<p.first+1<<" "<<p.second+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>SX>>SY;
  solve();

  return 0;
}
