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

// $ cp-batch ExplorerSpace | diff ExplorerSpace.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ExplorerSpace.cpp && ./a.out

/*

 4/23/2021

 8:51-10:30 give up

 4/26/2021

 23:00-23:35 read editorial and got AC

 https://codeforces.com/blog/entry/89968
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.sg433p999mvf

 https://twitter.com/laycrs/status/1385645265122594820
 https://twitter.com/kiri8128/status/1385647153884798976
 https://twitter.com/ei1333/status/1385648478101983235?s=20
 https://twitter.com/kzyKT_M/status/1385645746431553538?s=20

 */

const int MAX_N=500+1,MAX_K=21;
int H[MAX_N][MAX_N],V[MAX_N][MAX_N];

int N,M,K;
int maxstep;

const int Inf=1e9;
using Edge=pair<int, int>;
vector<Edge> G[MAX_N*MAX_N];

LL dp[MAX_N][MAX_N][MAX_K];
void solve() {
  if(K%2) {
    REP(i,N) {
      REP(j,M) cout<<-1<<" \n"[j==M-1];
    }
    return;
  }

  REP(i,N) REP(j,M) REP(k,K) dp[i][j][k]=k==0?0:Inf;
  REPE(k,K/2+1)REP(i,N)REP(j,M) {
    if(k>0) FORR(e,G[i*M+j]) {
      int w,v; tie(w,v)=e;
      SMIN(dp[i][j][k],dp[v/M][v%M][k-1]+w);
    }
  }

  REP(i,N){
    REP(j,M) cout<<dp[i][j][K/2]*2<<" \n"[j==M-1];
  }
}

long long D[MAX_N*MAX_N][MAX_K];
vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
void dijkstra(int si, int sj) {
  priority_queue<III,vector<III>,greater<III>> Q; Q.emplace(0,si*M+sj,0);
  D[si*M+sj][0]=0;
  while(Q.size()>0) {
    int d; int u,k;
    tie(d,u,k)=Q.top(),Q.pop();
    if(d!=D[u][k]) continue;
    if(k==maxstep) continue;
    FORR(e,G[u]) {
      int w,v; tie(w,v)=e;
      if(D[v][k+1]>d+w) {
        D[v][k+1]=d+w;
        Q.emplace(d+w,v,k+1);
      }
    }
  }
}

void solve_wrong() {
  REP(i,N)REP(j,M) {
    FORE(ii,i-11,i+11)FORE(jj,j-11,j+11)REPE(k,maxstep) D[ii*M+jj][k]=Inf;
    dijkstra(i,j);
    VV<II> xs(maxstep+1);
    FORE(ii,i-11,i+11)FORE(jj,j-11,j+11) {
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      REPE(k,maxstep) {
        int p=ii*M+jj;
        //dump(ii,jj,k,p);
        if(D[p][k]>=Inf) continue;
        xs[k].emplace_back(D[p][k],p);
      }
    }

    LL res=Inf;
    FORE(step,1,maxstep) {
      if(K%2) {
        LL cnt=K-step*2;
        if(cnt<=0) continue;
        REP(i,SZ(xs[step])) {
          int u=xs[step][i].second;
          FORR(e,G[u]) {
            int v=e.second,w=e.first;
            if(D[v][step]>=Inf) continue;
            int i1=u/M,j1=u%M,i2=v/M,j2=v%M;
            SMIN(res,D[step][u]+D[step][v]+cnt*w);
            dump(i1,j1,i2,j2,D[step][u],D[step][v],cnt,w,res);
          }
        }
        assert(res==Inf);
      } else {
        LL cnt=K-step*2;
        if(cnt<=0) continue;
        REP(i,SZ(xs[step])) {
          int u=xs[step][i].second;
          FORR(e,G[u]) {
            int v=e.second,w=e.first;
            int i1=u/M,j1=u%M,i2=v/M,j2=v%M;
            SMIN(res,D[step][u]*2+cnt*w);
            dump(step,i1,j1,i2,j2,D[step][u],cnt,w,res);
          }
        }
      }
    }
    if(res>=Inf) res=-1;
    cout<<res<<" ";
    if(j==M-1) cout<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>M>>K;
  maxstep=K/2+1;
  REP(i,N)REP(j,M-1) {
    int w; cin>>w;
    H[i][j]=w;
    int u=i*M+j,v=i*M+j+1;
    G[u].emplace_back(w,v);
    G[v].emplace_back(w,u);
  }
  REP(i,N-1)REP(j,M) {
    int w; cin>>w;
    V[i][j]=w;
    int u=i*M+j,v=(i+1)*M+j;
    G[u].emplace_back(w,v);
    G[v].emplace_back(w,u);
  }
  solve();

  return 0;
}
