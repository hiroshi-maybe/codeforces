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
struct GraphCycle {
public:
  // input
  int V;
  vector<vector<int>> G;
  GraphCycle(int V): V(V), G(V), done(V, -1), viz(V, 0) {}
  void edge(int u, int v) {
    assert(u<V&&v<V);
    G[u].push_back(v);
  }

  vector<int> findCycleFreeNodes() {
    vector<int> res;
    for(int u=0; u<V; ++u) {
      if(!viz[u]) dfs(u);
      if(!done[u]) res.push_back(u);
    }
    return res;
  }
private:
  vector<int> done; // -1: not done, 0: descendent has NO cycle, 1: descendent has cycle
  vector<int> viz;

  int dfs(int u) {
    if(done[u]!=-1) return done[u];
    viz[u]=true;

    int res=false;
    for(int v : G[u]) {
      if(!viz[v]) dfs(v);
      res|=done[v]==-1?true:done[v];
    }
    return done[u]=res;
  }
};

// $ cp-batch ABGraph | diff ABGraph.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ABGraph.cpp && ./a.out

/*

 2/5/2021

 7:40-9:00 give up
 9:30-10:00 give up

 https://twitter.com/laycrs/status/1357729684780244993
 https://twitter.com/kzyKT_M/status/1357729624168357894
 https://twitter.com/kiri8128/status/1357730625965289474

 2/8/2021

 21:20-22:20 AC

 https://codeforces.com/blog/entry/87523
 https://twitter.com/laycrs/status/1357729684780244993
 https://twitter.com/kiri8128/status/1357730625965289474
 https://twitter.com/kzyKT_M/status/1357729624168357894

 */

const int MAX_N=1e3+1;
string S[MAX_N];
int N,M;

bool ispalin(string &s) {
  int N=SZ(s),l=0,r=N-1;
  while(l<r) {
    if(s[l]!=s[r]) return false;
    ++l,--r;
  }
  return true;
}
void yes(VI &res) {
  string s;
  REP(i,M) s.push_back(S[res[i]][res[i+1]]);
  //dumpc(res);
  //dump(s);
  assert(ispalin(s));

  cout<<"YES"<<endl;
  REPE(i,M) cout<<res[i]+1<<" ";
  cout<<endl;
}

void solve() {
  VI res;
  if(M==1) {
    res={0,1};
    yes(res);
    return;
  }

  REP(i,N)REP(j,N) if(i!=j&&S[i][j]==S[j][i]) {
    REP(k,M+1) res.push_back(k%2?i:j);
    yes(res);
    return;
  }

  if(M%2) {
    assert(S[0][1]!=S[1][0]);
    REP(i,M+1) res.push_back(i%2);
    yes(res);
    return;
  }

  REP(l,2) {
    VV<int> in(N),out(N);
    REP(u,N)REP(v,N) if(u!=v&&S[u][v]=='a'+l) {
      in[v].push_back(u),out[u].push_back(v);
    }
    REP(u,N) if(SZ(in[u])&&SZ(out[u])) {
      int v1=in[u].back(),v2=out[u].back();
      //dump(v1,u,v2);
      assert(S[u][v1]!=S[v1][u]&&S[u][v2]!=S[v2][u]);
      REP(i,M/2) res.push_back(((i%2)^((M/2)%2))?v1:u);
      //assert(res.back()!=u);
      res.push_back(u);
      REP(i,M/2) res.push_back(i%2?u:v2);
      yes(res);
      return;
    }
  }

  cout<<"NO"<<endl;
}

VI G[2][MAX_N];
void solve_wrong() {
  REP(l,2) REP(u,N) G[l][u].clear();
  if(N==2&&S[0][1]!=S[1][0]&&M%2==0) {
    cout<<"NO"<<endl;
    return;
  }
  if(M==1) {
    cout<<"YES"<<endl;
    cout<<"1 2"<<endl;
    return;
  }

  REP(i,N)REP(j,N) if(i!=j) {
    int l=S[i][j]=='b';
    G[l][i].push_back(j);
  }

  REP(l,2) {
    /*
    REP(u,N) {
      dump(l,u);
      dumpc(G[l][u]);
    }*/

    GraphCycle gc(N);
    REP(u,N) FORR(v,G[l][u]) gc.edge(u,v);
    VI xs=gc.findCycleFreeNodes();
    set<int> X(ALL(xs));
    VV<int> sg(N);
    REP(u,N) if(!X.count(u)) {
      FORR(v,G[l][u]) if(!X.count(v)) sg[u].push_back(v);
    }

    if(SZ(X)!=N) REP(u,N) if(!X.count(u)) {
      //dump(l,u);
      VI res(1,u);

      int v=u;
      while(SZ(res)<=M) {
        assert(SZ(sg[v]));
        int vv=sg[v].front();
        res.push_back(vv),v=vv;
      }
      yes(res);
      return;
    }

    if(M%2) {
      REP(u,N)REP(v,N) if(S[u][v]!=S[v][u]) {
        VI res;
        REP(i,M+1) res.push_back(i%2?v:u);
        yes(res);
        return;
      }
    } else {
      if(M==2) {
        cout<<"NO"<<endl;
        return;
      }
      VV<int> ind(N),outd(N);
      REP(u,N) FORR(v,G[l][u]) ind[v].push_back(u),outd[u].push_back(v);
      REP(u,N) if(SZ(ind[u])>0&&SZ(outd[u])>0) {
        int v1=ind[u].back(),v2=outd[u].back();
        assert(v1!=v2);
        int mm=M/2;
        int x=v1;
        VI res;
        if(mm%2==0) x=v2;
        res.push_back(x);
        REP(_,mm-1) res.push_back(res.back()==v1?v2:v1);
        assert(res.back()==v1);
        res.push_back(u);
        res.push_back(v2);
        REP(_,mm-1) res.push_back(res.back()==v1?v2:v1);
        assert(SZ(res)==M+1);
        yes(res);
        return;
      }
    }
  }

  cout<<"NO"<<endl;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=genRandNum(2,5),M=genRandNum(1,9);
  REP(i,N) {
    S[i]=string(N,'*');
    REP(j,N) if(i!=j) S[i][j]='a'+genRandNum(0,2);
  }
  cout<<N<<" "<<M<<endl;
  REP(i,N) cout<<S[i]<<endl;
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N>>M;
    REP(i,N) cin>>S[i];
    solve();
  }

  return 0;
}
