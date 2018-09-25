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
 
 9/20/2018 ER51
 
 7:35-8:05 AC
 
 http://codeforces.com/blog/entry/61969
 http://betrue12.hateblo.jp/entry/2018/09/23/191155
 
 */

// 8:05 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e2+1;
int T;
string solve(string S) {
  VI ps[3];
  char X[3]={'9','z','Z'};
  int N=SZ(S);
  REP(i,N) {
    if(isdigit(S[i])) ps[0].push_back(i);
    else if(islower(S[i])) ps[1].push_back(i);
    else ps[2].push_back(i);
  }
//  dump(SZ(ps[1]));
//  dumpAR(ps[1]);
  int cnt=0;
  REP(i,3) cnt+=SZ(ps[i])!=0;
//  dump(cnt);
  if(cnt==3) return S;
  if(cnt==1) {
    int j=0;
    REP(i,3) if(SZ(ps[i])==0) S[j++]=X[i];
    return S;
  }
  int j=-1;
  REP(i,3) if(SZ(ps[i])==0) j=i;
  REP(i,3) if(SZ(ps[i])>1) {
    S[ps[i][0]]=X[j];
    break;
  }
  return S;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>T;
  REP(i,T) {
    string s; cin>>s;
    cout<<solve(s)<<endl;
  }
  
  return 0;
}
