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
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
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
 
 5/30/2018 R478 div2
 
 17:22-18:30 give up and add solution
 
 Editorials:
  - http://codeforces.com/blog/entry/59202
  - http://noimin.hatenablog.com/entry/2018/05/02/194924
  - http://kmjp.hatenablog.jp/entry/2018/05/02/0900
 
 */

// $ g++ -std=c++11 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=200000+1;
int X[MAX_N],V1[MAX_N],V2[MAX_N];
int N;
LL A,B;

int gcd(int a, int b) { return b==0?a:a%b; }

LL solve() {
  map<LL,LL> vm1;
  map<pair<LL,LL>,LL> vm2;
  REP(i,N) {
    vm1[A*V1[i]-V2[i]]++;
    vm2[{V1[i],V2[i]}]++;
  }
  LL res=0;
  FORR(kvp,vm1) res+=kvp.second*(kvp.second-1);
  FORR(kvp,vm2) res-=kvp.second*(kvp.second-1);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>A>>B;
  REP(i,N) {
    int v1,v2;
    cin>>X[i]>>v1>>v2;
    /*
    bool neg=false;
    if(v1<0&&v2>0) neg=true;
    if(v1>0&&v2<0) neg=true;
    v1=abs(v1),v2=abs(v2);
    if(v1==0&&v2!=0) v2=1;
    if(v2==0&&v1!=0) v1=1;
    int g=gcd(v1,v2);
    if(g!=0) v1/=g,v2/=g;
    if(neg) v1=-v1;*/
    V1[i]=v1,V2[i]=v2;
  }
  
  cout<<solve()<<endl;
  
  return 0;
}
