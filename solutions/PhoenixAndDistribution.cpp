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

// $ cp-batch PhoenixAndDistribution | diff PhoenixAndDistribution.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PhoenixAndDistribution.cpp && ./a.out

/*
 
 5/1/2020
 
 8:12-8:55 AC
 
 https://codeforces.com/blog/entry/76555
 
 */

//const int MAX_N=1e6+1;
string S;
int N,K;

void solve() {
  sort(ALL(S));
  
  string pre=S.substr(0,K),suf=S.substr(K);
  set<char> scs(ALL(suf)),pcs(ALL(pre));
  string res;
//  dumpc(pcs);
  if(SZ(pcs)>1) {
    auto it=pcs.rbegin();
    res=string(1,*it);
  } else if(SZ(scs)>1) {
    res=string(1,S.front());
    res+=suf;
  } else {
    vector<string> ss(K,string(1,S.front()));
    FOR(i,K,N) ss[(i-K)%K].push_back(S[i]);
    res=*max_element(ALL(ss));
  }
  
  cout<<res<<endl;
}

void solve_wrong() {
  sort(ALL(S));
  set<char> cs,allcs(ALL(S));
  
  string pre=S.substr(0,K);
  FORR(c,pre) cs.emplace(c);
  if(SZ(cs)>1) {
    auto it=cs.rbegin();
    string res(1,*it);
    cout<<res<<endl;
    return;
  }
  string res;
  if(SZ(allcs)==1) {
    vector<string> ss(K,string(1,S.front()));
    FOR(i,K,N) ss[(i-K)%K].push_back(S[i]);
    res=*max_element(ALL(ss));
  } else {
    res=string(1,S.front());
    res+=S.substr(K);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>S;
    solve();
  }
  
  return 0;
}
