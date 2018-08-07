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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 8/3/2018 ER48 div2
 
 10:10-11:46 pause
 12:50-12:58 fix bug, submit and got AC
 
 Editorial:
  - http://codeforces.com/blog/entry/61015
  - http://betrue12.hateblo.jp/entry/2018/08/04/135456
  - https://twitter.com/tempura_pp/status/1025423228276113408
 
 Summary:
  - Analysis was straighforward though, implementation was pretty painful
 
 */

// 10:10-11:46 give up
// 12:50-12:58 fix bug and submit and got AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3e5+1;
LL A[2][MAX_N];
int N;

LL cumA[2][2*MAX_N],cumB[2][2*MAX_N];

LL solve() {
  ZERO(cumA),ZERO(cumB);
  REP(st,2) {
    REP(i,2*N) {
      int r=i>=N?st^1:st,c=i>=N?2*N-i-1:i;
      LL a=A[r][c];
      cumA[st][i+1]=cumA[st][i]+a;
      cumB[st][i+1]=cumB[st][i]+a*i;
    }
  }
  LL cur=0;
  int i=0,j=0;
//  int l=0,r=N;
  LL res=cumB[0][2*N];
  REP(t,2*N) {
    cur+=t*A[i][j];
    if(t%2==1) {
      int l=(t+1)/2,r=2*N-l;
      LL a=(cumA[i][r]-cumA[i][l])*(t+1-l);
      LL b=cumB[i][r]-cumB[i][l];
      SMAX(res,cur+a+b);
      /*
      dump4(t,i,j,cur);
      dump4(t,l,r,a+b);
      dump4(t,cumA[i][l],cumA[i][r],a);
      dump4(t,cumB[i][l],cumB[i][r],b);*/
    }
    if(t%2==1) ++j;
    else i=i^1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[0][i];
  REP(i,N) cin>>A[1][i];

  cout<<solve()<<endl;
  
  return 0;
}
