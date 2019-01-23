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

// $ cp-batch GameWithString | diff GameWithString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GameWithString.cpp && ./a.out

/*
 
 1/22/2019
 
 6:41-7:07 AC
 
 https://misteer.hatenablog.com/entry/CF534
  - Parenthesis pairing
 https://codeforces.com/blog/entry/64722
 
 */

const int MAX_N=1e6+1;
int N;
string S;
void solve() {
  stack<char> st;
  int N=SZ(S);
  int p=0;
  REP(i,N) {
    if(st.empty()||S[i]!=st.top()) st.emplace(S[i]);
    else st.pop(),p^=1;
  }
  cout<<(p?"Yes":"No")<<endl;
}
int viz[MAX_N];
void solve_wrong() {
  ZERO(viz);
  queue<II> Q;
  int N=SZ(S);
  REP(i,N-1) if(viz[i]==0&&viz[i+1]==0&&S[i]==S[i+1]) {
    viz[i]=viz[i+1]=1;
    Q.emplace(i,i+1);
  }
  dump(SZ(Q));
  int p=0;
  while(SZ(Q)) {
    int l,r; tie(l,r)=Q.front(); Q.pop();
//    dump3(l,r,p);
    l=l-1,r=r+1;
    if(l<0) {
      l=2;
      while(l<N&&viz[l]) ++l;
      r=l+1;
      while(r<N&&viz[r]) ++r;
    }
    if(r>=N) {
      r=N-3;
      while(r>=0&&viz[r]) --r;
      l=r-1;
      while(l>=0&&viz[l]) --l;
    }
    dump2(l,r);
    if(l>=0&&l<N&&r>=0&&r<N&&viz[l]==0&&viz[r]==0&&S[l]==S[r]) {
      Q.emplace(l,r);
      viz[l]=viz[r]=1;
    }
    p^=1;
  }
  cout<<(p?"Yes":"No")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S;
  solve();
  
  return 0;
}
