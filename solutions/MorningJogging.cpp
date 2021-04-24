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

// $ cp-batch MorningJogging | diff MorningJogging.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MorningJogging.cpp && ./a.out

/*

 4/23/2021

 7:40-8:03 AC

 https://codeforces.com/blog/entry/89968

 */

const int MAX_N=100+1;
LL B[MAX_N][MAX_N];
int N,M;

void solve() {
  vector<pair<LL,int>> xs;
  REP(i,N)REP(j,M) xs.emplace_back(B[i][j],i);
  sort(ALL(xs));
  vector<deque<LL>> Q(N);
  REP(i,N) {
    sort(B[i],B[i]+M);
    REP(j,M) Q[i].emplace_back(B[i][j]);
  }

  VV<LL> res(N);
  REP(i,M) {
    auto p=xs[i];
    int pos=p.second;
    LL val=p.first;

    res[pos].push_back(val);
    assert(Q[pos].front()==val);
    Q[pos].pop_front();
    //dump(i,pos,val);
    REP(j,N) if(j!=pos) {
      res[j].push_back(Q[j].back());
      //dump(i,j,Q[j].back());
      Q[j].pop_back();
    }
  }

  REP(i,N) {
    assert(SZ(res[i])==M);
    REP(j,M) cout<<res[i][j]<<" ";
    cout<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N)REP(j,M) cin>>B[i][j];
    solve();
  }

  return 0;
}
