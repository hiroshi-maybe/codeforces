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
 
 10/11/2018 E52
 
 9:13-11:40 AC
 
 - tons of misunderstanding of problem statement
 - tons of bug (variable name, floy-warshall)
 
  http://codeforces.com/blog/entry/62411
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
vector< pair < int, int > >  kmoves = { {2,1}/*R*/,{1,2}};
const int MAX_N=10+1;
int A[MAX_N][MAX_N];
int N;
pair<LL,LL> D[MAX_N*MAX_N][3][MAX_N*MAX_N][3];
LL const Inf=1e16;
pair<LL,LL> dp[MAX_N*MAX_N][3];
pair<LL,LL> solve() {
  REP(i,N*N)REP(k1,3)REP(j,N*N)REP(k2,3) D[i][k1][j][k2]={Inf,Inf};
  
  REP(i,N)REP(j,N) {
    int u=A[i][j];
    
    // knight
    FORR(m,kmoves) for(int d1=-1; d1<=1; d1+=2) for(int d2=-1; d2<=1; d2+=2) {
      int ii=i+d1*m.first,jj=j+d2*m.second;
      if(ii<0||ii>=N||jj<0||jj>=N) continue;
      int v=A[ii][jj];
      assert(u!=v);
      D[u][0][v][0]={1,0};
      D[u][0][v][1]={2,1};
      D[u][0][v][2]={2,1};
    }
    
    // bishop
    for(int d=1; d<=N; ++d) for(int d1=-1; d1<=1; d1+=2) for(int d2=-1; d2<=1; d2+=2) {
      int ii=i+d*d1,jj=j+d*d2;
      if(ii<0||ii>=N||jj<0||jj>=N) continue;
      int v=A[ii][jj];
      if(u==v) continue;
       assert(u!=v);
      D[u][1][v][0]={2,1};
      D[u][1][v][1]={1,0};
      D[u][1][v][2]={2,1};
    }
    
    // rook
    for(int d=1; d<=N; ++d) for(int d1=-1; d1<=1; d1+=2) REP(s,2) {
      int ii=i,jj=j;
      if(s) ii+=d1*d;
      else jj+=d1*d;
      if(ii<0||ii>=N||jj<0||jj>=N) continue;
      int v=A[ii][jj];
      if(u==v) continue;
       assert(u!=v);
      D[u][2][v][0]={2,1};
      D[u][2][v][1]={2,1};
      D[u][2][v][2]={1,0};
    }
  }

  REP(b1,N*N)REP(b2,3)REP(a1,N*N)REP(a2,3)REP(c1,N*N)REP(c2,3) {
    LL x=D[a1][a2][b1][b2].first+D[b1][b2][c1][c2].first;
    LL y=D[a1][a2][b1][b2].second+D[b1][b2][c1][c2].second;
    assert(x>0);
    SMIN(D[a1][a2][c1][c2],make_pair(x,y));
  }

  REP(k,3)dp[0][k]={0,0};
  FORE(u,1,N*N)REP(k,3)dp[u][k]={Inf,Inf};
  REP(u,N*N)REP(k,3)REP(j,3) {
    LL a,b; tie(a,b)=dp[u][k];
    LL x=D[u][k][u+1][j].first+a,y=D[u][k][u+1][j].second+b;
    SMIN(dp[u+1][j],make_pair(x,y));
  }
  pair<LL,LL> res=min({dp[N*N-1][0],dp[N*N-1][1],dp[N*N-1][2]});
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N)REP(j,N) {
    cin>>A[i][j];
    A[i][j]--;
  }
  LL a,b; tie(a,b)=solve();
  cout<<a<<" "<<b<<endl;
  
  return 0;
}
