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
 
 9/6/2018
 
 9:04-9:40 1WA
 
 5
 325539 329221 106895 882089 718673
 502890 699009 489855 430685 939232
 
 9/10/2018
 
 14:30-14:57 I figured out that WA is happening due to implementaion bug
 
 http://codeforces.com/blog/entry/61692
 
 */
// 9:04-9:40 WA
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+10;
int N;
LL A[MAX_N],B[MAX_N];
LL f_org(bool turn, int i, int j) {
  if(i==-1&&j==-1) return 0;
  // covering pattern is not exhaustive 😡
  if(turn==0&&i==-1) return f_org(turn^1,i,j-1);
  if(turn==1&&j==-1) return f_org(turn^1,i-1,j);
  
  if(turn==0) {
    if(A[i]>=B[j]) return -(A[i]+f_org(turn^1,i-1,j));
    else return -f_org(turn^1,i,j-1);
  } else {
    if(B[j]>=A[i]) return -(B[j]+f_org(turn^1,i,j-1));
    else return -f_org(turn^1,i-1,j);
  }
}
LL f(bool turn, int i, int j) {
  if(i==-1&&j==-1) return 0;
  if(i==-1) {
    if(turn==0) return -f(turn^1,i,j-1);
    else return -(B[j]+f(turn^1,i,j-1));
  }
  if(j==-1) {
    if(turn==1) return -f(turn^1,i-1,j);
    else return -(A[i]+f(turn^1,i-1,j));
  }
  if(turn==0) {
    if(A[i]>=B[j]) return -(A[i]+f(turn^1,i-1,j));
    else return -f(turn^1,i,j-1);
  } else {
    if(B[j]>=A[i]) return -(B[j]+f(turn^1,i,j-1));
    else return -f(turn^1,i-1,j);
  }
}
void solve() {
  sort(A,A+N),sort(B,B+N);
  
  cout<<-f(0,N-1,N-1)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  REP(i,N) cin>>B[i];
  solve();
  return 0;
}
