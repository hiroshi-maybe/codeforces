#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 10/20/2018 R517 div2
 
 25:18-25:59 AC
 
 http://codeforces.com/blog/entry/62612
 
 I wrote complicated graph search though, graph is DAG. DP works.
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[MAX_N],B[MAX_N];
int N;
VI G[MAX_N*4];

const string yes="YES",no="NO";
VI res;
bool viz[MAX_N*4];
bool dfs(int u) {
  if(viz[u]) return false;
  viz[u]=true;
  if(u/4==N-1) {
    res.push_back(u%4);
    return true;
  }
  FORR(v,G[u]) if(dfs(v)) {
    res.push_back(u%4);
    return true;
  }
  return false;
}
void solve_org() {
  REP(i,N-1) {
    REP(a,4) REP(b,4) {
      if((a|b)!=A[i]){
        continue;
      }
      if((a&b)!=B[i]) {
        continue;
      }
      G[4*i+a].push_back(4*(i+1)+b);
    }
  }
  bool ok=false;
  REP(u,4) {
    ZERO(viz);
    if(dfs(u)) {
      ok=true;
      break;
    }
  }
  if(!ok) {
    cout<<no<<endl;
    exit(0);
  }
  reverse(res.begin(),res.end());
//  dumpAR(res);
  assert(SZ(res)==N);
  REP(i,N-1) {
    assert((res[i]|res[i+1])==A[i]);
    assert((res[i]&res[i+1])==B[i]);
  }
  
  cout<<yes<<endl;
  REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
}

int pre[MAX_N][4];
int dp[MAX_N][4];
void solve() {
  MINUS(pre);
  ZERO(dp);
  REP(i,4) dp[0][i]=1;
  REP(i,N-1)REP(a,4) if(dp[i][a]) REP(b,4) if((a|b)==A[i]&&(a&b)==B[i]) {
    dp[i+1][b]=1;
    pre[i+1][b]=a;
  }
  REP(i,4) if(pre[N-1][i]!=-1) {
    VI res;
    int a=i;
    for(int i=N-1; i>=0; --i) res.push_back(a),a=pre[i][a];
    reverse(ALL(res));
    cout<<yes<<endl;
    REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
    return;
  }
  cout<<no<<endl;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N-1) cin>>A[i];
  REP(i,N-1) cin>>B[i];

  solve();
  
  return 0;
}
