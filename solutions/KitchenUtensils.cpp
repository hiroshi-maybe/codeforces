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
 
 11/19/2018
 
 11:52-12:14 AC
 
 https://codeforces.com/blog/entry/63324
 
 max count <= d*K <=> d >= max count / K (K!=0)
 
 */

// $ ../batch KitchenUtensils | diff KitchenUtensils.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KitchenUtensils.cpp && ./a.out
const int MAX_N=1e5+1;
int A[MAX_N];
int N,K;

void solve() {
  map<int,int> M;
  int mcnt=0;
  REP(i,N) ++M[A[i]];
  //  FORR(kvp,M) dump2(kvp.first,kvp.second);
  FORR(kvp,M) SMAX(mcnt,kvp.second);
  
  int S=SZ(M);
  int d=(mcnt+K-1)/K;
  cout<<S*d*K-N<<endl;
}


void solve_org() {
  int res=1e6;
  map<int,int> M;
  int mcnt=0;
  REP(i,N) ++M[A[i]];
//  FORR(kvp,M) dump2(kvp.first,kvp.second);
  FORR(kvp,M) SMAX(mcnt,kvp.second);
  
  int S=SZ(M);
//  dump2(mcnt,S);
  REPE(d,1e2+10) if(mcnt<=d*K) {
    int rem=S*d*K-N;
//    dump2(d,rem);
    SMIN(res,rem);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  
  solve();
  
  return 0;
}
