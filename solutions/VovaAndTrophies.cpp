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

// $ ../batch VovaAndTrophies | diff VovaAndTrophies.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address VovaAndTrophies.cpp && ./a.out

/*
 
 12/20/2018
 
 15:32-16:10 AC
 
 https://codeforces.com/blog/entry/63544
 
 Counting # of connected components is complex.
 Simply comparing with total number makes things simpler.
 
 Summary:
  - Huge loss of time due to missing analysis of GGGGGSSSGGGG (# of intermediate S >1)
  - If we are interested in a case with # of connected component, compare with total number as shown in editorial
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
LL L[MAX_N],R[MAX_N];
int N;
string S;

int solve() {
  int totG=count(ALL(S),'G');
  REP(i,N) if(S[i]=='G') {
    L[i]=1;
    if(i>0) L[i]+=L[i-1];
  }
  for(int i=N-1; i>=0; --i) if(S[i]=='G') {
    R[i]=1;
    if(i<N-1) R[i]+=R[i+1];
  }
  int res=0;
  REP(i,N) if(S[i]=='S') {
    int l=0,r=0;
    if(i>0) l=L[i-1];
    if(i<N-1)r=R[i+1];
    SMAX(res,l+r+1);
  }
  SMIN(res,totG);
  if(N==totG) res=totG;
  return res;
}

int solve_my_cumbersome() {
  S="S"+S+"S";
  N+=2;
  int res=0,cs=0;
  REP(i,N) if(S[i]=='S') {
    int cnt=0,j=i+1;
    while(j<N&&S[j]=='G') ++j,++cnt;
    if(cnt>0) ++cs;
    SMAX(res,cnt);
  }
  if(cs==2) {
    REP(i,N) if(S[i]=='S') {
      int l=0,r=0;
      int j=i-1;
      while(j>=0&&S[j]=='G') --j,++l;
      j=i+1;
      while(j<N&&S[j]=='G') ++j,++r;
      
      if(l==0&&r==0) continue;
      if(l==0||r==0) SMAX(res,max(l,r)+1);
      else SMAX(res,l+r);
    }
    
  } else if(cs>2) {
    REP(i,N) if(S[i]=='S') {
      int l=0,r=0;
      int j=i-1;
      while(j>=0&&S[j]=='G') --j,++l;
      j=i+1;
      while(j<N&&S[j]=='G') ++j,++r;
      SMAX(res,l+r+1);
    }
  }
  return res;
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
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  VI ss=genRandSeq(10,0,2);
  S="";
  REP(i,SZ(ss)) S.push_back(ss[i]?'G':'S');
  N=SZ(ss);
  
  int res=0;
  REP(i,N)FOR(j,i+1,N) {
    swap(S[i],S[j]);
    int x=0;
    REP(k,N) {
      if(S[k]=='G') x+=1;
      else SMAX(res,x),x=0;
    }
    swap(S[i],S[j]);
    SMAX(res,x);
  }
  int res2=solve();
  if(res!=res2) dump3(S,res,res2);
  assert(res==res2);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>S;
  int res=solve();
  cout<<res<<endl;
  
  return 0;
}
