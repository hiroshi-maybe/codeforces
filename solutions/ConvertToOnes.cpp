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
 
 7/1/2018 R493 Div2 C
 
 23:35-24:17 AC
 
 7/27/2018
 
 Read editorials and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/60357
  - https://natsugiri.blogspot.com/2018/07/3.html
 
 Tweets:
  - https://togetter.com/li/1242766
  - https://twitter.com/kuuso1/status/1013455399687557120
  - https://twitter.com/hamko_intel/status/1013454054729478144
  - https://twitter.com/n_vip/status/1013454420812500993
 
 By one operation, group of 0s can be reduced by one.
 (replacing 1s with 0s does not seem to be optimal)
 It's applicable regardless operation types.
 However the last operation should be flip.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=3e5+1;
// 23:52 1WA
// 24:17 passed
int N;
LL R,I;
string S;
vector<int> X;

LL f() {
  X.clear();
  int cur=0;
  REP(i,N) {
    char c=S[i];
    if(c=='1') {
      if(cur>0) X.push_back(cur);
      cur=0;
    } else {
      ++cur;
    }
  }
  if(cur) X.push_back(cur);
  
  int M=SZ(X);
  LL res=M*I;
  REP(i,M) {
    LL x=1LL*(M-i)*I+1LL*i*min(R,I);
    SMIN(res,x);
  }
  return res;
}

LL solve_org() {
  LL res=f();
  REP(i,N) S[i]=(S[i]=='0'?'1':'0');
  SMIN(res,f()+I);
  return res;
}

LL solve() {
  int g=0;
  REP(i,N-1) g+=S[i]=='0'&&S[i+1]=='1';
  if(S[N-1]=='0') ++g;
//  dump(g);
  if(g==0) return 0;
  return (g-1)*min(R,I)+I;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>R>>I>>S;
  
  LL res=solve();
  cout<<res<<endl;
  
  return 0;
}
