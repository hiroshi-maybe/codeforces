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

// $ cp-batch MakeThemEqual | diff MakeThemEqual.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address MakeThemEqual.cpp && ./a.out

/*

 9/27/2020

 9:25-9:47, 9:56-10:30 give up
 16:50-17:32 AC after reading editorials

 https://twitter.com/hanseilimak/status/1310457862963904512
 https://codeforces.com/blog/entry/83036

 https://twitter.com/kzyKT_M/status/1310265154622255104
 https://twitter.com/laycrs/status/1310266660150898688

 */

const int MAX_N=1e6+1;
LL A[MAX_N];
int N;

void solve() {
  LL tot=accumulate(A+1,A+N+1,0LL);
  if(tot%N!=0) {
    cout<<-1<<endl;
    return;
  }

  vector<tuple<int,int,LL>> res;
  auto mv=[&](int i, int j, LL x) {
    res.emplace_back(i,j,x);
    A[i]-=(LL)i*x;
    A[j]+=(LL)i*x;
  };

  FORE(i,2,N) {
    // Encoutered a sh**** bug. Without this check, try to move 2 from A[1] to A[2]
    if(A[i]%i) {
      LL x=i-(A[i]%i);
      //dump(i,x,A[1],A[i]);
      mv(1,i,x);
    }
    assert(A[i]%i==0);
    assert(A[i]>=0);
    assert(A[1]>=0);
    mv(i,1,A[i]/i);
    assert(A[i]==0);
  }

  LL t=tot/N;
  FORE(i,2,N) {
    mv(1,i,t);
  }

  cout<<SZ(res)<<endl;
  REP(k,SZ(res)) {
    int i,j; LL x; tie(i,j,x)=res[k];
    cout<<i<<" "<<j<<" "<<x<<endl;
  }
  FORE(i,1,N) assert(A[i]==t);
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
  N=genRandNum(1,(int)10);
  VI as=genRandSeq(N,1,(int)10);
  REP(i,N) A[i+1]=as[i];
  dumpc(as);
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,N) cin>>A[i+1];
    solve();
  }

  return 0;
}
