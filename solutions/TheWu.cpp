#include <iostream>
#include <iomanip>
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
 
 8/8/2018 R502
 
 9:02-10:20 submit and TLEed
 10:35-10:45 TLE again
 11:58 got AC by `scanf`
 
 Editorials:
  - https://codeforces.com/blog/entry/61081
   - half brute-force
  - https://twitter.com/satanic0258/status/1027237112712593408
  - http://betrue12.hateblo.jp/entry/2018/08/11/155320
 
 */

// 10:20 submit and TLE
// 10:35-10:45 TLE again
// 23:58 AC by removing ios_base::sync_with_stdio(false),cin.tie(0); FUCK
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=12;
int N;
//MAPII MM;
int MM[1<<MAX_N]={};
int W[MAX_N];

//int cum[1<<MAX_N][102];
int bs[1<<MAX_N][102]={};

int qr(int t, int k) {
  //  dump3(t,k,cum[t][k+1]);
  //return bs[t].query(k);
  //return cum[t][k+1];
  return bs[t][k];
}

void solve() {
  REP(mask,1<<N) {
    REP(s,1<<N) {
      int score=0;
      int cnt=MM[s];
      REP(i,N) if(((mask>>i)&1)==((s>>i)&1)) score+=W[i];
      if(score<=100)bs[mask][score]+=cnt;
      //      dump4(mask,s,score,cnt);
    }
    //    cum[mask][0]=0;
    //    REPE(i,100)cum[mask][i+1]=cum[mask][i]+bs[mask][i];
    FORE(i,1,100)bs[mask][i]+=bs[mask][i-1];
  }
}

int main() {
//  ios_base::sync_with_stdio(false);
//  cin.tie(0);
  
  int M,Q;
  cin>>N>>M>>Q;
  REP(i,N)scanf("%d",&W[i]); //cin>>W[i];
  char s[MAX_N];
  REP(i,M) {
//    string s; cin>>s;
    scanf("%s",s);
    int x=0;
    REP(i,N) if(s[i]=='1') x+=(1<<i);
    MM[x]++;
  }
  solve();
  REP(i,Q) {
    scanf("%s",s);
    int K; scanf("%d",&K);
//    int K; string s; cin>>s>>K;
    int x=0;
    REP(i,N) if(s[i]=='1') x|=(1<<i);
//    cout<<qr(x,K)<<endl;
    printf("%d\n",qr(x,K));
  }
  
  return 0;
}
