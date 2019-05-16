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
template<class Iter> void __kumaerrc(Iter begin, Iter end) { for(; begin!=end; ++begin) { cerr<<*begin<<' '; } cerr<<endl; }
void __kumaerr(istream_iterator<string> it) { (void)it; cerr<<endl; }
template<typename T, typename... Args> void __kumaerr(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<"="<<a<<", ",__kumaerr(++it, args...); }
template<typename S, typename T> std::ostream& operator<<(std::ostream& _os, const std::pair<S,T>& _p) { return _os<<"{"<<_p.first<<','<<_p.second<<"}"; }
#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ' '; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch ThePartyAndSweets | diff ThePartyAndSweets.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThePartyAndSweets.cpp && ./a.out

/*
 
 5/12/2019
 
 8:25-8:54 WA on test case #7 forever
 9:35 give up
 
 14:35-15:35 read solutions and got AC
 
 I missed the case where max{B}=min{G}. Fxck 😡
 In this case, max{B} can hold all G[i].
 
 https://codeforces.com/blog/entry/66993
 
 */

const int MAX_N=1e6+1;
LL B[MAX_N],G[MAX_N];
int N,M;

LL solve() {
  sort(B,B+N),reverse(B,B+N);
  sort(G,G+M),reverse(G,G+M);
  LL maxb=*max_element(B,B+N),ming=*min_element(G,G+M);
  if(maxb>ming) return -1;
  LL sumb=accumulate(B,B+N,0LL);
  LL res=sumb*M;
  REP(i,M-1) res-=maxb,res+=G[i];
  if(maxb==ming) res-=maxb,res+=G[M-1];
  else res-=B[1],res+=G[M-1];
  return res;
}


LL solve_org() {
  sort(B,B+N),reverse(B,B+N);
  sort(G,G+M),reverse(G,G+M);
  LL maxb=*max_element(B,B+N),ming=*min_element(G,G+M);
  if(maxb>ming) return -1;
  LL sumb=accumulate(B,B+N,0LL);
  LL res=sumb*M;
  VI cnt(N,0);
//  dump(res);
  int j=0;
  REP(i,M) {
    LL g=G[i];
    if(j<N) {
      int b=B[j];
      if(b==g) continue;
      if(cnt[j]==M-1) ++j; // move here
      b=B[j];
//      dump(i,j,res);
      if(b<g&&cnt[j]<M-1) {
        res-=b,res+=g,++cnt[j];
        // this check should happen after confirming last one is not equal to `g`
        //if(cnt[j]==M-1) ++j;
        continue;
      }
    }
    return -1;
  }
  return res;
}

LL correct() {
  LL res=0;
  for(int i=0; i<N; ++i) res+=M*B[i];
  
  sort(B, B+N);
  for(int i=0, cnt=0; i<M; ++i) {
    G[i]-=B[N-1];
    if (G[i]<0) { res=-1; break; }
    res+=G[i];
    if (G[i]>0) ++cnt;
    if (cnt==M) res+=B[N-1]-B[N-2];
  }
  return res;
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
  N=genRandNum(2,5),M=genRandNum(2,5);
  VI bs,gs;
  bs=genRandSeq(N,0,10),gs=genRandSeq(M,0,10);
  REP(i,N) B[i]=bs[i];
  REP(i,M) G[i]=gs[i];
  LL a=solve(),b=correct();
  if(a!=b) {
    dump(a,b);
    dumpc(bs);
    dumpc(gs);
  }
  assert(a==b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>N>>M;
  REP(i,N) cin>>B[i];
  REP(i,M) cin>>G[i];
  cout<<solve()<<endl;
  
  return 0;
}
