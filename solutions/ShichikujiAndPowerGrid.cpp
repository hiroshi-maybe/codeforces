#include <bits/stdc++.h>
using namespace std;
// type alias
typedef long long LL;
typedef pair<int,int> II;
typedef tuple<int,int,int> III;
typedef vector<int> VI;
typedef vector<string> VS;
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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch ShichikujiAndPowerGrid | diff ShichikujiAndPowerGrid.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ShichikujiAndPowerGrid.cpp && ./a.out

/*
 
 11/1/2019
 
 8:40-9:26 WA
 9:35 give up
 
 11/2/2019
 
 12:02-12:12 got AC after fixing a bug.
 
 I was adding scores even when graphs are already connected 😞
 
 https://codeforces.com/blog/entry/71080
 
 */

const int MAX_N=2000+1;
LL X[MAX_N],Y[MAX_N],C[MAX_N],K[MAX_N];
int N;

struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1),cost=vector<LL>(N,0),st=VI(N,0);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int size(int x) { return sz[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    int p=x,c=y;
    if(sz[p]<sz[c]) swap(p,c);
    G--,sz[p]=sz[c]=sz[p]+sz[c];
    par[c]=p;
    return p;
  }
  vector<LL> cost;
  VI st;
private:
  vector<int> par,sz;
};

void solve() {
  UF uf(N);
  REP(i,N) uf.cost[i]=C[i],uf.st[i]=i;
  vector<tuple<LL,int,int>> es;
  REP(j,N)REP(i,j) {
    LL w=(abs(X[i]-X[j])+abs(Y[i]-Y[j]))*(K[i]+K[j]);
    es.emplace_back(w,i,j);
  }
  sort(ALL(es));
  vector<II> rese;
  FORR(e,es) {
    LL w; int u,v; tie(w,u,v)=e;
    int a=uf.find(u),b=uf.find(v);
    if(a==b) continue;
    LL costa=uf.cost[a],costb=uf.cost[b];
    int stcosta=C[uf.st[a]],stcostb=C[uf.st[b]];
    
    if(w-max(stcosta,stcostb)<=0) {
      rese.emplace_back(u,v);
      int newp = uf.unite(a,b);
      uf.cost[newp]=costa+costb+w-max(stcosta,stcostb);
      uf.st[newp]=stcosta<=stcostb?uf.st[a]:uf.st[b];
    }
  }
  LL tot=0;
  VI sts;
  REP(i,N) if(uf.find(i)==i) tot+=uf.cost[i],sts.push_back(uf.st[i]);
  println("%lld",tot);
  println("%d",SZ(sts));
  REP(i,SZ(sts)) printf("%d ",sts[i]+1);
  println("");
  println("%d",SZ(rese));
  FORR(p,rese) println("%d %d",p.first+1,p.second+1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>X[i]>>Y[i];
  REP(i,N) cin>>C[i];
  REP(i,N) cin>>K[i];
  solve();
  
  return 0;
}
