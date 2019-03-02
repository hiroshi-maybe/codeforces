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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch GourmetChoice | diff GourmetChoice.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GourmetChoice.cpp && ./a.out

/*
 
 3/1/2019
 
 21:23-22:03 WA
 22:22 fixed two bugs and got AC
 
 https://codeforces.com/blog/entry/65487
 
 */

struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),rank=vector<int>(N),cnt=vector<int>(N,1);
    for(int i=0; i<N; ++i) par[i]=i,rank[i]=0,cnt[i]=1;
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
    return p;
  }
private:
  vector<int> par,rank,cnt;
};

const int MAX_N=1e3+1;
string A[MAX_N];
int N,M;
VI G[2*MAX_N];

void nope() {
  println("No");
  exit(0);
}
void solve() {
  UF uf(N+M);
  REP(i,N)REP(j,M) if(A[i][j]=='=') uf.unite(i,N+j);
  REP(i,N)REP(j,M) if(A[i][j]!='=') {
    int u=uf.find(i),v=uf.find(N+j);
    if(u==v) nope();
    if(A[i][j]=='<') G[u].push_back(v);
    else if(A[i][j]=='>') G[v].push_back(u);
  }
  vector<int> D(N+M,-1);
  REP(i,N+M) if(uf.find(i)==i) D[i]=0;
  REP(i,N+M) {
    int u=uf.find(i);
    if(u!=i) continue;
    FORR(v,G[u]) D[v]++;
  }
  dump(D[2],D[5]);
  VI lv(N+M,0);
  int step=0;
  queue<int> Q;
  REP(i,N+M) if(D[i]==0) Q.emplace(i);
  while(SZ(Q)) {
    int L=SZ(Q);
    ++step;
    REP(_, L) {
      int u=Q.front(); Q.pop();
      dump(u,step);
      lv[u]=step;
      FORR(v,G[u]) {
        D[v]--;
        if(D[v]==0) Q.emplace(v);
      }
    }
  }
  REP(i,N+M) if(D[i]>0) nope();
  REP(i,N+M) if(uf.find(i)!=i) lv[i]=lv[uf.find(i)];
  println("Yes");
  REP(i,N) printf("%d ", lv[i]);
  println("");
  FOR(i,N,N+M) printf("%d ", lv[i]);
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
