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

// $ cp-batch NastyaAndScoreboard | diff NastyaAndScoreboard.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NastyaAndScoreboard.cpp && ./a.out

/*
 
 4/23/2020
 
 8:44-10:32 TLE
 22:03-22:43 read submit solutions and got AC
 
 https://twitter.com/hanseilimak/status/1253552785204760576
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.skucdpnb8ylc
 
 */

const int MAX_N=2e3+1;
string A[MAX_N];
int N,K;

int bin2n(string s) {
  int res=0;
  for(int i=0; i<s.size(); ++i) {
    res=2*res+(s[i]=='1');
  }
  return res;
}
string ds[10]={"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};

II pre[MAX_N][MAX_N];
string solve() {
  VI dmasks(10);
  REP(i,10) dmasks[i]=bin2n(ds[i]);
  REP(i,MAX_N)REP(j,MAX_N) pre[i][j]={-1,-1};
  VI masks(N); REP(i,N) masks[i]=bin2n(A[i]);
  reverse(ALL(masks));
  
  REP(i,N) {
    int mask=masks[i];
    REP(d,10) if((mask&dmasks[d])==mask) {
      int x=__builtin_popcount(dmasks[d])-__builtin_popcount(mask);
      REPE(k,K) if((i==0&&k==0)||pre[i][k].first!=-1) if(k+x<=K) {
        pre[i+1][k+x]={k,d};
//        dump(i,k,i+1,k+x,d);
      }
    }
  }
  
  string res;
  for(int i=N,k=K; i>=1; --i) {
    int kk,d; tie(kk,d)=pre[i][k];
    if(d==-1) return "-1";
    res.push_back('0'+d);
    k=kk;
  }
  return res;
}

string dp[2][MAX_N];
pair<VI,VI> f(VI &masks, VI &dmasks) {
  VI ls(N+1),rs(N+1);
  int prel=0,prer=0;
  REP(i,N) {
    int mask=masks[i];
    int l=10,r=-1;
    REP(j,10) if((mask&dmasks[j])==mask) {
      int x=__builtin_popcount(dmasks[j])-__builtin_popcount(mask);
      dump(i,j,x);
      SMIN(l,x),SMAX(r,x);
    }
    assert(l<10);
    ls[i+1]=min(prel+l,K),rs[i+1]=min(prer+r,K);
    dump(i,mask,l,r,prel,prer,ls[i+1],rs[i+1])
    prel=ls[i+1],prer=rs[i+1];
  }
  return {ls,rs};
}
string solve_tle1() {
  VI dmasks(10);
  REP(i,10) dmasks[i]=bin2n(ds[i]);
  REP(i,2)REP(j,MAX_N)dp[i][j]="";
  VI ls1(N+1),rs1(N+1);
  
  VI masks(N); REP(i,N) masks[i]=bin2n(A[i]);
  tie(ls1,rs1)=f(masks,dmasks);
  dumpc(masks);
  reverse(ALL(masks));
  dump("rev");
  dumpc(masks);
  VI ls2,rs2; tie(ls2,rs2)=f(masks,dmasks);
  
  VI ls(N+1),rs(N+1);
  REP(i,N) {
    int l1=ls1[i], r1=rs1[i];
    int l2=K-rs2[N-i],r2=K-ls2[N-i];
    dump(l1,r1,l2,r2);
    ls[i]=max(l1,l2),rs[i]=min(r1,r2);
  }
  dumpc(ls);
  dumpc(rs);
  
  REP(i,N){
    int mask=bin2n(A[i]);
    vector<II> ds;
    REP(i,10) if((mask&dmasks[i])==mask) ds.emplace_back(dmasks[i],i);
    FORE(k,ls[i],rs[i]) if((i==0&&k==0)||dp[0][k]!="") FORR(p,ds) {
      int dmask=p.first,d=p.second;
      int x=__builtin_popcount(dmask)-__builtin_popcount(mask);
      assert(x>=0);
      string s=dp[0][k];
      if(k+x<=K) {
        s.push_back('0'+d);
        SMAX(dp[1][k+x],s);
//        dump(i,k,x,k+x,d,s);
      }
    }
    REPE(k,K) dp[0][k]=dp[1][k],dp[1][k]="";
  }
  string res=dp[0][K];
  if(res=="") res="-1";
  return res;
}

string solve_tle2() {
  VI dmasks(10);
  REP(i,10) dmasks[i]=bin2n(ds[i]);
  REP(i,2)REP(j,MAX_N)dp[i][j]="";
  
  REP(i,N){
    int mask=bin2n(A[i]);
    vector<II> ds;
    REP(i,10) if((mask&dmasks[i])==mask) ds.emplace_back(dmasks[i],i);
    FORE(k,0,K) if((i==0&&k==0)||dp[0][k]!="") FORR(p,ds) {
      int dmask=p.first,d=p.second;
      int x=__builtin_popcount(dmask)-__builtin_popcount(mask);
      assert(x>=0);
      string s=dp[0][k];
      if(k+x<=K) {
        s.push_back('0'+d);
        SMAX(dp[1][k+x],s);
//        dump(i,k,x,k+x,d,s);
      }
    }
    REPE(k,K) dp[0][k]=dp[1][k],dp[1][k]="";
  }
  string res=dp[0][K];
  if(res=="") res="-1";
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K;
  REP(i,N) cin>>A[i];
  
  cout<<solve()<<endl;
  
  return 0;
}
