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

// $ cp-batch WeightsDivisionHard | diff WeightsDivisionHard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address WeightsDivisionHard.cpp && ./a.out

/*

 8/5/2020

 9:29-9:35 give up

 8/6/2020

 9:45-22:55 figured out a bug

 8/9/2020

 16:05-16:46 AC after looking at solution tweets

 https://twitter.com/hanseilimak/status/1292608251314413568
 https://codeforces.com/blog/entry/81082

 https://twitter.com/laycrs/status/1291054107369672711
 https://twitter.com/ei1333/status/1291054228308242433

 */

const int MAX_N=1e6+1;
LL S;
int N;

vector<tuple<LL,int,int>> G[MAX_N];

LL sum=0;

LL prof(LL w, int cnt) {
  return (w-w/2)*cnt;
}

int dfs(int u, int pre, vector<vector<tuple<LL,int,LL>>> &Q) {
  int cnt=SZ(G[u])==1;
  FORR(p,G[u]) {
    int v,c; LL w; tie(w,v,c)=p;
    if(v==pre) continue;
    int cnt2=dfs(v,u,Q);
    Q[c-1].emplace_back(prof(w,cnt2), cnt2, w);
    cnt+=cnt2;
    //dump(u,v,w,cnt2,(w-w/2)*cnt2);
    sum+=w*cnt2;
  }
  return cnt;
}

void solve() {
  sum=0;
  using T=tuple<LL,int,LL>;
  VV<T> xs(2,vector<T>());
  dfs(0,-1,xs);
  //dump(S,sum);

  if(S>=sum) {
    cout<<0<<endl;
    return;
  }
  VV<LL> costs(2);
  REP(c,2) {
    REP(i,SZ(xs[c])) {
      T t=xs[c][i];
      LL a,w; int cnt;
      tie(a,cnt,w)=t;
      while(prof(w,cnt)>0) costs[c].push_back(prof(w,cnt)),w/=2;
    }
    sort(costs[c].rbegin(),costs[c].rend());
  }

  VV<LL> cums(2);
  REP(c,2) {
    cums[c]=vector<LL>(SZ(costs[c])+1);
    REP(i,SZ(costs[c])) cums[c][i+1]=cums[c][i]+costs[c][i];
  }
  LL res=1e18;
  REP(i,SZ(cums[0])) {
    LL a=cums[0][i];
    LL rem=sum-S-a;
    auto it=lower_bound(cums[1].begin(),cums[1].end(),rem);
    if(it!=cums[1].end()) {
      SMIN(res,i+2LL*(it-cums[1].begin()));
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  sum=0;
  int res=0;
  VV<tuple<LL,int,LL>> costs(2,vector<tuple<LL,int,LL>>());
  dfs(0,-1,costs);

  vector<priority_queue<tuple<LL,int,LL>>> Q(2);
  REP(i,2) {
    while(SZ(costs[i])) Q[i].emplace(costs[i].back()),costs[i].pop_back();
  }

  auto pushdoubled = [&]() {
    if(SZ(Q[0])<2) return;
    tuple<LL,int,LL> t1,t2;
    t1=Q[0].top(),Q[0].pop();
    t2=Q[0].top();
    LL p1,p2;
    tie(p1,ignore,ignore)=t1,tie(p2,ignore,ignore)=t2;
    Q[1].emplace(p1+p2,-1,-1);
    Q[0].emplace(t1);
  };

  auto proc = [&](int cost, int turn) {
    vector<tuple<LL,int,LL>> X;
    REP(_, turn) {
      dump(cost,SZ(Q[cost]));
      auto t=Q[cost].top(); Q[cost].pop();
      LL p,w; int cnt; tie(p,cnt,w)=t;
      dump(cost,p,w,cnt);
      assert(p>0);
      res+=cost+1;
      sum-=p;
      w/=2;
      X.emplace_back(prof(w,cnt), cnt, w);
    }
    FORR(t,X) Q[cost].emplace(t);
  };

  pushdoubled();
  while(sum>S) {
    dump(sum,SZ(Q[0]),SZ(Q[1]));
    tuple<LL,int,LL> t0,t1;
    if(SZ(Q[0])) {
      t0=Q[0].top();
      LL p,w; int cnt; tie(p,cnt,w)=t0;
      if(sum-p<=S) {
        proc(0,1);
        break;
      }
      if(Q[1].empty()) {
        proc(0,1);
        continue;
      }
    }

    assert(SZ(Q[1]));
    t1=Q[1].top();
    LL p,w; int cnt; tie(p,cnt,w)=t1;
    dump(p,w,cnt);
    if(cnt==-1) {
      Q[1].pop();
      proc(0,2);
      if(SZ(Q[0])>1) pushdoubled();
    } else {
      proc(1,1);
    }
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>S;
    REP(i,N) G[i].clear();
    REP(_,N-1) {
      int u,v,c; LL w; cin>>u>>v>>w>>c;
      --u,--v;
      G[u].emplace_back(w,v,c),G[v].emplace_back(w,u,c);
    }
    solve();
  }

  return 0;
}
