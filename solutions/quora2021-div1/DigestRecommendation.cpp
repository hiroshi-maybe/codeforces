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

// $ cp-batch DigestRecommendation | diff DigestRecommendation.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DigestRecommendation.cpp && ./a.out

/*

 2/6/2021

 6:04-6:50 AC (100/100)

 https://codeforces.com/blog/entry/86539

 */

const int MAX_N=200+1;
int S[MAX_N];
int N,M,P,Q;

set<int> fuu[MAX_N],fus[MAX_N],fsu[MAX_N];
void solve() {
  VV<int> A(M,VI(M,0)),B(M,VI(N,0));
  REP(i,M)REP(j,M) {
    if(fuu[i].count(j)) {
      A[i][j]=3;
      continue;
    }

    bool found=false;
    FORR(s,fus[i]) if(S[s]==j) {
      found=true;
      A[i][j]=2;
    }
    if(found) continue;

    FORR(s,fus[i]) if(fsu[s].count(j)) A[i][j]=1;
  }

  REP(i,M)REP(j,N) {
    if(S[j]==i) B[i][j]=2;
    else if(fus[i].count(j)) B[i][j]=1;
  }

  REP(u,M) {
    vector<II> xs;
    REP(i,N) {
      xs.emplace_back(0,-i);
      if(S[i]==u||fus[u].count(i)) {
        xs.back().first=-1;
        continue;
      }
      REP(j,M) xs[i].first+=A[u][j]*B[j][i];
    }
    sort(ALL(xs)),reverse(ALL(xs));
    //dumpc(xs);
    cout<<-xs[0].second+1<<" "<<-xs[1].second+1<<" "<<-xs[2].second+1<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M;
  REP(i,N) cin>>S[i],S[i]--;
  cin>>P>>Q;
  REP(i,P) {
    int u,v; cin>>u>>v;
    --u,--v;
    fuu[u].emplace(v);
  }
  REP(i,Q) {
    int u,v; cin>>u>>v;
    --u,--v;
    fus[u].emplace(v),fsu[v].emplace(u);
  }
  solve();

  return 0;
}
