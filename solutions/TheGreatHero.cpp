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

// $ cp-batch TheGreatHero | diff TheGreatHero.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TheGreatHero.cpp && ./a.out

/*

 2/7/2021

 6:40-7:07 WA
 7:29 AC

 https://codeforces.com/blog/entry/87598

 17:50-18:05 Add solution with sorting by A[i]

 */

const int MAX_N=1e6+1;
LL A[MAX_N],B[MAX_N],AA,BB;
int N;

bool solve() {
  vector<pair<LL,int>> xs;
  REP(i,N) xs.emplace_back(A[i],i);
  sort(ALL(xs));
  REP(i,N) {
    int k=xs[i].second;
    LL cnt=(B[k]+AA-1)/AA;
    BB-=cnt*A[k];
    // dump(i,k,BB,A[k]);
    LL threshold=(i!=N-1?0:-A[k]);
    if (BB<=threshold) return false;
  }
  return true;
}

bool solve_org() {
  vector<pair<LL,int>> xs;
  REP(i,N) {
    LL cnt=(B[i]+AA-1)/AA;
    B[i]-=AA*(cnt-1);
    BB-=A[i]*(cnt-1);
  }
  if(BB<=0) return false;

  vector<pair<LL,LL>> es;
  REP(i,N) es.emplace_back(A[i],B[i]);
  sort(ALL(es));
  REP(i,N) {
    BB-=es[i].first;
    if(i<N-1&&BB<=0) return false;
  }
  return true;
  /*
  sort(ALL(xs));
  REP(i,N) {
    auto p=xs[i];
    if(BB<0) return false;
    if(i<N-1) {
      BB-=p.first;
    } else {
      LL cnt=(B[i]+AA-1)/AA;
      BB-=(cnt-1)*A[i];
      if(BB<=0) return false;
      LL b=B[i];
      b-=cnt*AA;
      return b<=0;
    }
  }
  assert(false);
  return true;*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>AA>>BB>>N;
    REP(i,N) cin>>A[i];
    REP(i,N) cin>>B[i];
    cout<<(solve()?"YES":"NO")<<endl;
  }


  return 0;
}
