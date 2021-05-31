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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
int f[1<<20];
void ztransform_superset(int N) {
  for(int i=0; i<N; ++i) {
    for(int T=0; T<(1<<N); ++T) {
      if ((T&(1<<i))==0) f[T]+=f[T|(1<<i)];
    }
  }
}
// $ cp-batch LoveHate | diff LoveHate.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address LoveHate.cpp && ./a.out

/*

 5/30/2021

 9:08-9:50 give up

 5/31/2021

 12:30-13:50 read editorials and got AC

 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.3zu1wynhehou

 https://codeforces.com/blog/entry/91271

 https://twitter.com/kzyKT_M/status/1399045720678670338
 https://twitter.com/laycrs/status/1399048075230932992

 */

const int MAX_N=1e6+1;
string A[MAX_N];
int N,M,P;

bool ith(int mask, int i) { return (mask>>i)&1; }
void solve() {
  string res(M,'0');
  int maxbit=0;

  REP(_, 50) {
    int basei=genRandNum(0,N);
    VI ps;
    REP(i,M) if(A[basei][i]=='1') ps.push_back(i);
    int L=SZ(ps);

    auto setres=[&](int mask) {
      string ans(M,'0');
      REP(i,L) if(ith(mask,i)) ans[ps[i]]='1';
      res=ans;
    };
    dump(basei,A[basei]);

    VI cnt(1<<L);
    REP(i,N) {
      int mask=0;
      REP(j,L)if(A[i][ps[j]]=='1') mask|=(1<<j);
      dump(i,A[basei],A[i],mask);
      cnt[mask]++;
    }

    REP(m,SZ(cnt)) dump(m,cnt[m]);
    REP(mask,1<<L) f[mask]=cnt[mask];
    ztransform_superset(L);

    REP(mask,1<<L) if(f[mask]>=(N+1)/2) {
      int pcnt=__builtin_popcount(mask);
      if(pcnt>maxbit) {
        dump(mask,pcnt,f[mask]);
        maxbit=pcnt;
        setres(mask);
      }
    }
  }

  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>P;
  REP(i,N) cin>>A[i];
  solve();

  return 0;
}
