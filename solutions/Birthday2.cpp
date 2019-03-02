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

// $ cp-batch Birthday2 | diff Birthday2.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Birthday2.cpp && ./a.out

/*
 
 2/23/2019
 
 3:04-3:40 give up
 
 3/1/2019
 
 18:15-19:32 Read editorial and got AC
 
 Sort the array first and make a cycle by connecting adjacent elements in an array.
 In a cycle, A[i] must be adjacent to exactly two elements.
 One potential optimal way to minimize maximum gap is arranging the array to be adjacent to two neighbored elements as below:
 
 .., A[i-1], A[i], A[i+1], ..
 
 However in this arrangement, gap between A[N-1] and A[0] gives large gap.
 Next strategy is putting elements with at most two adjacent elements as below:
 
 .., A[i-2], A[i], A[i+2], ..
 
 The first element and last element has A[i+1] or A[i-1] as an adjacent element.
 This arrangement is possible to construct.
 
 Let's show that this is optimal.
 Suppose gap between A[i-2] and A[i] is large and we want to make arrangement like
 
 .., A[i-2], A[i-1], A[i], ..
 
 However in this case we need to somehow connect A[i-3] and A[i+1] to make a cycle.
 The gap is larger than A[i] - A[i-2]. Thus below arrangement is optimal:
 
 A[0], A[1], A[3], A[5], .., A[N-1], A[N-2], A[N-4], .., A[2]
 
 https://codeforces.com/blog/entry/65487
 
 */

const int MAX_N=1e3+1;
LL A[MAX_N];
int N;

void solve() {
  sort(A,A+N);
  deque<int> Q;
  REP(i,N) {
    if(i%2==0) Q.push_back(A[i]);
    else Q.push_front(A[i]);
  }
  REP(i,N) {
    printf("%d ", Q.front()),Q.pop_front();
  }
  println("");
}

LL f(VI &X) {
  int res=0;
  REP(i,SZ(X)) SMAX(res,abs(X[i]-X[(i+1)%N]));
  return res;
}
void test() {
  VI A={1,30,32,49,60,65,72,100};
  N=SZ(A);
  VI P(N); REP(i,N)P[i]=i;
  
  LL res=1e8; VI xs;
  do {
    VI B(N);
    REP(i,N)B[i]=A[P[i]];
    if(f(B)<res) res=f(B),xs=B;
  } while(next_permutation(ALL(P)));
  dump(res);
  dumpc(xs);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
