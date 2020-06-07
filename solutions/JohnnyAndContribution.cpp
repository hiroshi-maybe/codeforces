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

// $ cp-batch JohnnyAndContribution | diff JohnnyAndContribution.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address JohnnyAndContribution.cpp && ./a.out

/*

 6/4/2020

 8:17-10:17 give up

 6/6/2020

 17:10-18:34 AC after fixing a bug

 https://twitter.com/hanseilimak/status/1269421358116528128
 https://codeforces.com/blog/entry/78355

 https://twitter.com/tempura_cpp/status/1268589653747105792
 https://twitter.com/tsutaj/status/1268589848220196864
 https://twitter.com/heno_code/status/1268590196804603904
 https://twitter.com/ngtkana/status/1268590896930361350
 https://twitter.com/laycrs/status/1268593282717593600

 */

const int MAX_N=1e6+1;
int T[MAX_N];
int N,M;

VI G[MAX_N];
void nope() {
  cout<<-1<<endl;
}

void verify(VI &res) {
  VI viz(N,0);
  REP(i,N) {
    int u=res[i];
    int t=T[u];
    set<int> ts;
    FORR(v, G[u]) if(viz[v]) {
      assert(T[v]<t);
      ts.emplace(T[v]);
    }
    viz[u]=1;
    //dump(u,t);
    //dumpc(ts)
    assert(SZ(ts)==t);
  }
}

int viz[MAX_N];
bool solve() {
  ZERO(viz);

  vector<II> ord;
  REP(i,N) ord.emplace_back(T[i],i);
  sort(ALL(ord));
  //dumpc(ord);
  VI res;
  REP(i,N) {
    int t,u; tie(t,u)=ord[i];
    set<int> ts;
    FORR(v,G[u]) if(viz[v]) {
      if(T[v]==t) return false;
      ts.emplace(T[v]);
    }
    if(SZ(ts)!=t) return false;
    res.push_back(u),viz[u]=1;
  }

  verify(res);

  REP(i,N) cout<<res[i]+1<<" ";
  cout<<endl;

  return true;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
vector<vector<int>> gen_graph(int N, int maxM=(int)1e5) {
  vector<vector<int>> G(N);
  set<pair<int,int>> es;
  int m=N==1?0:genRandNum(0,min(N*(N-1)/2,maxM));
  dump(N,m);
  while(m--) {
    int u=genRandNum(0,N),v=genRandNum(0,N);
    if(u==v) continue;
    if(u>v) swap(u,v);
    if(es.count({u,v})) continue;
    es.emplace(u,v);
  }

  M=SZ(es);
  printf("%d %d\n",N,M);
  for(auto e : es) {
    printf("%d %d\n",e.first+1,e.second+1);
    G[e.first].push_back(e.second);
    G[e.second].push_back(e.first);
  }
  return G;
}

void test() {
  N=genRandNum(1,100);
  VV<int> g=gen_graph(N);
  REP(i,N) G[i].clear();
  REP(i,N) G[i]=g[i];
  VI ts=genRandSeq(N,0,N);
  REP(i,N) printf("%d ",ts[i]+1),T[i]=ts[i];
  println("");
  bool res=solve();

/*
  bool exp=false;

  VI P(N);
  REP(i,N)P[i]=i;
  do {
    VI viz2(N,false);
    VI ds(N,-1);
    bool ok=true;
    dumpc(P);
    REP(i,N) {
      int u=P[i];
      int maxd=-1,d=T[u];
      dumpc(G[u]);
      FORR(v,G[u]) if(viz2.at(v)) {
        //dump(u,v,T[v],maxd);
        SMAX(maxd,T[v]);
      }
      dump(u,maxd,d);
      if(maxd!=d-1) {
        ok=false;
        break;
      }
      ds[u]=d,viz2[u]=true;
      dump(u,ds[u],viz2[u]);
    }
    if(ok) {
      exp=true;
      break;
    }
  } while(next_permutation(ALL(P)));

  dump(exp,res);
  assert(exp==res);*/
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  // while(true) test();

  cin>>N>>M;
  REP(i,M) {
    int u,v; cin>>u>>v;
    --u,--v;
    G[u].push_back(v),G[v].push_back(u);
  }
  REP(i,N) cin>>T[i],T[i]--;
  bool res=solve();
  if(!res) nope();

  return 0;
}
