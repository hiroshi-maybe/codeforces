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
 
 7/31/2018
 
 25:10-25:35 AC
 
 N is small. Once figureing out brute-forcing four groups, it was straightforward.
 
 Editorials:
  - https://atcoder.jp/img/arc073/editorial.pdf
  - https://youtu.be/0_ztXTCTOfw?t=2148
  - https://kimiyuki.net/writeup/algo/atcoder/arc-073-d/
  - http://chakku.hatenablog.com/entry/2017/06/13/021049
  - http://prdc.hatenablog.com/entry/2017/09/08/214128
  - http://hamayanhamayan.hatenablog.jp/entry/2017/04/30/165332
  - https://ei1333.hateblo.jp/entry/2017/05/01/004235
  - http://baitop.hatenadiary.jp/entry/2018/06/26/233817
 
 Editorial video is saying that search space is at most (N/4)^4=390625
 I'm interested in how it's calculated 🤔
 I actually computed by `calcMaxSearchspace()` and found out that it's 176851<390625.
 
 Below is my guess:
 Computation happens a*b*c*(N-a-b-c) times which is maximal if they are even like a=N/4,b=N/4,c=N/4,d=N/4.
 Thus complexity is upper-bounded by (N/4)^4.
 
 Summary:
  - Implementation was a bit heavy
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
//const int MAX_N=100+1;
LL w0,W;
vector<LL> WS[4];
vector<LL> cum[4];
int N;
LL solve() {
  REP(i,4) {
    sort(WS[i].rbegin(),WS[i].rend());
    int M=SZ(WS[i]);
    cum[i].resize(M+1,0);
    REP(j,M) cum[i][j+1]=cum[i][j]+WS[i][j];
  }
  
  LL res=0;
  REPE(a,N)if(a<SZ(cum[0])) {
    REPE(b,N-a)if(b<SZ(cum[1])) {
      REPE(c,N-a-b)if(c<SZ(cum[2])) {
        REPE(d,N-a-b-c)if(d<SZ(cum[3])) {
          LL wtot=w0*a+(w0+1)*b+(w0+2)*c+(w0+3)*d;
          if(wtot>W) continue;
          SMAX(res,cum[0][a]+cum[1][b]+cum[2][c]+cum[3][d]);
        }
      }
    }
  }
  return res;
}

void calcMaxSearchspace() {
  //vector<tuple<int,int,int,int>> X;
  set<tuple<int,int,int,int,int>> S;
  REPE(a,100)REPE(b,100)REPE(c,100)REPE(d,100)if(a+b+c+d==100) {
    //    dump4(a,b,c,a*b*c);
    //    X.emplace_back(a*b*c,a,b,c);
    S.emplace(a,b,c,d);
  }
  dump(SZ(S));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>W;
  LL v0;
  cin>>w0>>v0;
  WS[0].push_back(v0);
  REP(i,N-1) {
    LL w,v;
    cin>>w>>v;
    WS[w-w0].push_back(v);
  }
  cout<<solve()<<endl;
  
  return 0;
}
