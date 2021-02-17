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

// $ cp-batch MinimumTies | diff MinimumTies.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MinimumTies.cpp && ./a.out

/*

 2/15/2021

 7:39-8:17　AC

 https://codeforces.com/blog/entry/87873
 https://twitter.com/hanseilimak/status/1362088112675954688
 https://twitter.com/kiri8128/status/1361353767707316226
 https://twitter.com/laycrs/status/1361353437078646791
 https://twitter.com/kzyKT_M/status/1361353560647032836

 */

int N;

void solve() {
  VV<int> res(N,VI(N,0));
  VI wl={3,0};
  if(N%2) {
    REP(i,N) {
      VI cnt(4,0);
      REP(j,i) cnt[res[i][j]]++;
      int k=(cnt[3]>cnt[0])?1:0;
      FOR(j,i+1,N) {
        res[i][j]=wl[k];
        k^=1;
        res[j][i]=wl[k];
      }
    }
  } else {
    REP(i,N) {
      VI cnt(4,0);
      REP(j,i) cnt[res[i][j]]++;
      int k=(cnt[3]>cnt[0])?1:0;
      FOR(j,i+1,N) {
        if(j==N-1-i) {
          res[i][j]=1,res[j][i]=1;
        } else {
          res[i][j]=wl[k];
          k^=1;
          res[j][i]=wl[k];
        }
      }
    }
  }

  //REP(i,N) dumpc(res[i]);

  set<int> S;
  REP(i,N) {
    int sum=accumulate(res[i].begin(),res[i].end(),0);
    S.emplace(sum);
  }
  assert(SZ(S)==1);

  const int Inf=1e6;
  VI score={-1,0,Inf,1};
  REP(i,N) FOR(j,i+1,N) cout<<score[res[i][j]]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  /*FOR(i,2,100) {
    N=i;
    solve();
  }*/

  int t; cin>>t;
  while(t--) {
    cin>>N;
    solve();
  }

  return 0;
}
