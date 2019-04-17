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

// $ cp-batch ServalAndRootedTree | diff ServalAndRootedTree.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ServalAndRootedTree.cpp && ./a.out

/*
 
 4/13/2019
 
 8:18-8:56 give up
 
 4/15/2019
 
 10:40-12:05, 16:35-17:20 read editorials and got AC
 
 https://codeforces.com/blog/entry/66539
 https://www.hamayanhamayan.com/entry/2019/04/14/110609
 https://cinnamo-coder.hatenablog.com/entry/2019/04/14/183311
 
 We cannot test by assigning 1..K because of constraint.
 Instead we can solve subproblems for each subtree.
 We want to know maximum rank in the subtree that we can get.
 If we can merge them in parent, we can solve this problem.
 
 Let's define problem as f(u) = maximum rank of leaf in the subtree rooted by `u`
 then res=K-f(0)-1
 
 1) `u` is max node
 
 We can take maximum among children. We can just take highest rank.
 Suppose we have children with rank R={2,4,3,5}.
 If we give highest two numbers in subtree `0`, we can obtain maximum leaf.
 
 2) `u` is min node
 
 We take ∑{r∈R} from children.
 Suppose we have children with rank R={2,4,3,5}.
 The optimal rank that we get is 14-th (=2+4+3+5).
 
 */

const int MAX_N=1e6+1;
VI G[MAX_N];
int S[MAX_N];
int N;
const int Inf=1e6;

II dfs(int u) {
  int s=S[u];
  if(G[u].empty()) return {1,1};
  int cnt=0,res=s==1?Inf:0;
  FORR(v,G[u]) {
    auto p=dfs(v);
    cnt+=p.second;
    if(s==1) SMIN(res,p.first);
    else res+=p.first;
  }
  return {res,cnt};
}
void solve() {
  auto p=dfs(0);
  int res=p.second-p.first+1;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>S[i];
  REP(i,N-1) {
    int u; cin>>u;
    --u;
    G[u].push_back(i+1);
  }
  solve();
  
  return 0;
}
