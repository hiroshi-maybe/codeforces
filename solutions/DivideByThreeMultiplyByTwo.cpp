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
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 5/7/2018 Codeforces #479 div3
 
 23:45-24:20 AC
 
 Editorial:
  - http://codeforces.com/blog/entry/59281
  - http://tancahn2380.hatenablog.com/entry/2018/05/09/045313
 
 Key:
  - if it's guaranteed that solution exists, just sort by exponential which divides by 3^x works
  - two properties needs to be found to solve in simple way
   - if `a` is divisible like 3^x|a, `a` stays left for larger `x`
   - Tie break is larger `a`
 
 Summary:
  - I solved by reducing to graph problem though, editorial solution is very simple 🤔
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=100;
LL A[MAX_N];
int N;
int viz[MAX_N];
// 23:45-24:20 AC
void solve() {
  sort(A,A+N);
  vector<vector<LL>> X;
  ZERO(viz);
  
  REP(i,N) if(!viz[i]) {
    vector<LL> Y(1,A[i]); viz[i]=true;
    FOR(j,i+1,N) if(!viz[j]&&A[j]==Y.back()*2) Y.push_back(A[j]),viz[j]=true;
    if(SZ(Y)){
      X.push_back(Y);
//      dumpAR(Y);
    }
  }
  
  vector<int> S;
  int M=SZ(X);
//  dump(M);
  REP(s,M) {
    S.clear();
    S={s};
    ZERO(viz);
    viz[s]=true;
    while(SZ(S)<M) {
      bool ok=false;
      REP(i,M) if(!viz[i]&&X[i].front()*3==X[S.back()].back()) {
        S.push_back(i);
        viz[i]=true;
        ok=true;
        break;
      }
      if(!ok) goto next;
//      dumpAR(S);
    }
    if(SZ(S)==M) break;
  next: 1;
  }
  
  REP(i,SZ(S)) REP(j,SZ(X[S[i]])) {
    cout<<X[S[i]][j];
    if(i!=N-1||j!=SZ(X[S[i]])-1) cout<<" ";
  }
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}

// 1. more precision in double in iostream
// cout<<setprecision(12)<<fixed;
