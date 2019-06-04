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

// $ cp-batch EhabAndTheExpectedXORProblem | diff EhabAndTheExpectedXORProblem.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address EhabAndTheExpectedXORProblem.cpp && ./a.out

/*
 
 6/3/2019
 
 7:30-9:10 give up
 9:20-10:10 read solutions from twitter timeline and got AC
 
 https://codeforces.com/blog/entry/67388
 https://twitter.com/btk15049/status/1135579718055411714
 https://twitter.com/tempura_cpp/status/1135578865793765381
 https://twitter.com/kyort0n/status/1135579268119842816
 https://twitter.com/xuzijian629/status/1135579196468547585
 https://twitter.com/mistter_gp/status/1135579140281606145

 A[i] does NOT need to be distinct 😡
 Read samples 😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡😡
 
 Very very very typical technique of prefix XOR is the first step.
 
 A[l..r] != 0 <=> A[0..l]^A[0..r] != 0
 
 a) X>=2^N
 
 In this case, what we should avoid is A[0..i] != A[0..j] for i=0..j-1
 Suppose we have cum[0]=001,cum[1]=010,cum[2]=011,..,cum[2^N-2]=111
 Then we can restore A from cum[0..2^N-2].
 This should be optimal because it includes all the possible digit numbers except `0`.
 
 Thus L=2^N-1, A={1,2 xor 1,3 xor 2,4 xor 3,..,(2^N-1) xor (2^N-2)}
 
 b) X<2^N
 
 Basic process is almost same as case #a. However we should add the other condition.
 
 A[0..i] xor A[0..j] != X for i=0..j-1
 
 Since X>=1, we can choose MSB(X) and collect subset of `cum` in case #a.
 We can remove numbers which satisfies (cum[i]>>MSB(X))&1 and get L = 2^(N-1)-1
 Suppose we are adding 1<<MSB(X) to the subset. Since we have all the bit patterns without MSB(X), X xor (1<<MSB(X)) should be part of our sebset. 1<<MSB(X) xor (X xor (1<<MSB(X))) = X. Since this happens for any number `y` without MSB(X) bit for 1<<MSB(X) | y, the subset is optimal.
 
 */

//const int MAX_N=1e6+1;
//LL A[MAX_N];
int N,X;

bool kth(int a, int i) {
  return (a>>i)&1;
}

void solve() {
  int k=20;
  if(X<(1<<N)) {
    REP(i,N) if((X>>i)&1) k=i;
  }
  
  VI cum;
  FOR(n,1,1<<N) if(!kth(n,k)) cum.push_back(n);
  VI res;
  if(SZ(cum)>0) {
    res={cum[0]};
    FOR(i,1,SZ(cum)) res.push_back(cum[i]^cum[i-1]);
  }
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%d ",res[i]);
  if(SZ(res))println("");
}

bool ok(VI &A, int X) {
  int M=SZ(A);
  REP(i,M)FORE(j,i+1,M) {
    int x=0;
    FOR(k,i,j) x^=A[k];
    if(x==X||x==0) return false;
  }
  return true;
}
void test() {
  X=100,N=3;
  VI A; REP(i,1<<N) if(i!=0&&i!=X) A.push_back(i);
  map<int,VV<int>> ans;
  int M=SZ(A);
  int full=1<<M;
  int maxl=0;
  REP(mask,full) {
    VI B; REP(i,M)if((mask>>i)&1) B.push_back(A[i]);
    do {
      if(ok(B,X)) {
        ans[SZ(B)].push_back(B);
        SMAX(maxl,SZ(B));
      }
    } while(next_permutation(ALL(B)));
  }
  dump(maxl,SZ(ans[maxl]));
  FORR(as,ans[maxl]) dumpc(as);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  test();
  
  cin>>N>>X;
  solve();
  
  return 0;
}
