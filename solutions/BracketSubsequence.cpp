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
 
 7:15-8:36 AC
 
 Editorials:
  - http://codeforces.com/blog/entry/61356
  - http://betrue12.hateblo.jp/entry/2018/08/18/181413
 
 Tweets:
  - https://togetter.com/li/1257672
  - https://twitter.com/_olphe/status/1030498603704283137
  - https://twitter.com/my316g/status/1030503849453178881
  - https://twitter.com/natsugir/status/1030533897753219072
  - https://twitter.com/satanic0258/status/1030501797536784384
 
 */

// 8:36 submit
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=1e5+1;
int N,K;
string S;
void solve() {
  stack<int> ST;
  vector<II> X;
  REP(i,N) {
    if(S[i]=='(') ST.push(i);
    else {
      assert(SZ(ST));
      int l=ST.top(); ST.pop();
      X.emplace_back(l,i);
    }
  }
  assert(ST.empty());
  assert(SZ(X)==N/2);
  assert(SZ(X)>=(N-K)/2);
  REP(i,(N-K)/2) {
    int l,r; tie(l,r)=X[i];
    S[l]='#',S[r]='#';
  }
  string res="";
  REP(i,N) if(S[i]!='#') res+=S[i];
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K>>S;
  solve();
  return 0;
}
