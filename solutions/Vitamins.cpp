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
// minmax
template<class T> inline bool SMIN(T &l,const T &r){ if(l>r)l=r;}
template<class T> inline bool SMAX(T &l,const T &r){ if(l<r)l=r;}
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
// debug cerr
#define TRACE true
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }

/*
 
 10/24/2018
 
 16:39-16:54 AC
 
 http://codeforces.com/blog/entry/61891
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e3+1;
LL P[8];
int N;

LL solve() {
  LL const Inf=1e8;
  LL res=Inf;
  REP(mask1,8){
    if(mask1==7) SMIN(res,P[mask1]);
    REP(mask2,8){
      if((mask1|mask2)==7) SMIN(res,P[mask1]+P[mask2]);
      REP(mask3,8) {
        if((mask1|mask2|mask3)==7) SMIN(res,P[mask1]+P[mask2]+P[mask3]);
//        if((mask1|mask2|mask3)==7) dump4(P[mask1],P[mask2],P[mask3],res);
      }
    }
  }
  return res>=Inf?-1:res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  REP(i,8) P[i]=1e8;
  
  cin>>N;
  REP(i,N) {
    LL p; string S; cin>>p>>S;
    int mask=0;
    REP(c,3)REP(i,SZ(S)) {
      if(S[i]=='A'+c) mask|=1<<c;
    }
    //SMIN(P[mask],p);
    P[mask]=min(P[mask],p);
//    dump3(p,mask,P[mask]);
  }
  
  cout<<solve()<<endl;
  
  return 0;
}
