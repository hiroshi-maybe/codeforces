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

// $ cp-batch NeighborGrid | diff NeighborGrid.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NeighborGrid.cpp && ./a.out

/*

 7/4/2020

 7:53-8:36 WA
 8:59 AC

 https://codeforces.com/blog/entry/79731

 */

const int MAX_N=300+1;
int A[MAX_N][MAX_N];
int N,M;

vector<pair<int,int>> moves = { {0,1}/*R*/,{1,0}/*D*/,{0,-1}/*L*/,{-1,0}/*U*/ };
int viz[MAX_N][MAX_N];
void solve() {
  ZERO(viz);
  priority_queue<II> Q;
  REP(i,N)REP(j,M) {
    int cnt=0,cntcnt=0;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      ++cnt;
      cntcnt+=A[ii][jj]>0;
    }
    if(A[i][j]>cnt) {
      cout<<"NO"<<endl;
      return;
    }
    A[i][j]=cnt;
  }

  cout<<"YES"<<endl;
  REP(i,N) {
    REP(j,M) cout<<A[i][j]<<" ";
    cout<<endl;
  }

  REP(i,N)REP(j,M) if(A[i][j]>0) {
    int cnt=0;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      cnt+=(A[ii][jj]>0);
    }
    dump(i,j,A[i][j],cnt);
    assert(A[i][j]==cnt);
  }
}

void solve_wrong() {
  ZERO(viz);
  priority_queue<II> Q;
  REP(i,N)REP(j,M) {
    int cnt=0,cntcnt=0;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      ++cnt;
      cntcnt+=A[ii][jj]>0;
    }
    if(A[i][j]>cnt) {
      cout<<"NO"<<endl;
      return;
    }
    if(A[i][j]>0) {
      SMAX(A[i][j],cntcnt);
      Q.emplace(A[i][j],i*M+j);
      viz[i][j]=1;
      dump(i,j);
    }
  }

  while(SZ(Q)) {
    int p; tie(ignore, p)=Q.top(); Q.pop();
    int i=p/M,j=p%M;
    int cnt=0;
    VI cand;
    for(auto m : moves) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      cnt+=viz[ii][jj]>0;
      if(viz[ii][jj]==0) cand.push_back(ii*M+jj);
    }
    dump(i,j,A[i][j],cnt);
    if(A[i][j]>cnt) {
      if(A[i][j]-cnt>SZ(cand)) {
        cout<<"NO"<<endl;
        return;
      }
      REP(k,A[i][j]-cnt) {
        int p=cand[k];
        viz[p/M][p%M]=1;
        Q.emplace(0,p);
      }
    }
    A[i][j]=max(A[i][j],cnt);
  }
  cout<<"YES"<<endl;
  REP(i,N) {
    REP(j,M) cout<<A[i][j]<<" ";
    cout<<endl;
  }

  REP(i,N)REP(j,M) if(A[i][j]>0) {
    int cnt=0;
    for(auto m : moves) {
     int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      cnt+=(A[ii][jj]>0);
    }
    dump(i,j,A[i][j],cnt);
    assert(A[i][j]==cnt);
  }
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
  N=genRandNum(1,5),M=genRandNum(1,5);
  REP(i,N) {
    VI as=genRandSeq(M,0,4);
    REP(j,M) A[i][j]=as[j];
  }

  cout<<N<<" "<<M<<endl;
  REP(i,N) {
    REP(j,M) cout<<A[i][j]<<" ";
    cout<<endl;
  }
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
    REP(i,N)REP(j,M) cin>>A[i][j];
    solve();
  }

  return 0;
}
