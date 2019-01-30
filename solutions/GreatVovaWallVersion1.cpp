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

// $ cp-batch GreatVovaWallVersion1 | diff GreatVovaWallVersion1.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GreatVovaWallVersion1.cpp && ./a.out

/*
 
 1/28/2019
 
 8:57-10:05 WA on test case #9
 10:36 got AC (no proof)
 
 https://codeforces.com/blog/entry/63961
  - parenthesis balance and greedy
 http://tsutaj.hatenablog.com/entry/2018/12/28/052918
  - Merge consecutive pairs => parenthesis balance

 It can be shown that original problem is subset of parenthesis balance problem.
 (We can just ignore negative balance in prefixes)
 Then merge happens like ()() or (()). They can be both covered by bfs.
 
 It's nice to understand that merge of even consecutive intervals can be reduced to parenthesis balance problem.
 
 */

struct UF {
public:
  int N,G/* # of disjoint sets */;
  VI L,R;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1),L=VI(N,-1),R=VI(N,-1);
    for(int i=0; i<N; ++i) par[i]=i,rank[i]=0,cnt[i]=1,L[i]=i,R[i]=i;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int count(int x) { return cnt[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    G--,cnt[x]=cnt[y]=cnt[x]+cnt[y];
    int p=x,c=y;
    if(rank[p]>rank[c]) swap(p,c);
    else rank[p]+=rank[p]==rank[c];
    par[c]=p;
    L[p]=min(L[p],L[c]),R[p]=max(R[p],R[c]);
    return p;
  }
private:
  vector<int> par,rank,cnt;
};

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

int viz[MAX_N];
void solve_org() {
  ZERO(viz);
  queue<int> Q;
  UF uf(N);
  REP(i,N-1) if(A[i]==A[i+1]&&viz[i]==0&&viz[i+1]==0) {
    int p=uf.unite(i,i+1);
    Q.emplace(p),viz[i]=viz[i+1]=1;
  }
  while(SZ(Q)) {
    int i=Q.front(); Q.pop();
    int l=uf.L[i],r=uf.R[i];
    if(l-1>=0&&r+1<N&&viz[l-1]==0&&viz[r+1]==0&&A[l-1]==A[r+1]) {
//      dump2(l-1,r+1);
      int p=uf.unite(i,l-1);
      p=uf.unite(p,r+1);
      Q.emplace(p),viz[l-1]=viz[r+1]=1;
    } else if(l-1>=0&&viz[l-1]) {
      int p=uf.unite(i,l-1);
      Q.emplace(p);
    } else if(r+1<N&&viz[r+1]) {
      int p=uf.unite(i,r+1);
      Q.emplace(p);
    }
  }
  int cnt[2]={};
  REP(i,N)if(viz[i]==0) cnt[A[i]]++;
  
  cout<<(cnt[0]==0||cnt[1]==0?"YES":"NO")<<endl;
}

void solve() {
  stack<int> S;
  REP(i,N) {
    if(S.empty()||A[i]!=S.top()) S.emplace(A[i]);
    else S.pop();
  }
  cout<<(SZ(S)<=1?"YES":"NO")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i],A[i]%=2;
  solve();
  
  return 0;
}
