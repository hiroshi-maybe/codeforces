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
 
 8/17/2018
 
 7:35-7:56 AC
 
 Editorials:
  - http://betrue12.hateblo.jp/entry/2018/08/18/181413
 
 Tweets:
  - https://togetter.com/li/1257672
  - https://twitter.com/hamko_intel/status/1030501408347320320
  - https://twitter.com/satanic0258/status/1030501797536784384
 
 Clean implementation by @Egor: http://codeforces.com/contest/1023/submission/41686667
 
 Summary:
  - I need more speed for better rating
  - Narrow down conditions more efficiently
   - * exists
   - pattern is too long
   - compare left and right
 
 */

// 7:56 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N,M;
string S,T;
bool solve_org() {
  if(N>M+1) return false;
  int l=0;
  while(l<N&&S[l]!='*') ++l;
  if(l==N) return S==T;
  if(l>M) return false;
//  dump(l);
  REP(i,l) if(S[i]!=T[i]) {
//    dump3(i,S[i],T[i]);
    return false;
  }
  REP(d,N-l-1) if(S[N-d-1]!=T[M-d-1]) {
//    dump3(d,S[N-d-1],T[M-d-1]);
    return false;
  }
  return true;
}

bool solve() {
  int l=0;
  while(l<N&&S[l]!='*') ++l;
  if(l==N) return S==T;
  if(N>M+1) return false;
  string x=S.substr(0,l),y=S.substr(l+1,N-l-1);
  string L=T.substr(0,l),R=T.substr(M-(N-l-1),N-l-1);
  return x==L&&y==R;
}

const string yes="YES", no="NO";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>M>>S>>T;
  cout<<(solve()?yes:no)<<endl;
  return 0;
}
