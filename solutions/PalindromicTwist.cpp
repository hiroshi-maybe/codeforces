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
 
 8/18/2018
 
 7:35-7:47 AC
 
 Necessary and sufficient condition:
  - distance of chars is 0 or 2
 
 Editorial:
  - http://codeforces.com/blog/entry/61311
  - http://betrue12.hateblo.jp/entry/2018/08/19/182014
 
 Summary:
  - my implementation is clumsy. Distance is clean.
 
 */

// 7:47 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
VI f(char c) {
  VI res;
  for(int d=-1; d<=1; d+=2) {
    int x=c-'a'+d;
    if(0<=x&&x<26) res.push_back(x);
  }
  return res;
}
bool solve_org(string S, int N) {
  int l=0,r=N-1;
  while(l<r) {
    VI a=f(S[l]),b=f(S[r]);
    bool ok=false;
    REP(i,SZ(a)) REP(j,SZ(b)) ok|=a[i]==b[j];
    if(!ok) return false;
    ++l,--r;
  }
  return true;
}

bool solve(string S, int N) {
  int l=0,r=N-1;
  while(l<r) {
    int x=abs(S[l]-S[r]);
    if(x!=0&&x!=2) return false;
    ++l,--r;
  }
  return true;
}

const string yes="YES",no="NO";
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  int T; cin>>T;
  REP(i,T) {
    int N; cin>>N;
    string S; cin>>S;
    cout<<(solve(S,N)?yes:no)<<endl;
  }
  return 0;
}
