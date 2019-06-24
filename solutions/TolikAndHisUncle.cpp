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

// $ cp-batch TolikAndHisUncle | diff TolikAndHisUncle.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TolikAndHisUncle.cpp && ./a.out

/*
 
 6/21/2019
 
 10:59-11:56 TLE
 12:05 give up
 
 14:25-14:47 add solution
 
 https://codeforces.com/blog/entry/67891
 
 */

int N,M;
void solve() {
  vector<II> res;
  int r0=0,r1=N-1;
  while(r0<=r1) {
    if(r0!=r1) REP(c,M) {
      res.emplace_back(r0,c);
      res.emplace_back(r1,M-1-c);
    }
    if(r0==r1) {
      int c0=0,c1=M-1;
      while(c0<=c1) {
        res.emplace_back(r0,c0++);
        if(c1>c0) res.emplace_back(r0,c1--);
      }
    }
    r0++,r1--;
  }
//  dumpc(res);
  assert(SZ(res)==N*M);
  REP(i,SZ(res)) println("%d %d", res[i].first+1, res[i].second+1);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
vector<int> shuffle(vector<int> &A) {
  int N = A.size();
  vector<int> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}

void test() {
  VI P(N*M);
  REP(i,N*M) P[i]=i;
  do {
    set<II> S;
    vector<II> X(1,{0,0});
    FOR(i,1,N*M) {
      II pre=X.back();
      int r=P[i]/M,c=P[i]%M;
      S.emplace(r-pre.first, c-pre.second);
      X.emplace_back(r,c);
    }
    if(SZ(S)==N*M-1) {
      dumpc(X);
    }
  } while(next_permutation(P.begin()+1,P.end()));
}

set<II> viz;
VI res;
bool dfs(VI &cur, VI &X) {
  if(X.empty()) {
    res=cur;
    return true;
  }
  int maxcnt=10;
  while(maxcnt--) {
    int p2=X.back(),p1=cur.back();
    int dr=p2/M-p1/M,dc=p2%M-p1%M;
//    dump(dr,dc);
    assert(dr<N&&dc<M);
    if(viz.count({dr,dc})==0) {
      viz.emplace(dr,dc);
      X.pop_back(),cur.push_back(p2);
      if(dfs(cur,X)) return true;
      viz.erase({dr,dc});
      X.push_back(p2),cur.pop_back();
    }
    VI Y=shuffle(X);
    X=Y;
  }
  return false;
}

void solve_tle() {
  viz.clear();
  VI cur={0};
  VI X; FOR(i,1,N*M) X.push_back(i);
  X=shuffle(X);
  if(dfs(cur, X)) {
    REP(i,SZ(res)) println("%d %d", res[i]/M+1, res[i]%M+1);
  } else {
    println("-1");
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  /*
  N=2,M=4;
  test();*/
  
  cin>>N>>M;
  solve();
  
  return 0;
}
