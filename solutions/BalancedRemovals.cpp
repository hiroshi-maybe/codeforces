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

// $ cp-batch BalancedRemovals | diff BalancedRemovals.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BalancedRemovals.cpp && ./a.out

/*

 8/15/2020

 16:34-17:31 AC

 https://codeforces.com/blog/entry/70620

 */

const int MAX_N=1e5+1;
int X[MAX_N],Y[MAX_N],Z[MAX_N];
int N;

void solve() {
  vector<II> res;
  map<int,vector<III>> ps;
  REP(i,N) ps[X[i]].emplace_back(Y[i],Z[i],i);

  int p=-1;
  FORR(kvp, ps) {
    map<int,vector<II>> ps2;
    FORR(t, kvp.second) {
      int y,z,i; tie(y,z,i)=t;
      ps2[y].emplace_back(z,i);
    }
    int pp=-1;
    FORR(kvp2, ps2) {
      vector<II> ps3=kvp2.second;
      sort(ALL(ps3));
      for(int i=0; i<SZ(ps3)-1; i+=2) {
        res.emplace_back(ps3.at(i).second,ps3.at(i+1).second);
      }
      if(SZ(ps3)%2==1) {
        //dump(kvp.first,kvp2.first,SZ(ps3));
        if(pp!=-1) res.emplace_back(pp,ps3.back().second),pp=-1;
        else pp=ps3.back().second;
      }
    }
    if(pp!=-1) {
      if(p!=-1) res.emplace_back(p,pp),p=-1;
      else p=pp;
    }
  }

  assert(SZ(res)==N/2);
  REP(i,N/2) cout<<res[i].first+1<<" "<<res[i].second+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i]>>Z[i];
  solve();

  return 0;
}
