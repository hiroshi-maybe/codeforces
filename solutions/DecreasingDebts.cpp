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

// $ cp-batch DecreasingDebts | diff DecreasingDebts.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DecreasingDebts.cpp && ./a.out

/*
 
 12/17/2019
 
 7:48-9:23 WA
 9:35 give up
 
 12/21/2019
 
 11:10-12:45 read editorials and got AC
 
 https://codeforces.com/blog/entry/72243
 https://twitter.com/hanseilimak/status/1208489264821850112
 https://twitter.com/tempura_cpp/status/1206992029072252929?s=20
 https://twitter.com/ajis_ka/status/1206992058814087168?s=20
 https://twitter.com/n_vip/status/1206993076759097344?s=20
 https://twitter.com/n_vip/status/1206994722570420224?s=20
 https://twitter.com/satanic0258/status/1206997274338816000?s=20
 https://twitter.com/ngtkana/status/1206994700176986113
 https://scrapbox.io/snuke/Codeforces_Global_Round_6
 
 */

const int MAX_N=1e6+1;
int N,M;

tuple<int,int,LL> E[MAX_N];
void solve() {
  VV<int> in(N),out(N);
  REP(i,M) {
    auto t=E[i];
    int u,v; LL d; tie(u,v,d)=t;
    in[v].push_back(i),out[u].push_back(i);
  }
  vector<LL> bal(N);
  VI pos,neg;
  REP(i,N) {
    LL ins=0,outs=0;
    FORR(j,in[i]) ins+=get<2>(E[j]);
    FORR(j,out[i]) outs+=get<2>(E[j]);
    bal[i]=ins-outs;
    if(bal[i]>0) pos.push_back(i);
    if(bal[i]<0) neg.push_back(i);
  }
  assert(accumulate(ALL(bal),0LL)==0LL);
  vector<tuple<int,int,LL>> res;
  int j=0;
  REP(i,SZ(pos)) {
    int u=pos[i];
    while(bal[u]>0) {
      assert(j<SZ(neg));
      int v=neg[j];
      LL d=min(abs(bal[v]),bal[u]);
      res.emplace_back(v,u,d);
      bal[v]+=d,bal[u]-=d;
      if(bal[v]==0) ++j;
    }
  }
  assert(j==SZ(neg));
  println("%d", SZ(res));
  FORR(t,res) {
    int u,v; LL d; tie(u,v,d)=t;
    println("%d %d %lld", u+1,v+1,d);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  scanf("%d %d", &N,&M);
  REP(i,M) {
    int u,v; LL d;
    scanf("%d %d %lld", &u,&v,&d);
    --u,--v;
    E[i]={u,v,d};
  }
  solve();
  
  return 0;
}

set<int> in[MAX_N],out[MAX_N];
map<pair<int,int>,LL> weights;

void remedge(int u, int v) {
  out[u].erase(v),in[v].erase(u),weights.erase({u,v});
}
void addedge(int u, int v, LL d) {
  in[v].emplace(u),out[u].emplace(v),weights[{u,v}]+=d;
}
void adjustedge(int u, int v, LL d) {
  if(weights.count({v,u})) {
    if(weights[{v,u}]==d) remedge(v,u);
    else if (weights[{v,u}]>d) weights[{v,u}]-=d;
    else {
      LL x=weights[{v,u}];
      remedge(v,u);
      addedge(u,v,d-x);
    }
  } else {
    addedge(u,v,d);
  }
}

void solve_tle() {
  VI viz(N,0);
  queue<int> Q;
  REP(u,N) if(SZ(in[u])&&SZ(out[u])) {
    Q.emplace(u),viz[u]=1;
  }
  while(SZ(Q)) {
    int u=Q.front(); Q.pop();
    while(SZ(in[u])&&SZ(out[u])) {
      int a=*in[u].begin();
      int b=*out[u].begin();
      LL wa=weights[{a,u}],wb=weights[{u,b}];
      assert(wa>0&&wb>0);
      LL z=min(wa,wb);
      if(wa==wb) {
        remedge(a,u),remedge(u,b);
      } else if(wa>wb) {
        remedge(u,b);
        weights[{a,u}]=wa-z;
      } else {
        remedge(a,u);
        weights[{u,b}]=wb-z;
      }
      adjustedge(a,b,z);
      if(!viz[b]&&SZ(in[b])&&SZ(out[b])) Q.emplace(b),viz[b]=1;
    }
    viz[u]=0;
  }
  
  println("%d", SZ(weights));
  FORR(kvp, weights) {
    println("%d %d %lld", kvp.first.first+1,kvp.first.second+1,kvp.second);
  }
}

int main_tle() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  scanf("%d %d", &N,&M);
  REP(i,M) {
    int u,v; LL d;
    scanf("%d %d %lld", &u,&v,&d);
//    cin>>u>>v>>d;
    --u,--v;
    adjustedge(u,v,d);
  }
  solve();
  
  return 0;
}
