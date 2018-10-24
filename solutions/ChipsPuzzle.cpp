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
// minmax
template<class T> inline bool SMIN(T &l,const T &r){return l<r?l=r,1:0;}
template<class T> inline bool SMAX(T &l,const T &r){return l>r?l=r,1:0;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/18/2018
 
 13:30-14:00, 14:30-15:00 give up
 
 10/23/2018
 
 20:20-21:29 analysis
 22:15 I gave up because I cannot make top two strings.
 
 I wasted 1 hour due to wrong approach. Making direct move from A to B.
 Next I tried to make a fixed state. However I couldn't complete.
 
 Collecting all 0s and 1s to each dedicated cell was good.
 However I couldn't resolve mixed 0s and 1s in top two rows.
 
 moving 0s and 1s to one place and deliver?
  => upper bound of this strategy is not clear
 
 http://codeforces.com/blog/entry/62563
 
 There are two keys
 1. Move to common intermediate state
  - Operation is symmetry. If we can make it, reversed operation will make final state
 2. Leverage two dimension for two values
  - There are only two values {0,1}. Separate them to independent places
 
 25:20 AC after tons of stupid TLE due to `endl`
 
 Summary:
  - Very disappointing performance. Keep in mind that all conditions are satisfied.
 
 I spent more than one hour to catch root cause of TLE "endl" 🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=310;
string A[2][MAX_N][MAX_N];
queue<int> Q[MAX_N][MAX_N];

int LIM;
int N,M;
typedef tuple< int, int, int, int> IIII;
int pos[2];
IIII res[2][200100];
inline void move(int i1, int j1, int i2, int j2, int p) {
  res[p][pos[p]++]={i1+1,j1+1,i2+1,j2+1};
//  assert(SZ(Q[i1][j1]));
//  dump3(SZ(res[p]),LIM,SZ(Q[i1][j1]));
//  dump4(i1,j1,i2,j2);
//  assert(SZ(res[p])<=2*LIM);
  char x=Q[i1][j1].front();
  Q[i1][j1].pop();
  Q[i2][j2].push(x);
}

void f(int p) {
  REP(i,N)REP(j,M) {
    while(SZ(Q[i][j]))Q[i][j].pop();
    for(int k=SZ(A[p][i][j])-1; k>=0; --k) Q[i][j].push(A[p][i][j][k]-'0');
  }
  FOR(j,1,M) while(SZ(Q[0][j])) move(0,j,0,0,p);
  FOR(i,1,N) while(SZ(Q[i][0])) move(i,0,0,0,p);
//  dump("ph1");
  
  FOR(i,1,N)FOR(j,1,M)while(SZ(Q[i][j])) {
    int i2=i,j2=j;
    if(Q[i][j].front()==0) i2=0;
    else j2=0;
    move(i,j,i2,j2,p);
  }
//  dump("ph2");

  FOR(i,2,N) while(SZ(Q[i][0])) move(i,0,1,0,p);
  FOR(j,2,M) while(SZ(Q[0][j])) move(0,j,0,1,p);
//  dump("ph3");

//  dump(SZ(Q[0][0]));
  while(SZ(Q[0][0])) {
    int i2=0,j2=0;
    if(Q[0][0].front()==0) j2=1;
    else i2=1;
    move(0,0,i2,j2,p);
  }
//  dump("ph4");
}
void showQ(int i, int j) {
  queue<int> QQ=Q[i][j];
  dump3(i,j,SZ(QQ));
  while(SZ(QQ)) {
    dump(QQ.front()); QQ.pop();
  }
}

void solve() {
  f(0);
  REP(i,N)REP(j,M) reverse(A[1][i][j].begin(),A[1][i][j].end());
  f(1);
  
  reverse(res[1],res[1]+pos[1]);
  printf("%d\n",pos[0]+pos[1]);
  REP(p,2) REP(i,pos[p]) {
    int x1,y1,x2,y2; tie(x1,y1,x2,y2)=res[p][i];
    if(p) swap(x1,x2),swap(y1,y2);
    printf("%d %d %d %d\n",x1,y1,x2,y2);
  }
}

/*
void solve_wrong() {
  REP(j,M) {
    FOR(i,2,N) REP(c,2) want1[j][c]+=count(B[i][j].begin(),B[i][j].end(),'0'+c);
  }
  
  // move to top right
  REP(j,M-1) REP(i,2) {
    while(SZ(Q[i][j])) {
      // This is not satisfying that charater can move in the same row. Are you crazy? 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
      move(i,j,Q[i][j].front(),M-1);
    }
  }
  REP(i,2) {
    while(cnt[i][M-1][i^1]) {
      move(i,M-1,Q[i][M-1].front(),M-2);
    }
  }
  REP(i,2) {
    while(SZ[i][M-2]) {
      move(i,M-2,Q[i][M-2].front(),M-1);
    }
  }

  // move to top
  REP(j,M) {
    FOR(i,2,N) while(SZ(Q[i][j])) {
      move(i,j,Q[i][j].front(),j);
    }
  }
  
  // make delivery pool
  REP(j,M) {
    REP(i,2) {
      int need=min(0,want1[j][i]-cnt[i][j][i]);
      REP(j2,M) if(j!=j2&&need>0) {
        int red=min(0,cnt[i][j2][i]-want1[j2][i]);
        if(red>0) {
          int dt=min(red,need);
          REP(_,dt) move(i,j2,i,j);
          need-=red;
        }
      }
      assert(need==0);
      while(cnt[i][j][i]>want1[j][i]) move(i,j,i,M-1);
    }
  }
  
  // make top pool. however in stuck.
  REP(j,M)REP(i,2) {
    REP(k,B[i][j]) {
      int x=B[i][j][k]-'0';
      //REP(k,M-1,k,j);
    }
  }
  
  return -1;
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  REP(i,N)REP(j,M) {
    cin>>A[0][i][j];
    LIM+=SZ(A[0][i][j]);
  }
  REP(i,N)REP(j,M) cin>>A[1][i][j];
  solve();
  
  return 0;
}
