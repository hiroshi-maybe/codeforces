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
 
 10/7/2018 Lyft Level 5 Challenge 2018 - Elimination Round
 
 10:05-10:19 AC
 
 https://codeforces.com/blog/entry/62287
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
int N;
int ax,ay,bx,by,cx,cy;
int viz[MAX_N][MAX_N];

const string yes="YES",no="NO";
vector< pair < int, int > >  movesd = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };

bool ng(int i, int j) {
  if(i==ay||j==ax) return true;
  if(abs(i-ay)==abs(j-ax)) return true;
  return false;
}
void dfs(int i, int j) {
  if(viz[i][j]) return;
  viz[i][j]=1;
  FORR(m,movesd) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=N) continue;
    if(ng(ii,jj)) continue;
    dfs(ii,jj);
  }
}
bool solve() {
  ZERO(viz);
  dfs(by,bx);
  /*
  REP(i,N) {
    REP(j,N) cout<<viz[i][j];
    cout<<endl;
  }*/
  return viz[cy][cx];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>ax>>ay>>bx>>by>>cx>>cy;
  --ax,--ay,--bx,--by,--cx,--cy;
  cout<<(solve()?yes:no)<<endl;
  
  return 0;
}
