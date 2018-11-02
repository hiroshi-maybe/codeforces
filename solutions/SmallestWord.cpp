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
 
 10/28/2018 R519 div2
 
 9:03-9:28 AC
 
 http://codeforces.com/blog/entry/62797
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
int N;
string S;

void solve() {
  N=SZ(S);
  VI res(N,0);
  int x=0;
  REP(i,N-1) if(S[i]!=S[i+1]) {
    if(x<2)++x;
    if(x==2) {
      res[i]=1;
      reverse(S.begin(),S.begin()+i+1);
    }
  }
  if(S[0]=='b'&&S[N-1]=='a') {
    res[N-1]=1;
    reverse(S.begin(),S.begin()+N);
  }
  
//  dump(S);
  int p=-1;
  REP(i,N-1) if(S[i]!=S[i+1]) { p=i; break; }
  if(p>-1) REP(i,N) assert(S[i]==(i<=p?'a':'b'));
  
  REP(i,N) cout<<res[i]<<(i==N-1?'\n':' ');
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}

void test() {
  while(true) {
  S=string(10,'a');
  REP(i,10) if(genRandNum(0,2)==1)S[i]='b';
  dump(S);
  solve();
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  cin>>S;
  solve();
  
  return 0;
}
