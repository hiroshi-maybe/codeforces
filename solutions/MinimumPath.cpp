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
typedef pair<int,int> II;
typedef long long LL;
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
 
 10/28/2018
 
 14:35-15:55 give up
 
 Tons of mistakes in analysis. ARE YOU CRAZYYYYYYYY? 🖕🖕🖕🖕🖕🖕🖕🖕🖕🖕
  - missing analysis of `a` prefix case
  - missing analysis of intermediate `a` case
  - poor and slow implementation
 
 23:20-24:20 read editorial and got AC
 
 http://codeforces.com/blog/entry/62612
 
 Basic idea to consume `K` greedily in former cells.
 However I missed a case that `a` is coming later like `azzzazz` because I'm stupid.
 
 */

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=2e3+1;
string A[MAX_N];
int N,K;

const int Inf=1e8;
int dp[MAX_N][MAX_N];
void solve() {
  REP(i,N)REP(j,N) dp[i][j]=Inf;
  dp[0][0]=(A[0][0]!='a');
  REP(i,N)REP(j,N) {
    REP(dr,2)REP(dc,2)if((dr^dc)==1) {
      int ii=i+dr,jj=j+dc;
      if(ii<N&&jj<N) {
        SMIN(dp[ii][jj],dp[i][j]+(A[ii][jj]!='a'));
      }
    }
  }
  int maxd=-1;
  queue<II> Q;
  REP(i,N)REP(j,N)if(dp[i][j]<=K) SMAX(maxd,i+j);
  REP(i,N)REP(j,N)if(dp[i][j]<=K&&i+j==maxd) Q.emplace(i,j);
  string res(maxd+1,'a');
  if(Q.empty()) {
    res=string(1,A[0][0]);
    Q.emplace(0,0);
  }
  while(SZ(Q)) {
    int L=SZ(Q);
    char minc='~';
    set<II> S;
    REP(_,L) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      REP(dr,2)REP(dc,2)if((dr^dc)==1) {
        int ii=i+dr,jj=j+dc;
        if(ii<N&&jj<N) {
          if(minc==A[ii][jj]) S.emplace(ii,jj);
          else if(minc>A[ii][jj]) {
            S.clear();
            S.emplace(ii,jj);
            minc=A[ii][jj];
          }
        }
      }
    }
//    dump2(L,minc);
    if(SZ(S)) res+=minc;
    FORR(p,S) Q.emplace(p);
  }
  cout<<res<<endl;
}

int viz[MAX_N][MAX_N]={};
void solve_wrong() {
  queue<II> Q;
  if(A[0][0]=='a') Q.emplace(0,0),viz[0][0]=1;;
  while(SZ(Q)) {
    int i,j; tie(i,j)=Q.front(); Q.pop();
    REP(dr,2)REP(dc,2)if((dr^dc)==1) {
      int ii=i+dr,jj=j+dc;
      if(ii<N&&jj<N&&!viz[i][j]&&A[i][j]=='a') {
        Q.emplace(ii,jj);
        viz[ii][jj]=true;
      }
    }
  }
  int maxd=-1;
  REP(i,N)REP(j,N) if(viz[i][j])SMAX(maxd,i+j);
  REP(i,N)REP(j,N) if(viz[i][j]&&i+j==maxd) Q.emplace(i,j);
  dump4(maxd,maxd+K,2*N-1,maxd+K>=2*N-1);
  
  if(maxd+K>=2*N-1||(maxd<0&&K>=2*N-1)) {
    string res(2*N-1,'a');
    cout<<res<<endl;
    return;
  }

  set<II> S;
  int L=SZ(Q);
  REP(_,L) {
    int i,j; tie(i,j)=Q.front(); Q.pop();
//    dump2(i,j);
    REPE(dr,K) {
      int ii=i+dr,jj=j+K-dr;
      if(ii<N&&jj<N) S.emplace(ii,jj);
    }
  }
  FORR(s,S) dump2(s.first,s.second);
  FORR(p,S) Q.emplace(p);
  if(Q.empty()) {
    REP(i,N)REP(j,N) if(i+j==K-1) {
      Q.emplace(i,j);
      dump2(i,j);
    }
  }
  string res="";
  while(SZ(Q)) {
    int L=SZ(Q);
    char minc='~';
    set<II> S;
    REP(_,L) {
      int i,j; tie(i,j)=Q.front(); Q.pop();
      REP(dr,2)REP(dc,2)if((dr^dc)==1) {
        int ii=i+dr,jj=j+dc;
        if(ii<N&&jj<N) {
          if(minc==A[ii][jj]) S.emplace(ii,jj);
          else if(minc>A[ii][jj]) {
            S.clear();
            S.emplace(ii,jj);
            minc=A[ii][jj];
          }
        }
      }
    }
    dump2(L,minc);
    if(SZ(S)) res+=minc;
    FORR(p,S) Q.emplace(p);
  }
  string ans(maxd+1+K,'a');
  ans+=res;
  cout<<ans<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
