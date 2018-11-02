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
 
 10/28/2018 R519 div2
 
 9:30-10:35 time is up (3WA)
 
 11/1/2018
 
 22:00-22:31 retry and got AC
 
 http://codeforces.com/blog/entry/62797
 
 */
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
LL A[10][MAX_N];
int N,M;

LL P[10][MAX_N];
LL cnt[MAX_N];

void solve() {
  REP(i,M)REP(j,N) P[i][A[i][j]]=j;
  LL res=1,l=-1,pre=A[0][0];
  FOR(i,1,N) {
    int a=A[0][i];
    bool ok=true;
//    dump3(i,pre,a);
    FOR(j,1,M) {
      int p2=P[j][a],p1=P[j][pre];
//      dump4(i,j,p1,p2);
      if(p1!=p2-1) ok=false;
    }
    if(!ok) l=i-1;
    res+=i-l;
//    dump4(l,i,i-l,res);
    pre=a;
  }
  //cout<<res<<endl;
  println("%lld",res);
}

void solve_org() {
  REP(i,M)REP(j,N) P[i][A[i][j]]=j;
  MINUS(cnt);
  REP(n,N) if(cnt[n]==-1) {
    VI pos(M); REP(i,M)pos[i]=P[i][n];
    LL l=0;
    while(true) {
      if(pos[0]+l==N) break;
      int n2=A[0][pos[0]+l];
      if(cnt[n2]>=0) {
        // merge
        l+=cnt[n2];
        cnt[n2]=0;
        break;
      }
      bool ok=true;
      REP(i,M) {
        int p=pos[i]+l;
        if(p>=N||A[i][p]!=n2) {
          ok=false;
          break;
        }
      }
      if(!ok) break;
      cnt[n2]=0;
      ++l;
    }
//    dump2(n,l);
    cnt[n]=l;
  }
  
//  dumpc(cnt,cnt+N);
  LL res=0;
  REP(n,N) if(cnt[n]>0) {
    res+=1LL*cnt[n]*(cnt[n]+1)/2LL;
  }
  cout<<res<<endl;
}

struct UF {
public:
  int groupNum;
  UF(int N) {
    uf=vector<int>(N);
    rank=vector<int>(N);
    for(int i=0; i<N; ++i) uf[i]=i,rank[i]=0;
    groupNum=N;
  }
  
  int find(int i) {
    return uf[i]==i?i:uf[i]=find(uf[i]);
  }
  
  bool same(int x, int y) {
    return find(x)==find(y);
  }
  
  void unite(int x, int y) {
    x=find(x);
    y=find(y);
    if(x==y) return;
    groupNum--;
    
    if (rank[x]==rank[y]) {
      uf[x]=y;
      rank[y]++;
      return;
    }
    
    if (rank[x]<rank[y]) {
      uf[x]=y;
    } else {
      uf[y] =x;
      if(rank[x]==rank[y]) ++rank[x];
    }
  }
private:
  vector<int> rank;
  vector<int> uf;
};

int viz[MAX_N];
void solve_wrong() {
  REP(i,M)REP(j,N) P[i][A[i][j]]=j;
  UF uf(N);
  ZERO(cnt);
  ZERO(viz);
  REP(n,N) if(!viz[n]) {
    VI pos(M); REP(i,M)pos[i]=P[i][n];
    LL l=0;
    while(true) {
      if(pos[0]+l==N) break;
      int n2=A[0][pos[0]+l];
      if(viz[n2]) {
        // merge
        uf.unite(n,n2);
        break;
      }
      bool ok=true;
      REP(i,M) {
        int p=pos[i]+l;
        if(p>=N||A[i][p]!=n2) {
          ok=false;
          break;
        }
      }
      if(!ok) break;
      viz[n2]=1;
      uf.unite(n,n2);
      ++l;
    }
//    dump2(n,l);
    cnt[n]=l;
    viz[n]=1;
  }
  
//  dumpc(cnt,cnt+N);
  LL res=0;
  MAPII G; REP(n,N) G[uf.find(n)]+=cnt[n];
  FORR(kvp,G) {
    LL x=kvp.second;
    res+=1LL*x*(x+1)/2LL;
  }
  cout<<res<<endl;
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
void test() {
  N=5, M=3;
  
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
//  test();
  
  scanf("%d %d",&N,&M);
  REP(i,M)REP(j,N){
    scanf("%lld",&A[i][j]);
    A[i][j]--;
  }
  solve();
  
  return 0;
}
