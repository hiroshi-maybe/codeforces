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
 
 8/19/2018
 
 7:18-7:46 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61323
  - http://kmjp.hatenablog.jp/entry/2018/08/20/0900
  - http://betrue12.hateblo.jp/entry/2018/08/20/212528
 
 Tweets:
  - https://togetter.com/li/1258285
  - https://twitter.com/satanic0258/status/1031208997158772737
  - https://twitter.com/beet_aizu/status/1031206813071339521
  - https://twitter.com/Yazaten/status/1031208986035384320
 
 Key:
  - operation is just a rotation and reverse
 
 Summary:
  - nice to figure out that operation is equal to rotation 👍
 
 */

// 7:46 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N;
//LL A[MAX_N];
vector<int> A;
void solve() {
  VI B(2*N,0);
  REP(i,N) B[i]=A[i],B[i+N]=A[i];
//  dumpAR(A);
//  dumpAR(B);
  int res=0;
  int cur=0;
  REP(i,2*N) {
    if(i==0||B[i]!=B[i-1]) ++cur,res=SMAX(res,cur);
    else cur=1;
  }
  SMIN(res,N);
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  string S;
  cin>>S;
  N=SZ(S);
  A.resize(N);
  REP(i,N) A[i]=S[i]=='w';
  solve();
  return 0;
}
