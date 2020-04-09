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

// $ cp-batch ChallengesInSchool41 | diff ChallengesInSchool41.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ChallengesInSchool41.cpp && ./a.out

/*
 
 4/8/2020
 
 9:16-10:20, 11:30-12:50 TLE
 20:30-20:47 AC
 23:48 add simpler solution inspired by @betrue12
 
 https://twitter.com/laycrs/status/1247926256953200642
 https://twitter.com/hanseilimak/status/1248137852010946561
 https://codeforces.com/contest/1333/submission/75869017 by @betrue12
 https://codeforces.com/contest/1333/submission/75874751 by @hitonanode
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.r93acxpmq5gp
 
 */

string S;
int N,K;

void nope() {
  println("-1");
//  exit(0);
}
void solve() {
  VV<int> steps;
  int rem=0;
  while(true) {
    VI xs;
    REP(i,N-1) if(S[i]=='R'&&S[i+1]=='L') {
      xs.push_back(i);
    }
    FORR(x,xs) swap(S[x],S[x+1]);
    if(xs.empty()) break;
    steps.push_back(xs);
    rem+=SZ(xs);
  }
  if(K>rem||SZ(steps)>K) {
    nope();
    return;
  }
  REP(i,SZ(steps)) if(rem>0) {
    VI xs=steps[i];
    while(SZ(xs)) {
      int cnt=min(SZ(xs),rem-(K-1));
      assert(cnt>0);
      rem-=cnt,--K;
      printf("%d ", cnt);
      while(cnt--) printf("%d ", xs.back()+1),xs.pop_back();
      println("");
    }
  }
  assert(rem==0&&K==0);
}
void solve_original() {
  vector<II> ps;
  int cntr=0;
  int lb=-1,hb=0,cont=0;
  REP(i,N) {
    if(S[i]=='L') {
      int a=i-SZ(ps)+cont;
      ps.emplace_back(i,cntr),SMAX(lb,a),hb+=cntr;
      cont++;
    } else cntr++,cont=0;
  }
  dump(lb,K,hb)
  if(lb>K) {
    nope();
    return;
  }
  if(hb<K) {
    nope();
    return;
  }
  int k=K;
  assert(SZ(ps));
  VV<int> fuck;
  while(k<hb) {
    VI x;
    --k;
    REP(i,SZ(ps)) {
      int p=ps[i].first;
      if(p>0&&S[p-1]=='R'&&k<hb) {
        x.push_back(i),--hb;
      }
      if(k>=hb) break;
    }
    dumpc(x);
    if(x.empty()) {
      nope();
      return;
    }
    assert(SZ(x));
    VI fuckfuck;
    REP(i,SZ(x)) {
      int p=ps[x[i]].first;
      assert(p>0);
      fuckfuck.push_back(p);
    }
    fuck.push_back(fuckfuck);
    FORR(i,x) {
      swap(S[ps[i].first],S[ps[i].first-1]);
      ps[i].first-=1,ps[i].second-=1;
    }
    dump(S,k,hb);
    dumpc(ps);
  }
  FORR(f,fuck) {
    printf("%d ", SZ(f));
    FORR(ff,f) printf("%d ", ff);
    println("");
  }
  REP(i,SZ(ps)) {
    while(ps[i].first>i) {
      assert(k>0);
      if(i>0) assert(ps[i-1].first!=ps[i].first-1);
      dump(i,ps[i].first);
      int p=ps[i].first;
      println("1 %d", p);
      assert(p>0);
      swap(S[p-1],S[p]);
      ps[i].first-=1,ps[i].second-=1;
      --k;
      dump(k,S);
    }
  }
  REP(i,SZ(S)) if(S[i]=='L') assert(i<SZ(ps));
  dump(S);
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
void test() {
//  N=3000;
//  K=2250000;//genRandNum(1,N*N/2);
  N=100;
  K=genRandNum(1,N*N/2);
  VI A=genRandSeq(N,0,2);
  S=string(N,'R');
  REP(i,N)if(A[i]) S[i]='L';
//  REP(i,N)if(i>=1500) S[i]='L';
  dump(K,N,S);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
//  while(true) test();
  
  cin>>N>>K>>S;
  solve();
  
  return 0;
}
