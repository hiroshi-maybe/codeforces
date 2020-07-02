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

// $ cp-batch Grid00100 | diff Grid00100.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Grid00100.cpp && ./a.out

/*

 7/1/2020

 7:27-8:30 WA
 8:35 give up

 23:22-24:55 read editorial and got AC

 https://twitter.com/hanseilimak/status/1278576802076606465
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.dmqqyi8ijhvn
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.yhx6s98kzqpw
 https://codeforces.com/blog/entry/79624

 https://twitter.com/ajis_ka/status/1278352736476594177
 https://twitter.com/laycrs/status/1278352821386047488
 https://twitter.com/kzyKT_M/status/1278352007326085120

 */

int N,K;

void solve() {
  vector<string> A(N,string(N,'0'));
  int k=K,i=0,j=0;
  while(k--) {
    A[i][j]='1';
    ++i,++j;
    if(i==N) i=0,(++j)%=N;
    else j%=N;
  }
  VI R(N,0), C(N,0);
  REP(i,N) R[i]=count(ALL(A[i]),'1');
  REP(j,N) REP(i,N) C[j]+=A[i][j]=='1';
  int r=*max_element(ALL(R))-*min_element(ALL(R));
  int c=*max_element(ALL(C))-*min_element(ALL(C));
  int res=r*r+c*c;

  if(r>1||c>1) {
    dump(N,K,r,c);
  }

  cout<<res<<endl;
  REP(i,N) cout<<A[i]<<endl;
}

void solve_wrong() {
  vector<string> A(N,string(N,'0'));
  int k=K;
  REP(i,N) if(k>0) {
    A[i][i]='1',--k;
  }
  FOR(x,1,N) {
    dump(x);
    REPE(i,x) if(k>0&&A.at(i).at(x-i)=='0') {
      dump(i,x-i);
      A[i][x-i]='1',--k;
    }
    REPE(jj,x) if(k>0) {
      int j=N-1-jj,i=2*N-2-x-j;
      dump(jj,j,i);
      if(A.at(i).at(j)=='0') {
        dump(i,j);
        A[i][j]='1',--k;
      }
    }
    if(k==0) break;
  }
  assert(k==0);
  VI R(N,0), C(N,0);
  REP(i,N) R[i]=count(ALL(A[i]),'1');
  REP(j,N) REP(i,N) C[j]+=A[i][j]=='1';
  int r=*max_element(ALL(R))-*min_element(ALL(R));
  int c=*max_element(ALL(C))-*min_element(ALL(C));
  int res=r*r+c*c;

  if(r>1||c>1) {
    dump(N,K,r,c);
  }

  cout<<res<<endl;
  REP(i,N) cout<<A[i]<<endl;

  assert(r<=1&&c<=1);
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}

void test() {
  N=genRandNum(1,4);
  K=genRandNum(0,N*N);
  dump(N,K);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

//  while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N>>K;
    solve();
  }

  return 0;
}
