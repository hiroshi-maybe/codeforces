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
 
 18:05-18:13 pause
 20:20-21:04 AC
 
 Editorial:
  - http://codeforces.com/blog/entry/59105
 
 Simple solutions:
  - Those are fixing position of ship first and counting for relevant cells 👏
   - http://codeforces.com/contest/965/submission/37605358
   - http://codeforces.com/contest/965/submission/37606360
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e2+1;
int K,N;
string G[MAX_N];

int g(int a, int b, int di, int dj) {
  int res=0;
  while(true) {
    a+=di,b+=dj;
    if(0<=a&&a<N&&0<=b&&b<N&&G[a][b]=='.') res++;
    else break;
  }
  return min(res,K-1);
}

int f(int a, int b) {
  if(G[a][b]=='#') return 0;

  int x1=g(a,b,1,0),y1=g(a,b,-1,0);
//  if(a==5&&b==2)dump4(a,b,x1,y1);
  int res1=0;
  while(K-x1-1<=y1&&x1>=0) res1+=1,x1--;
  
  int x2=g(a,b,0,1),y2=g(a,b,0,-1);
//  if(a==5&&b==2)dump4(a,b,x2,y2);
  int res2=0;
  while(K-x2-1<=y2&&x2>=0) res2+=1,x2--;
  
  dump4(a,b,res1,res2);
  
  return res1+res2;
}

void solve() {
  II res={0,0};
  int maxn=0;
  REP(i,N)REP(j,N) {
    int x=f(i,j);
    if(x>maxn) res={i,j},maxn=x;
  }
  cout<<res.first+1<<" "<<res.second+1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>G[i];
  solve();
  return 0;
}
