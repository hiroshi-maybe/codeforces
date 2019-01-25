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

// $ cp-batch AlmostRegularBracketSequence | diff AlmostRegularBracketSequence.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AlmostRegularBracketSequence.cpp && ./a.out

/*
 
 1/24/2019
 
 17:06-17:49 AC
 
 https://codeforces.com/blog/entry/64130
 https://betrue12.hateblo.jp/entry/2018/12/28/152148
 
 */

const int MAX_N=1e6+1;
string S;
int N;

int cum[MAX_N];
int ok1[MAX_N][2],ok2[MAX_N];
void solve() {
  cum[0]=0;
  int bal=0;
  REP(i,N) {
    bal+=S[i]=='('?1:-1;
    cum[i+1]=bal;
  }
  ok1[N][0]=ok1[N][1]=1;
  for(int i=N; i>0; --i) {
    ok1[i-1][0]=ok1[i][0]&&cum[i]>=2;
    ok1[i-1][1]=ok1[i][1]&&cum[i]>=-2;
  }
  ok2[0]=true;
  REP(i,N) ok2[i+1]=ok2[i]&&cum[i+1]>=0;
  int res=0;
  REP(i,N) {
    if(S[i]=='(') {
//      dump4(i,bal-2==0,ok1[i][0],ok2[i]);
      res+=(bal-2==0&&ok1[i][0]&&ok2[i]);
    } else {
//      dump4(i,bal+2==0,ok1[i][1],ok2[i]);
      res+=(bal+2==0&&ok1[i][1]&&ok2[i]);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>S;
  solve();
  
  return 0;
}
