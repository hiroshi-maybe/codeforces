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
 
 4/29/2018
 
 22:50-23:42 1WA
 
 5/1/2018
 
 19:15-19:20 fix corner case bug (x1==x2) and got ACC
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_C=1e5+1,MAX_Q=1e5+1;
LL N,M,C1,C2,V,C3;
vector<LL> A,B;
const LL Inf=1e18;
LL stair(LL x1, LL y1, LL x2, LL y2, LL s) {
  return abs(y1-s)+abs(y2-s)+abs(x2-x1);
}
LL elev(LL x1, LL y1, LL x2, LL y2, LL e) {
  return abs(y1-e)+abs(y2-e)+(abs(x2-x1)+V-1)/V;
}

LL f(LL x1, LL y1, LL x2, LL y2) {
  LL res=Inf;

  int i1=lower_bound(A.begin(),A.end(),y1)-A.begin(),i0=i1-1;
  if(i1<C1) SMIN(res,stair(x1,y1,x2,y2,A[i1]));
  if(0<=i0) SMIN(res,stair(x1,y1,x2,y2,A[i0]));
  
  int j1=lower_bound(B.begin(),B.end(),y1)-B.begin(),j0=j1-1;
  if(j1<C2) SMIN(res,elev(x1,y1,x2,y2,B[j1]));
  if(0<=j0) SMIN(res,elev(x1,y1,x2,y2,B[j0]));
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>C1>>C2>>V;
  A=vector<LL>(C1);
  B=vector<LL>(C2);
  REP(i,C1) cin>>A[i];
  REP(i,C2) cin>>B[i];
  cin>>C3;
  REP(i,C3) {
    LL x1,y1,x2,y2;
    cin>>x1>>y1>>x2>>y2;
    
    if(x1==x2) {
      cout<<abs(y1-y2)<<endl;
    } else {
      LL a=f(x1,y1,x2,y2),b=f(x2,y2,x1,y1);
      cout<<min(a,b)<<endl;
    }
  }
  
  return 0;
}

