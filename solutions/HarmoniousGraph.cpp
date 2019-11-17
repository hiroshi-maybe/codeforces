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
struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1);
    L=VI(N),R=VI(N);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1,L[i]=i,R[i]=i+1;
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
    L[p]=min(L[c],L[p]);
    R[p]=max(R[c],R[p]);
    return p;
  }
  vector<int> L,R;
private:
  vector<int> par,sz;
};

// $ cp-batch HarmoniousGraph | diff HarmoniousGraph.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address HarmoniousGraph.cpp && ./a.out

/*
 
 11/16/2019
 
 7:51-8:04 WA
 8:35 give up
 11:30-12:11 understand problem correctly and got AC
 
 https://twitter.com/hanseilimak/status/1196148742392430592
 https://codeforces.com/blog/entry/71489
 
 */

const int MAX_N=1e6+1;
int N,M;
VI G[MAX_N];
UF uf(0);

int solve() {
  vector<II> X;
  REP(i,N) if(uf.find(i)==i) {
    X.emplace_back(uf.L[i],uf.R[i]);
  }
  sort(ALL(X));
  int res=0,r=-1;
  REP(i,SZ(X)) {
    if(X[i].first<r) {
      ++res;
    }
    SMAX(r,X[i].second);
  }
  return res;
}

int solve_wrong() {
  int res=2;
  REP(i,N-2) {
    int a=i,b=i+1,c=i+2;
    SETI S;
    S.emplace(uf.find(a)),S.emplace(uf.find(b)),S.emplace(uf.find(c));
    if(SZ(S)==1) SMIN(res,0);
    else if(SZ(S)==2) SMIN(res,1);
    else SMIN(res,2);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M;
  uf=UF(N);
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
//    G[u].push_back(v),G[v].push_back(u);
    uf.unite(u,v);
  }
  cout<<solve()<<endl;
  
  return 0;
}
