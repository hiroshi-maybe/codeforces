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
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef unordered_map<int,int> MAPII;
typedef unordered_set<int> SETI;
template<class T> using VV=vector<vector<T>>;
// minmax
template<class T> inline T SMIN(T& a, const T b) { return a=(a>b)?b:a; }
template<class T> inline T SMAX(T& a, const T b) { return a=(a<b)?b:a; }
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// collection
#define ALL(c) (c).begin(),(c).end()
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// stdout
#define println(args...) fprintf(stdout, ##args),putchar('\n');

// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 11/16/2018
 
 16:43-17:41 AC
 
 https://codeforces.com/blog/entry/63199
 
 Bunch of mistakes to make a formula
  - misunderstanding of problem statement (delta is x_i)
  - confusion between addition and final result
  - mistake of addition of `0` elements
 
 Value increases uniformly.
 It's possible to compute them independently.
 Final result is integral of each contribution of each element.

 */

// 17:41 AC
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG Banh-mi.cpp && ./a.out
const LL MOD=1e9+7;
const int MAX_N=1e5+1;
string S;
int N,Q;

LL cum[MAX_N];
LL P2[MAX_N];

void solve(int l, int r) {
  LL cnt1=cum[r]-cum[l],cnt0=r-l-cnt1;
  assert(cnt1<=MAX_N&&cnt0<=MAX_N&&cnt0+cnt1==r-l);
  LL a=(P2[cnt1]+MOD-1LL)%MOD;
  LL b=a*(P2[cnt0]+MOD-1)%MOD;
//  dump3(cnt1,cnt0,a*b);
  LL res=(a+b)%MOD;
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>Q>>S;
  ZERO(cum);
  REP(i,N) cum[i+1]=cum[i]+S[i]-'0';
  
  P2[0]=1LL;
  REP(i,N) P2[i+1]=P2[i]*2LL%MOD;
  
  REP(i,Q) {
    int l,r; cin>>l>>r;
    --l;
    solve(l,r);
  }
  
  return 0;
}
