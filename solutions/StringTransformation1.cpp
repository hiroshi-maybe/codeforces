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
private:
  vector<int> par,sz;
};
// $ cp-batch StringTransformation1 | diff StringTransformation1.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StringTransformation1.cpp && ./a.out

/*

 7/24/2020

 8:21-8:56 WA
 9:10 WA
 9:35 give up
 10:20-10:40 AC by looking at failed test case

 7/26/2020

 12:40 Read editorial and add union-find solution

 https://twitter.com/hanseilimak/status/1287469898512228352
 https://codeforces.com/blog/entry/80562

 https://twitter.com/laycrs/status/1286702256608272385
 https://twitter.com/Rubikun_pro/status/1286702359121281024
 https://twitter.com/Cinnamon_VR/status/1286702933736742912
 https://twitter.com/kzyKT_M/status/1286703464504889344

 */

string A,B;
int N;

LL solve() {
  REP(i,N) if(A[i]>B[i]) return -1;
  UF uf(20);
  VV<int> mx(20, VI(20));
  REP(i,N) mx[A[i]-'a'][B[i]-'a']=1;
  LL res=0;
  REP(c,20) {
    VI cs;
    REP(i,20) if(mx[i][c]) cs.push_back(i);
    cs.push_back(c);
    SETI S;
    FORR(c,cs) S.emplace(uf.find(c));
    REP(i,SZ(cs)-1) uf.unite(cs[i],cs[i+1]);
    res+=SZ(S)-1;
  }
  return res;
}

LL solve_org() {
  REP(i,N) if(A[i]>B[i]) return -1;
  map<int,set<int>> E;
  REP(i,N) E[B[i]-'a'].emplace(A[i]-'a');
  LL res=0;
  VI B(20,0); REP(i,20) B[i]=i;
  FORR(kvp,E) {
    int cur=kvp.first;
    VI A(ALL(kvp.second));
    //int vizcnt=0,nvizcnt=0;
    set<int> S;
    FORR(a,A) {
      if(a<cur) S.emplace(B[a]);
    }
    REP(i,20) if(S.count(B[i])) B[i]=cur;
    //dump((char)('a'+cur),SZ(S));
    res+=SZ(S);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>A>>B;
    cout<<solve()<<endl;
  }

  return 0;
}
