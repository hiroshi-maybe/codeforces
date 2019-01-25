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

// $ cp-batch ArrayStabilization | diff ArrayStabilization.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ArrayStabilization.cpp && ./a.out

/*
 
 1/24/2019
 
 13:54-14:04 AC
 
 https://codeforces.com/blog/entry/64130
 https://betrue12.hateblo.jp/entry/2018/12/28/152148
 https://mumumucoder.hatenablog.com/entry/2018/12/28/015653
 
 Sort and return min(A[N-1]-A[1],A[N-2]-A[0]) is smart
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int cnt[MAX_N];
void solve_org() {
  REP(i,N)cnt[A[i]]++;
  int l=MAX_N,r=-1;
  REP(i,MAX_N)if(cnt[i]) SMIN(l,i),SMAX(r,i);
  dump2(l,r);
  
  int res=MAX_N;
  cnt[l]--;
  int ll=MAX_N,rr=-1;
  REP(i,MAX_N)if(cnt[i]) SMIN(ll,i),SMAX(rr,i);
  dump2(ll,rr);
  SMIN(res,rr-ll);
  cnt[l]++,cnt[r]--;
  ll=MAX_N,rr=-1;
  REP(i,MAX_N)if(cnt[i]) SMIN(ll,i),SMAX(rr,i);
  dump2(ll,rr);
  SMIN(res,rr-ll);
  cout<<res<<endl;
}

void solve() {
  sort(A,A+N);
  cout<<min(A[N-1]-A[1],A[N-2]-A[0])<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
