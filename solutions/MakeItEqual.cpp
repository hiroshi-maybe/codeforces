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
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
template<class T> using VV=vector<vector<T>>;
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
 
 10/11/2018 E52
 
 8:20-9:12 AC
 
 http://codeforces.com/blog/entry/62411
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e5+1;
LL H[MAX_N];
int N;
LL K;

LL cost(LL h) {
  LL res=0;
  REP(i,N) res+=max(0LL,H[i]-h);
  return res;
}
LL solve_wrong() {
  LL res=0;
  while(true) {
    int cnt=0;
    REP(i,N) cnt+=H[i]==H[0];
    if(cnt==N) return res;
    
    LL good=2e5+1,bad=-1;
    while(abs(good-bad)>1) {
      LL m=(good+bad)/2;
      if(cost(m)<=K) good=m;
      else bad=m;
    }
    ++res;
    REP(i,N) H[i]=min(H[i],good);
  }
  return -1;
}

LL solve() {
  sort(H,H+N);
  int r=N-1;
  LL res=0,sum=0;
  for(int i=N-2; i>=0; --i) if(H[i]<H[r]) {
    LL h1=H[i],h2=H[r];
    REP(_,h2-h1) {
      if(sum+(LL)(N-i-1)>K) {
//        dump2(sum+(N-i-1),_);
        ++res;
        sum=(N-i-1);
      } else {
        sum+=(N-i-1);
      }
    }
//    dump4(i,r,h2-h1,res);
    r=i;
    if(H[r]==H[0]) break;
  }
  if(sum>0) ++res;
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>H[i];
  cout<<solve()<<endl;
  
  return 0;
}
