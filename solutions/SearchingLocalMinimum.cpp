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

// $ cp-batch SearchingLocalMinimum | diff SearchingLocalMinimum.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SearchingLocalMinimum.cpp && ./a.out

/*

 2/7/2021

 7:30-8:10 WA
 8:22 AC

 https://codeforces.com/blog/entry/87598

 */

int N;

const bool LOCAL=0;
const int MAX_N=1e6;
int A[MAX_N];

const int UP=2,VA=1,DOWN=0;
const int Inf=1e8;
int qcnt=0;
int ask(int i) {
  assert(++qcnt<=100);
  if(LOCAL) {
    return A[i];
  }

  cout<<"? "<<i+1<<endl;
  int res; cin>>res;
  return res;
}

int check(int i) {
  int l=i==0?Inf:ask(i-1);
  int m=ask(i);
  int r=i==N-1?(Inf+1):ask(i+1);
  if(l<m&&m<r) return UP;
  if(l>m&&m<r) return VA;
  return DOWN;
  //dump(l,m,r,i);
  //assert(false);
}

void ans(int k) {
  cout<<"! "<<k+1<<endl;
}

void solve() {
  qcnt=0;
  int l=0,r=N;
  while(qcnt<98) {
    int m=(l+r)/2;
    int res=check(m);
    if(res==VA) {
      //dump(qcnt);
      ans(m);
      return;
    }
    (res==UP?r:l)=m;
  }
  assert(false);
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
// tested at https://github.com/hiroshi-maybe/leetcode/blob/master/384-Shuffle-an-Array/ShuffleArray.cpp
template <typename Integer>
vector<Integer> shuffle(vector<Integer> &A) {
  int N = A.size();
  vector<Integer> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}
void test() {
  N=(int)1e5;//genRandNum(1,(int)1e5);
  VI as(N); iota(ALL(as),1);
  as=shuffle(as);
  cout<<N<<endl;
  REP(i,N) cout<<A[i]<<" ";
  cout<<endl;
  REP(i,N) A[i]=as[i];
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  if(!LOCAL) cin>>N;
  /*REP(i,100000) cout<<i+1<<" ";
  cout<<endl;*/

  //while(true) test();

  /*if(LOCAL) {
    REP(i,N) A[i]=i+1;
  }*/
  solve();

  return 0;
}
