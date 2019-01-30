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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

// $ cp-batch GreatVovaWallVersion2 | diff GreatVovaWallVersion2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GreatVovaWallVersion2.cpp && ./a.out

/*
 
 1/28/2019
 
 10:50-11:11 AC after fixing bug found in test case #4
 
 https://codeforces.com/blog/entry/63961
 http://tsutaj.hatenablog.com/entry/2018/12/28/052918
 
 I solved again by stack approach. However code is shit.
 There are two conditions that we should hold
 1. merge when equal height can be paired
 2. height of inner segment should be at most outer segment
 
 #1 can be satisfied by popping when top of the stack is equal.
 #2 can be satisfied when pushing height is less than top of the stack.
 
 Proof of #2:
 
 Suppose top of the stack is `a` and we are pushing `b`.
 If `a`==`b`, we can just pop `a`.
 If `a`>`b`, we push `b`. We are sure that `b` is popped earlier than `a`.
 Thus condition that height of inner segment is at most outer holds.
 If `a`<`b`, height of inner segment is more than outer as symmetry property of `a`>`b` case. The given sequence is valid.
 
 Remaining one corresponds to the last state after merges. It should be max A.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

struct UF {
public:
  int N,G/* # of disjoint sets */;
  VI L,R,V;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1),L=VI(N,-1),R=VI(N,-1),V=VI(N);
    for(int i=0; i<N; ++i) par[i]=i,rank[i]=0,cnt[i]=1,L[i]=i,R[i]=i,V[i]=A[i];
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
    L[p]=min(L[p],L[c]),R[p]=max(R[p],R[c]),V[p]=max(V[p],V[c]);
    return p;
  }
private:
  vector<int> par,rank,cnt;
};

int viz[MAX_N];
void solve_greedy() {
  ZERO(viz);
  queue<int> Q;
  UF uf(N);
  REP(i,N-1) if(A[i]==A[i+1]&&viz[i]==0&&viz[i+1]==0) {
    dump2(i,i+1)
    int p=uf.unite(i,i+1);
    Q.emplace(p),viz[i]=viz[i+1]=1;
  }
  while(SZ(Q)) {
    int i=Q.front(); Q.pop();
    int l=uf.L[i],r=uf.R[i];
    if(l-1>=0&&r+1<N&&viz[l-1]==0&&viz[r+1]==0&&A[l-1]==A[r+1]&&A[l-1]>=uf.V[i]) {
            dump2(l-1,r+1);
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
  map<int,int> cnt;
  REP(i,N)if(viz[i]==0) cnt[A[i]]++;
  
  int maxv=0;
  REP(i,N)if(viz[i]) SMAX(maxv,uf.V[uf.find(i)]);
  
  bool ok=false;
  if(SZ(cnt)==0) ok=true;
  if(SZ(cnt)==1) ok=cnt.begin()->first>=maxv;
  
  cout<<(ok?"YES":"NO")<<endl;
}

void solve_nusty_stack() {
  VI S;
  REP(i,N) {
    if(S.empty()) S.push_back(A[i]);
    else if(S.back()==A[i]) {
      S.pop_back();
      S.push_back(-A[i]);
    } else if(S.back()<0) {
      if(SZ(S)>1&&S[SZ(S)-2]==A[i]) {
        if(-S.back()<=A[i]) {
          S.pop_back(),S.pop_back();
          S.push_back(-A[i]);
        } else {
          cout<<"NO"<<endl;
          return;
        }
      } else S.push_back(A[i]);
    } else {
      S.push_back(A[i]);
    }
    while(SZ(S)>1&&S[SZ(S)-1]<0&&S[SZ(S)-2]<0) {
      int a=S[SZ(S)-1],b=S[SZ(S)-2];
      S.pop_back(),S.pop_back();
      S.push_back(min(a,b));
    }
  }
  SETI T;
  int lb=0;
  REP(i,SZ(S)) {
    if(S[i]>0) T.emplace(S[i]);
    else SMIN(lb,S[i]);
  }
  if(T.empty()) cout<<"YES"<<endl;
  else if(SZ(T)>1) cout<<"NO"<<endl;
  else {
    int x=*T.begin();
    cout<<(x>=abs(lb)?"YES":"NO")<<endl;
  }
}

void solve() {
  stack<int> S;
  REP(i,N) {
    int a=A[i];
    if(S.empty()) S.push(a);
    else if(S.top()==a) S.pop();
    else if(S.top()<a) {
      cout<<"NO"<<endl;
      return;
    } else S.push(a);
  }
  int x=*max_element(A,A+N);
  bool res=true;
  if(SZ(S)>=2) res=false;
  if(SZ(S)==1&&S.top()!=x) res=false;
  cout<<(res?"YES":"NO")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
