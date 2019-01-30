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

// $ cp-batch TreeWithMaximumCost | diff TreeWithMaximumCost.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TreeWithMaximumCost.cpp && ./a.out

/*
 
 1/25/2019
 
 14:49-15:52 AC
 
 https://codeforces.com/blog/entry/63961
 
 Almost same as https://leetcode.com/problems/sum-of-distances-in-tree/
 I solved this problem by myself. However I couldn't solve LeetCode problem on the same day 😡
 
 ans[0]=f(0,-1)
 f(u,v)=∑{ f(c,u)+∑{A[i]:i∈subtree(c,u)} : c∈children of u in subtree(u,v) }
 
 => ans[v]=ans[u]+∑A-2*∑{A[i]:i∈subtree(v,u)}
 
 Suppose there is an edge between subtree(u,v) and subtree(v,u).
   ans[u]
 = f(u,v) + ∑{dist(i,u)*A[i] : i∈V}
 = f(u,v) + A[v] + ∑{dist(i,u)*A[i] : i∈V\{v}}
 = f(u,v) + A[v] + ∑{(dist(i,v)+1)*A[i] : i∈V\{v}} (dist(i,u)=dist(i,v)+1)
 = f(u,v) + ∑{A[i]:i∈subtree(v,u)} + ∑{dist(i,v)*A[i] : i∈subtree(v,u)}
 = f(u,v) + ∑{A[i]:i∈subtree(v,u)} + f(v,u)
 
 Also ∑{A[i]:i∈subtree(v,u)} + ∑{A[i]:i∈subtree(u,v)} = ∑A
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;
VI G[MAX_N];
LL res=0;
LL memo[MAX_N],sum[MAX_N];

void f(int u, int pre) {
  memo[u]=0,sum[u]=A[u];
  FORR(v,G[u]) if(v!=pre) {
    f(v,u);
    memo[u]+=sum[v]+memo[v],
    sum[u]+=sum[v];
  }
}
void dfs(int u, int pre, LL fs, LL sums) {
//  dump3(u,fs,sums);
  FORR(v,G[u]) if(v!=pre) {
    fs+=memo[v];
    sums+=sum[v];
  }
  //dump4(u,fs,sums,fs+sums);
  SMAX(res,fs+sums);
  FORR(v,G[u]) if(v!=pre) {
    dfs(v,u,fs+sums-memo[v]-sum[v],sums-sum[v]+A[u]);
  }
}
void solve_org() {
  MINUS(memo),MINUS(sum);
  f(0,-1);
  dfs(0,-1,0,0);
  cout<<res<<endl;
}

LL tot=0;
LL fs[MAX_N],asums[MAX_N],ans[MAX_N];
void dfs1(int u, int pre) {
  fs[u]=0,asums[u]=A[u];
  FORR(v,G[u])if(v!=pre) {
    dfs1(v,u);
    fs[u]+=fs[v]+asums[v];
    asums[u]+=asums[v];
  }
}

void dfs2(int u, int pre) {
  SMAX(res,ans[u]);
  dump(u,ans[u]);
  FORR(v,G[u])if(v!=pre) {
    ans[v]=ans[u]+tot-2*asums[v];
    dfs2(v,u);
  }
}

void solve_dp() {
  ZERO(fs),ZERO(asums);
  tot=accumulate(A,A+N,0LL);
  dfs1(0,-1);
  res=ans[0]=fs[0];
  dfs2(0,-1);
  cout<<res<<endl;
}

// inspired by @kmjp's solution
void solve() {
  ZERO(fs),ZERO(asums);
  tot=accumulate(A,A+N,0LL);
  res=0;
  function<void(int,int,int)> dfs1=[&](int u, int pre, int d)->void {
    res+=A[u]*d;
    dump(u,d,A[u]*d,res);
    asums[u]=A[u];
    FORR(v,G[u])if(v!=pre) dfs1(v,u,d+1),asums[u]+=asums[v];
  };
  dfs1(0,-1,0);
  dump(res);
  ans[0]=res;
  function<void(int,int)> dfs2=[&](int u, int pre)->void {
    if(u!=0) ans[u]=ans[pre]-asums[u]+(tot-asums[u]);
    FORR(v,G[u])if(v!=pre) dfs2(v,u);
  };
  dfs2(0,-1);
  dumpC(ans,ans+N);
  cout<<*max_element(ans,ans+N)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(_,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
