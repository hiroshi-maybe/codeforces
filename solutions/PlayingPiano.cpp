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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 11/19/2018
 
 12:33-12:57 AC
 
 https://codeforces.com/blog/entry/63324
 
 */
// 12:57 AC
// $ ../batch PlayingPiano | diff PlayingPiano.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PlayingPiano.cpp && ./a.out
const int MAX_N=1e5+1;
int A[MAX_N];
int N;

int dp[MAX_N][5];
int pre[MAX_N][5];
void solve() {
  ZERO(dp);
  MINUS(pre);
  REP(j,5) dp[0][j]=1;
  FOR(i,1,N)REP(j,5)if(dp[i-1][j]) {
    REP(k,5) {
      if(A[i-1]<A[i]&&j<k) dp[i][k]=1,pre[i][k]=j;
      if(A[i-1]>A[i]&&j>k) dp[i][k]=1,pre[i][k]=j;
      if(A[i-1]==A[i]&&j!=k) dp[i][k]=1,pre[i][k]=j;
    }
  }
  VI res;
  REP(j,5) if(dp[N-1][j]&&res.empty()) res.push_back(j);
  if(res.empty()) {
    println("-1");
    return;
  }
  
  int i=N-1;
  int cur=res.front();
  while(cur>=0) {
    assert(i>=0);
    cur=pre[i--][cur];
    if(cur>=0)res.push_back(cur);
  }
  dump2(N,SZ(res));
  dumpAR(res);
  assert(i==-1);
  assert(SZ(res)==N);
  reverse(ALL(res));
  REP(i,N-1) {
    if(A[i]<A[i+1]) assert(res[i]<res[i+1]);
    if(A[i]>A[i+1]) assert(res[i]>res[i+1]);
    if(A[i]==A[i+1]) assert(res[i]!=res[i+1]);
  }
  
  REP(i,N) printf("%d ",res[i]+1);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}
