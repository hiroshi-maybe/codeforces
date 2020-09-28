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

// $ cp-batch WoArrays | diff WoArrays.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WoArrays.cpp && ./a.out

/*

 9/27/2020

 8:14-9:02 WA
 9:47-9:56 AC

 https://twitter.com/hanseilimak/status/1310453180635832320
 https://codeforces.com/blog/entry/83036

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N,T;

void solve() {
  map<int,VI> ps;
  REP(i,N) ps[A[i]].push_back(i);

  VI res(N,-1);
  FORR(kvp, ps) {
    int a=kvp.first;
    if(SZ(kvp.second)&&res[kvp.second.front()]!=-1) continue;

    if(a+a==T) {
      int M=SZ(kvp.second);
      REP(i,M) {
        res[kvp.second[i]]=i>=M/2;
      }
    } else if(ps.count(T-a)) {
      FORR(i,kvp.second) res[i]=0;
      FORR(i,ps[T-a]) res[i]=1;
    } else {
      FORR(i,kvp.second) res[i]=0;
    }
  }

  REP(i,N) cout<<res[i]<<" ";
  cout<<endl;
}

void solve_wrong() {
  vector<II> as(N);
  REP(i,N) as[i]={A[i],i};
  sort(ALL(as));
  VI res(N,0);
  int l=0,r=N-1;
  while(l<r) {
    if(as[l].first+as[r].first<T) {
      ++l;
    } else if(as[l].first+as[r].first>T) {
      res[as[r--].second]=1;
    } else {
      //dump(l,r);
      res[as[r].second]=1;
      --r,++l;
    }
  }
  if(N>1&&N%2==1&&as[l].first+as[l-1].first==T&&as[l].first!=as[l-1].first) {
    res[as[l].second]=1;
  }
  REP(i,N) cout<<res[i]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>T;
    REP(i,N) cin>>A[i];
    solve();
  }

  return 0;
}
