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
 
 9:35-9:48 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61493
 
 Tweets:
  - https://togetter.com/li/1261045
  - https://twitter.com/satanic0258/status/1034153506381258755
 
 Summary:
  - looks like I was misunderstanding the problem. There is only ONE square in the grid...
 
 */

// 9:48 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG FindSquare.cpp && ./a.out
//const int MAX_N=115+10;
int N,M;
vector<vector<int>> A;

struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};

void solve_org() {
  TwoDimCumSum cum(A);
  REP(i,N)REP(j,M) {
    int ii=-1,jj=-1;
    for(int l=1; l<=min(N,M); l+=2) {
      if(i+l>N) continue;
      if(j+l>M) continue;
      if(cum.query(i,j,i+l,j+l)==l*l) {
//        dump3(i,j,cum.query(i,j,i+l,j+l));
        ii=(i+(i+l))/2,jj=(j+(j+l))/2;
      }
    }
    if(ii!=-1&&jj!=-1) {
      cout<<ii+1<<" "<<jj+1<<endl;
      return;
    }
  }
  assert(false);
}

const int Inf=1e6;
void solve() {
  int x1=Inf,y1=Inf,x2=-1,y2=-1;
  REP(i,N)REP(j,M) if(A[i][j]) {
    SMIN(x1,i),SMAX(x2,i);
    SMIN(y1,j),SMAX(y2,j);
  }
  int x=(x1+x2)/2+1,y=(y1+y2)/2+1;
  cout<<x<<" "<<y<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M;
  A.resize(N,VI(M,0));
  REP(i,N)REP(j,M) {
    char c; cin>>c;
    A[i][j]=c=='B';
  }
  solve();
  return 0;
}
