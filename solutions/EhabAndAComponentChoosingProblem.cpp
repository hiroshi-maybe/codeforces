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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
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

// $ ../batch EhabAndAComponentChoosingProblem | diff EhabAndAComponentChoosingProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabAndAComponentChoosingProblem.cpp && ./a.out

/*
 
 12/24/2018
 
 21:01-21:50 analysis
 22:01 submit and got WA on test case #5
 
 I missed to catch up a condition "connected component should not overlap".
 Kadane's algorithm is not applicable without modification to satisfy this condition.
 
 12/25/2018
 
 11:30-12:03 got AC before looking at editorial (However I looked at failed test case)
 
 Keep component max and detect component separation by checking sign of current summation
 
 https://codeforces.com/blog/entry/63656
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;
VI G[MAX_N];
bool allneg=true;
map<LL,int> cnt;
const LL Inf=1e17;

pair<LL,LL> dfs(int u, int pre) {
  LL res=A[u];
  LL cmax=-Inf;
  FORR(v,G[u]) if(v!=pre) {
    auto p=dfs(v,u);
    LL x=p.first;
    if(x>0) res+=x;
    SMAX(cmax,p.second);
  }
  if(res>cmax) {
//    dump3(u,res,cmax);
    cnt[res]++;
    cmax=res;
  }
  if(res<=0) cmax=-Inf; // cut component
  return {res,cmax};
}

void solve() {
  dfs(0,-1);
  auto p=*cnt.rbegin();
  LL r=p.first*p.second,d=p.second;
  println("%lld %lld",r,d);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) {
    cin>>A[i];
    if(A[i]>0) allneg=false;
  }
  REP(i,N-1) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  solve();
  
  return 0;
}
