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
 
 8/27/2018 AIM Tech Round 5
 
 10:11-11:16 AC
 
 It took tons of time to figure out that I should solve each dimension independently due to poor complexity taste 😞
 
 There are almost 10^5 rectangles (4*10^5 points).
 Regardless of number of points or number of rectangles, O(N^2) algorithm never works.
 Even if we make 2d imos, it takes O(N^2) time to check all 4*N points against O(N) intervals.
 
 Corner points should be candidate of the result.
 If those points are part of N-1 overlapping rectangles, it should be N-1 overlapping in x/y-coordinate respectively.
 So we can do 1d imos for x-coordinate and y-coordinate.
 We can firstly filter those x values and y values and check all the pairs of them.
 
 Editorials:
  - http://codeforces.com/blog/entry/61493
 
 Tweets:
  - https://togetter.com/li/1261045
  - https://twitter.com/satanic0258/status/1034153506381258755
 
 Actually editorial is showing different solution.
 Overlapping rectangle is also a rectangle.
 Suppose we want to find `i` s.t. R[0..i-1] and R[i+1..N-1] are overlapping.
 If we know overlapping rectangle of R[0..i-1] and R[i+1..N-1], it's possible to check it in O(1) time.
 Thus we can solve by remembering R[0..x] and R[x..N-1] in O(N) space.
 
 Summary:
  - imos makes O(N) intervals. Switch to analyze dimension-independent algorithm quickly
 
 */

// 11:16 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=132674+2;
int N;
int X1[MAX_N],Y1[MAX_N],X2[MAX_N],Y2[MAX_N];
void solve_org() {
  map<int,int> imos;
  REP(i,N) imos[X1[i]]+=1,imos[X2[i]+1]-=1;
  int cur=0;
  SETI X;
  FORR(kvp,imos) {
    cur+=kvp.second;
    if(cur>=N-1) {
      X.emplace(kvp.first);
    }
  }
  imos.clear();
  REP(i,N) imos[Y1[i]]+=1,imos[Y2[i]+1]-=1;
  cur=0;
  SETI Y;
  FORR(kvp,imos) {
    cur+=kvp.second;
    if(cur>=N-1) {
      Y.emplace(kvp.first);
    }
  }
  FORR(x,X)FORR(y,Y) {
    int cnt=0;
    REP(i,N) {
      int x1=X1[i],x2=X2[i],y1=Y1[i],y2=Y2[i];
      if(x1<=x&&x<=x2&&y1<=y&&y<=y2) ++cnt;
      /*
      REP(j,2)REP(k,2) if(X.count(XX[j])&&X.count(YY[k])) {
        cout<<XX[j]<<" "<<YY[k]<<endl;
        return;
      }*/
    }
    if(cnt>=N-1) {
      cout<<x<<" "<<y<<endl;
      return;
    }
  }
  
  assert(false);
}

const int Inf=2e9;
int A[MAX_N][4],B[MAX_N][4]; // x1,y1,x2,y2
void solve() {
//  int x1=Inf,x2=-Inf,y1=Inf,y2=-Inf;
  REP(i,4) {
    A[0][i]=A[N+1][i]=B[0][i]=B[N+1][i]=i<2?-Inf:Inf;
  }
  REP(i,N) {
    int X[4]={X1[i],Y1[i],X2[i],Y2[i]};
    REP(j,2) A[i+1][j]=max(A[i][j],X[j]);
    FOR(j,2,4) A[i+1][j]=min(A[i][j],X[j]);
  }
  for(int i=N-1; i>=0; --i) {
    int X[4]={X1[i],Y1[i],X2[i],Y2[i]};
    REP(j,2) B[i+1][j]=max(B[i+2][j],X[j]);
    FOR(j,2,4) B[i+1][j]=min(B[i+2][j],X[j]);
  }
  FORE(i,1,N) {
    int X[4];
    REP(j,2) X[j]=max(A[i-1][j],B[i+1][j]);
    FOR(j,2,4) X[j]=min(A[i-1][j],B[i+1][j]);
    
    if(X[0]<=X[2]&&X[1]<=X[3]) {
      cout<<X[0]<<" "<<X[1]<<endl;
      return;
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>X1[i]>>Y1[i]>>X2[i]>>Y2[i];
  solve();
  return 0;
}
