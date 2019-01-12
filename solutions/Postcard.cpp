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

// $ ../batch Postcard | diff Postcard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Postcard.cpp && ./a.out

/*
 
 1/5/2019
 
 9:02-9:40 system test failed
 13:35-13:43 looked at failed test case and fixed a bug
 
 https://codeforces.com/blog/entry/64331
 
 */

int K;
string S;

void nope() {
  println("Impossible");
  exit(0);
}

void solve() {
  int N=SZ(S);
  vector<string> X(N,"");
  int len=0;
  REP(i,N) {
    if(S[i]=='*') X[i-1]="",--len;
    else if(S[i]=='?') X[i-1]="",--len;
    else X[i]=string(1,S[i]),++len;
    dump2(i,len);
  }
  dump(len);
  if(len>K) nope();
  int cnta=count(ALL(S),'*'),cntq=count(ALL(S),'?');
  dump4(S,K,cnta,cntq);
  if(cnta>0&&K>len) {
    int p=-1; REP(i,N) if(S[i]=='*') { p=i; break; }
    X[p-1]=string(1,S[p-1]),len++;
    dump(len);
    X[p]=string(K-len,S[p-1]),len+=K-len;
  } else {
    REP(i,N) if(len<K&&(S[i]=='*'||S[i]=='?')) {
      X[i-1]=string(1,S[i-1]);
      len++;
    }
  }
  if(len<K) nope();
  string res;
  REP(i,N) res+=X[i];
  if(SZ(res)!=K) dump3(K,SZ(res),res);
  assert(SZ(res)==K);
  cout<<res<<endl;
}
/*
void solve_() {
  int cnta=count(ALL(S),'*'),cntq=count(ALL(S),'?');
  int N=SZ(S);
  if(K<N-2*cnta-2*cntq) nope();
  
  string T;
  if(cnta>0) {
    bool added=false;
    REP(i,N) {
      if(S[i]=='?') T.pop_back();
      else if(S[i]=='*') {
        if(!added) {
          char c=T.back();
          REP(_,K-(N-2*cntq-cnta)) T.push_back(c);
          added=true;
        }
      } else {
        T.push_back(S[i]);
      }
    }
  } else if(cntq>0) {
    
  } else {
    
  }
  assert(SZ(T)==K);
  cout<<T<<endl;
}*/

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S>>K;
  solve();
  
  return 0;
}
