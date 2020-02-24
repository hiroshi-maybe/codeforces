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

// $ cp-batch Homecoming | diff Homecoming.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Homecoming.cpp && ./a.out

/*
 
 2/23/2020
 
 8:12-8:41 WA on system test
 
 17:00-18:24 AC
 
 */

//const int MAX_N=1e6+1;
int N;
LL A,B,P;
string S;

LL cost(int c) {
  return c==0?A:B;
}
int solve() {
  S.pop_back();
  N=SZ(S);
//  dump(S);
  if(N==0) return 1;
  vector<pair<LL,char>> rl;
  REP(i,N) {
    char c=S[i];
    if(rl.empty()||rl.back().second!=c) rl.emplace_back(0,c);
    rl.back().first++;
  }
  char c=rl.front().second=='B';
  vector<LL> costs(SZ(rl));
  REP(i,SZ(rl)) {
    costs[i]=cost(c);
    c^=1;
  }
//  dumpc(costs);
  int M=SZ(rl);
  vector<LL> X(M+1);
  X[M]=0;
  LL p=P;
  for(int i=M-1; i>=0; --i) {
    p-=costs[i];
    X[i]=p;
  }
//  dumpc(X);
  int res=0;
  REPE(i,M) {
    if(X[i]>=0) {
      return res+1;
    }
    res+=rl[i].first;
  }
  assert(false);
}

int correct() {
  int n=SZ(S);
  vector <LL> ans(n);
  ans[n - 1] = 0;
  char now = 'n';
  for (int i = n - 2; i > -1; i--) {
      if (S[i] == now) {
          ans[i] = ans[i + 1];
      }
      else {
          if (S[i] == 'A') {
              ans[i] = ans[i + 1] + A;
              now = 'A';
          } else {
              ans[i] = ans[i + 1] + B;
              now = 'B';
          }
      }
  }
//  dumpc(ans);
  for (int i = 0; i < n; i++) {
      if (ans[i] <= P) {
        return i + 1;
      }
  }
}

#include <chrono>
#include <random>
// mt19937_64 for 64 bit unsigned integer
//mt19937 rnd(time(nullptr));
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
  N=genRandNum(2,100000);
  A=genRandNum(1,100000);
  B=genRandNum(1,100000);
  P=genRandNum(1,100000);
  VI seq=genRandSeq(N,0,2);
  S=string(N,'A');
  REP(i,N) S[i]='A'+seq[i];
  
  dump(N,A,B,P,S);
  int exp=correct(),act=solve();
  
  if(exp!=act) {
    dump(exp,act);
  }
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  int T; cin>>T;
  REP(i,T) {
    cin>>A>>B>>P>>S;
    cout<<solve()<<endl;
  }
  
  return 0;
}
