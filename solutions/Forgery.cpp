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
template<class T> using VV=vector<vector<T>>;
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
 
 10/5/2018
 
 20:53-21:34 give up
 
 False check is hell
 True check needs huge search.
 
 I cannot find a good equivalent condition like parity. In stuck.
 
 10/8/2018
 
 21:06-21:28 brute-force and got AC
 
 http://codeforces.com/blog/entry/62238
 
 Summary:
  - Can we paint it? Just try them all (brute-force)
   - https://github.com/hiroshi-maybe/topcoder/blob/master/Painting/Painting.cpp
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
string S[MAX_N];
int N,M;
int viz[MAX_N][MAX_N];

vector< pair < int, int > >  moves = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };
vector< pair < int, int > >  moves1 = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
const string yes="YES",no="NO";
bool chk(int r1, int c1, int r2, int c2) {
  if(r2-r1<3||c2-c1<3) return false;
  if(r2-r1==3||c2-c1==3) {
    int cnt=0;
    FOR(i,r1,r2)FOR(j,c1,c2) cnt+=S[i][j]=='#';
    if(cnt==9) return false;
  }
  FOR(i,r1,r2)FOR(j,c1,c2)if(S[i][j]=='.') {
    FORR(m,moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(S[ii][jj]=='.') return false;
    }
  }
  return true;
}
int R1,R2,C1,C2;
void dfs(int i, int j) {
  if(viz[i][j]) return;
  viz[i][j]=1;
//  dump2(i,j);
  SMIN(R1,i),SMAX(R2,i);
  SMIN(C1,j),SMAX(C2,j);
  FORR(m,moves1) {
    int ii=i+m.first,jj=j+m.second;
    if(ii<0||ii>=N||jj<0||jj>=M) continue;
    if(S[ii][jj]=='.') continue;
    dfs(ii,jj);
  }
}
bool solve_wrong() {
  REP(i,N)REP(j,M) if(S[i][j]=='#'&&!viz[i][j]) {
    R1=R2=i,C1=C2=j;
    dfs(i,j);
//    dump4(R1,R2,C1,C2);
    if(!chk(R1,C1,R2+1,C2+1)) return false;
  }
  return true;
}

bool canpaint(int i, int j) {
  REP(di,3)REP(dj,3) {
    int ii=i+di,jj=j+dj;
    if(ii<0||ii>=N||jj<0||jj>=M) return false;
    if(di!=1||dj!=1) {
      if(S[ii][jj]=='.') return false;
    }
  }
  return true;
}
bool solve() {
  VV<int> X(N,VI(M,0));
  REP(i,N)REP(j,M) if(S[i][j]=='#') {
    if(canpaint(i,j)) {
      REP(di,3)REP(dj,3) {
        int ii=i+di,jj=j+dj;
        if(di!=1||dj!=1) X[ii][jj]=1;
      }
    }
  }
  REP(i,N)REP(j,M) if((X[i][j]==1)!=(S[i][j]=='#')) return false;
  return true;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N) cin>>S[i];
  
  cout<<(solve()?yes:no)<<endl;
  
  return 0;
}
