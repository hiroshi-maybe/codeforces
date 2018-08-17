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
 
 8/13/2018 R503
 
 7:42-9:10 got AC
 
 I designed very complex algorithm.
 Make `M` priority queues and greedily take
 
 Editorials:
  - https://codeforces.com/blog/entry/61161
  - http://betrue12.hateblo.jp/entry/2018/08/12/155016
  - https://www.hamayanhamayan.com/entry/2018/08/12/082702
  - https://kimiyuki.net/writeup/algo/codeforces/1019-a/
  - https://twitter.com/ei1333/status/1028303878826016768
  - https://twitter.com/satanic0258/status/1028306722455080960
 
 O(N^2) works. So we can brute-force something.
 If P_1 gets `x`, P_i (i!=1) should get at most `x-1`.
 This is very strong property. We should try to satisfy this.
 Note that P_1 may not get `x` even if others have `x-1`.
 In such a case, we should take cheapest missing voites to truely "win".
 
 Key:
  - N is small. Brute-force (fix) something
  - If P_1 has `x`. Others should have at most `x-1`
 
 Summary:
  - I should have started brute-forcing something to afford O(N^2) or O(N^2*lg N) algorithm
  - If at least `x` votes of P_1 is fixed, we can greedily determine what votes should be bought.
 
 */

// 9:10 submit and AC

// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=1e5+1;
int N,M=0,MM=0;
tuple<LL,int,int> A[MAX_N];
priority_queue<pair<LL,int>,vector<pair<LL,int>>,greater<pair<LL,int>>> Q[MAX_N];
int viz[MAX_N];
int cnt=0;
//const LL Inf=1e16;
void solve_org() {
  sort(A,A+M);
  ZERO(viz);
  vector<pair<LL,int>> X(M);
  REP(i,M) {
    LL cost; int p,id; tie(cost,p,id)=A[i];
    Q[p].emplace(cost,id);
    X[i]={cost,id};
//    dump3(p,cost,id);
  }
  int maxn=0;
  REP(i,N) SMAX(maxn,SZ(Q[i]));
  LL res=0;
//  dump4(maxn,cnt,maxn-cnt+1,max(0,maxn-cnt+1));
  REP(i,max(0,maxn-cnt+1)) {
    res+=get<0>(X[i]);
  }
//  dump2(cnt,res);
  LL cost=0;
  while(true) {
//    dump3(cnt,cost,N);
    maxn=0;
    REP(i,N) SMAX(maxn,SZ(Q[i]));
    if(maxn<cnt) break;
    int x=-1;
    REP(i,N) if(SZ(Q[i])==maxn) {
      if(x==-1||(SZ(Q[i])&&Q[x].top().first>Q[i].top().first)) x=i;
    }
//    dump2(x,maxn);
    assert(x!=-1);
    cost+=Q[x].top().first; viz[Q[x].top().second]=1; Q[x].pop();
    maxn=0;
    REP(i,N) SMAX(maxn,SZ(Q[i]));
    cnt++;
    int cnt2=cnt; LL cost2=cost;
    for(int i=0; i<M&&cnt2<=maxn; ++i) if(!viz[get<1>(X[i])]) {
      cnt2+=1;
      cost2+=get<0>(X[i]);
    }
    SMIN(res,cost2);
  }
  cout<<res<<endl;
}

void solve() {
  sort(A,A+M);
  LL res=1e14;
  REPE(x,MM) {
    int a=cnt;
    vector<LL> P(N,0);
    priority_queue<LL,vector<LL>,greater<LL>> Q;
    REP(i,M) P[get<1>(A[i])]++;
    LL sum=0;
    REP(i,M) {
      LL cost; int p,id; tie(cost,p,id)=A[i];
      if(P[p]<x) Q.emplace(cost);
      else {
        sum+=cost;
        P[p]--;
        ++a;
      }
    }
    while(a<x) {
      sum+=Q.top(); Q.pop();
      ++a;
    }
    SMIN(res,sum);
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  
  cin>>MM>>N;
  REP(i,MM) {
    int p; LL w;
    cin>>p>>w;
    --p;
    if(p==0) cnt+=1;
    else A[M++]={w,p,i};
  }
  solve();
  return 0;
}
