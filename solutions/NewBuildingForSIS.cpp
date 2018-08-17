#include <iostream>
#include <iomanip>
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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/11/2018 R503 div2
 
 6:35-6:48 1WA
 7:31 submit and got AC
 
 Editorials:
  - https://codeforces.com/blog/entry/61161
 
 Summary:
  - I didn't notice very clear corner case x1==x2 😡
  - I spent tons of time to find my bug by random test cases and Floyd-Warshall 😡😡
 
 */

// 6:48 1WA
// 6:57 2WA
// 7:31 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_K=1e4+1;
LL N,H,a,b,K;
pair<LL,LL> X1[MAX_K],X2[MAX_K];

LL f(pair<LL,LL> p1, pair<LL,LL> p2) {
  LL x1=p1.first,y1=p1.second,x2=p2.first,y2=p2.second;
  LL res=abs(x2-x1);
  if(y1>b&&y2>b) res+=(x1==x2?abs(y1-y2):y1-b+y2-b);
  else if(y1<a&&y2<a) res+=(x1==x2?abs(y1-y2):a-y1+a-y2);
  else res+=abs(y2-y1);
  return res;
}

void solve() {
  REP(i,K) {
    cout<<f(X1[i],X2[i])<<endl;
  }
}

int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rand() % (int)(ub - lb);
  return x + lb;
}
LL mx[100][100];
void test() {
  
  while(true) {
    b=genRandNum(0,10),a=genRandNum(0,b+1);
    const LL Inf=1e10;
    REP(i,100)REP(j,100)mx[i][j]=i==j?0:Inf;
    REP(i,9)FORE(j,a,b) mx[10*i+j][10*(i+1)+j]=mx[10*(i+1)+j][10*i+j]=1;
    REP(i,10)REP(j,9) mx[10*i+j][10*i+j+1]=mx[10*i+j+1][10*i+j]=1;
    REP(k,100)REP(i,100)REP(j,100) SMIN(mx[i][j],mx[i][k]+mx[k][j]);
    int q=0;
    while(++q<100) {
      pair<LL,LL> p1={genRandNum(0,10),genRandNum(0,10)},p2={genRandNum(0,10),genRandNum(0,10)};
      if(mx[10*p1.first+p1.second][10*p2.first+p2.second]!=f(p1,p2)) {
        dump4(a,b,mx[10*p1.first+p1.second][10*p2.first+p2.second],f(p1,p2));
        dump4(p1.first,p1.second,p2.first,p2.second);
        return;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  cin>>N>>H>>a>>b>>K;
  REP(i,K) {
    LL x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    X1[i]={x1,y1};
    X2[i]={x2,y2};
  }
  solve();
  return 0;
}
