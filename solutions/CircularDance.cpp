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

// $ cp-batch CircularDance | diff CircularDance.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CircularDance.cpp && ./a.out

/*
 
 1/24/2019
 
 15:51-16:09 WA on test case #13...
 16:39 bug fix and got AC
 
 The last one should not be already selected one....
 When first element is determined, next and next-next ones can be determined, too.
 If we follow this, the corner case never hits. Added the solution.
 
 https://codeforces.com/blog/entry/64130
 https://betrue12.hateblo.jp/entry/2018/12/28/152148
 
 */

const int MAX_N=1e6+1;
int A[MAX_N][2];
int N;

// Added this simpler solution.
void solve() {
  VI res(1,0);
  int x=A[0][0],y=A[0][1];
  if(A[x][0]==y||A[x][1]==y) {
    res.push_back(x);
    res.push_back(y);
  } else {
    res.push_back(y);
    res.push_back(x);
  }
  FOR(i,1,N-1) {
    int a=res[i],b=res[i+1];
    int x=A[a][0],y=A[a][1];
    if(x==b) res.push_back(y);
    else res.push_back(x);
  }
  REP(i,N) {
    int a=res[i];
    int b=res[(i+1)%N],c=res[(i+2)%N];
    assert((A[a][0]==b&&A[a][1]==c)||(A[a][0]==c&&A[a][1]==b));
  }
  REP(i,N) printf("%d ",res[i]+1);
  println("");
}

int viz[MAX_N];
void solve_org() {
  ZERO(viz);
  
  VI res(1,0); viz[0]=1;
  REP(i,N-1) {
    int a=res.back();
    int x=A[a][0],y=A[a][1];
    assert(a!=x&&a!=y);
    if(viz[x]==0&&(A[x][0]==y||A[x][1]==y)) {
//      dump4(a,x,y,x);
      res.push_back(x),viz[x]=1;
    } else {
      assert(A[y][0]==x||A[y][1]==x);
      assert(viz[y]==0);
//      dump4(a,x,y,y);
      res.push_back(y),viz[y]=1;
    }
  }
//  dumpAR(res);
  REP(i,N) {
    int a=res[i];
    int b=res[(i+1)%N],c=res[(i+2)%N];
    assert((A[a][0]==b&&A[a][1]==c)||(A[a][0]==c&&A[a][1]==b));
  }
  REP(i,N) printf("%d ",res[i]+1);
  println("");
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> shuffle(vector<int> &A) {
  int N = A.size();
  vector<int> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}
void test() {
  N=genRandNum(3,10);
  VI X(N); REP(i,N)X[i]=i;
  X=shuffle(X);
  println("%d",N);
  REP(i,N) {
    A[X[i]][0]=X[(i+1)%N],A[X[i]][1]=X[(i+2)%N];
    if(genRandNum(0,2)) swap(A[X[i]][0],A[X[i]][1]);
  }
  REP(i,N) {
    println("%d %d",A[i][0],A[i][1]);
  }
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N;
  REP(i,N)REP(j,2) cin>>A[i][j],A[i][j]--;
  solve();
  
  return 0;
}
