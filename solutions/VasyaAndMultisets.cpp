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
 
 9/20/2018
 
 8:17-8:48 AC
 
 http://codeforces.com/blog/entry/61969
 http://betrue12.hateblo.jp/entry/2018/09/23/191155
 
 */

// 8:48 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N;
LL A[MAX_N];
const string yes="YES",no="NO";
void end() {
  cout<<no<<endl;
  exit(0);
}
void solve() {
  MAPII M;
  REP(i,N) M[A[i]]++;
  int cnt[4]={};
  FORR(kvp,M) {
    if(kvp.second<=2) cnt[kvp.second]++;
    else cnt[3]++;
  }
  if(cnt[1]%2==1&&cnt[3]==0) end();
  
  char C[2]={'A','B'};
  int g=0;
  string S(N,'?');
  
  if(cnt[1]%2==0) {
    REP(i,N) {
      if(M[A[i]]==1) {
        S[i]=C[g],g^=1;
      } else {
        S[i]=C[0];
      }
    }
  } else {
    bool done=false;
    REP(i,N) {
      if(M[A[i]]==1) {
        S[i]=C[g],g^=1;
      } else if(M[A[i]]==2) {
        S[i]=C[0];
      } else {
        if(done) S[i]=C[0];
        else {
          S[i]=C[1];
          done=true;
        }
      }
    }
  }
  cout<<yes<<endl;
  cout<<S<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  return 0;
}
