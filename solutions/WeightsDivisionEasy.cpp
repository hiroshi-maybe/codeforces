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

// $ cp-batch WeightsDivisionEasy | diff WeightsDivisionEasy.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WeightsDivisionEasy.cpp && ./a.out

/*

 8/5/2020

 8:14-9:11 understood the problem
 9:27 AC

 https://twitter.com/hanseilimak/status/1291423391812001794
 https://codeforces.com/blog/entry/81082

 */

const int MAX_N=1e6+1;
LL S;
int N;

vector<pair<LL,int>> G[MAX_N];

LL sum=0;
int dfs(int u, int pre, priority_queue<tuple<LL,int,LL>> &Q) {
  int cnt=SZ(G[u])==1;
  FORR(p,G[u]) if(p.second!=pre) {
    int v; LL w; tie(w,v)=p;
    int cnt2=dfs(v,u,Q);
    Q.emplace((w-w/2)*cnt2, cnt2, w);
    cnt+=cnt2;
    //dump(u,v,w,cnt2,(w-w/2)*cnt2);
    sum+=w*cnt2;
  }
  return cnt;
}
void solve() {
  sum=0;
  int res=0;
  priority_queue<tuple<LL,int,LL>> Q;
  dfs(0,-1,Q);
  while(sum>S) {
    ++res;
    LL a,w; int cnt; tie(a,cnt,w)=Q.top(), Q.pop();
    //dump(sum,a,res);
    sum-=a;
    w/=2;
    Q.emplace((w-w/2)*cnt,cnt,w);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>S;
    REP(i,N) G[i].clear();
    REP(_,N-1) {
      int u,v; LL w; cin>>u>>v>>w;
      --u,--v;
      G[u].emplace_back(w,v),G[v].emplace_back(w,u);
    }
    solve();
  }

  return 0;
}