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

// $ cp-batch BeautifulArray | diff BeautifulArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BeautifulArray.cpp && ./a.out

/*
 
 4/22/2019
 
 8:26-9:11 WA on test case #10
 10:10 give up
 
 I tried to combine with Kadane's algorithm. However no luck.
 
 5/6/2019
 
 22:15-22:41 read editorials and got AC
 
 https://codeforces.com/blog/entry/66687
 https://cinnamo-coder.hatenablog.com/entry/2019/04/23/165615
 
 If we can transform subsegments constant time, automata dp works.
 Also it can be combined with other dp (Kadane's max subsegment in this problem)
 
 */

const int MAX_N=1e6+1;
LL X,A[MAX_N];
int N;

LL dp[MAX_N][3];
LL solve() {
  ZERO(dp);
  LL res=0;
  REP(i,N) {
    // 0->0
    SMAX(dp[i+1][0],max(dp[i][0]+A[i],A[i]));
    // 0->1
    SMAX(dp[i+1][1],max(dp[i][0]+A[i]*X,A[i]*X));
    // 1->1
    SMAX(dp[i+1][1],max(dp[i][1]+A[i]*X,A[i]*X));
    // 1->2
    SMAX(dp[i+1][2],max(dp[i][1]+A[i],A[i]));
    // 2->2
    SMAX(dp[i+1][2],max(dp[i][2]+A[i],A[i]));
    
    SMAX(res,max({dp[i+1][0],dp[i+1][1],dp[i+1][2]}));
  }
  return res;
}

LL kadane(int l, int r) {
  LL res=0,cur=0;
  FOR(i,l,r) {
    cur=max({0LL,cur+A[i],A[i]});
    SMAX(res,cur);
  }
  return res;
}
LL solve_wrong() {
  if(X>=0) {
    LL res=kadane(0,N);
    res=max(res,X*res);
    return res;
  } else {
    LL res=kadane(0,N);
    vector<II> I;
    LL minv=0,cur=0; int l=0;
    REP(i,N) {
      cur+=A[i];
      if(cur<=minv) {
        if(cur<minv) I.clear();
        I.emplace_back(l,i+1);
        minv=cur;
      } else if(cur>=0) {
        l=i+1,cur=0;
      }
    }
    dumpc(I);
    vector<pair<LL,int>> I2(N,{0,-1});
    FORR(p,I) {
      LL sum=0;
      FOR(i,p.first,p.second) sum+=A[i]*X;
      I2[p.first]={sum,p.second};
      dump(p.first,p.second,sum);
    }
    ZERO(dp);
    REP(i,N)REP(j,2) {
      SMAX(dp[i+1][j],max(A[i],dp[i][j]+A[i]));
      SMAX(res,dp[i+1][j]);
      if(j==0&&I2[i].second!=-1) {
        int ii=I2[i].second;
        SMAX(dp[ii][1],dp[i][j]+I2[i].first);
        dump(i,ii,dp[ii][1]);
        SMAX(res,dp[ii][1]);
      }
    }
    dump(dp[5][0],dp[8][1]);
//    dump(res,dp[N][0]);
//    assert(dp[N][0]==res);
    return res;
  }
}

LL B[MAX_N];
LL f() {
//  dump(N,X);
  LL res=kadane(0,N);
  REP(i,N) B[i]=A[i];
  REP(l,N)FORE(r,l+1,N) {
    dump(l,r);
    FOR(i,l,r) A[i]*=X;
    LL z=kadane(0,N);
    dump(l,r,z);
    dumpC(A,A+N);
    SMAX(res,z);
    FOR(i,l,r) A[i]=B[i];
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
  N=10;
  VI as=genRandSeq(N,-10,11);
  REP(i,N) A[i]=as[i];
  X=genRandNum(-5,6);
  
  dumpc(as);
  LL a=f(),b=solve();
  if(a!=b) {
    dump(X,a,b);
    dumpc(as);
  }
  assert(a==b);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true)test();
  
  cin>>N>>X;
  REP(i,N) cin>>A[i];
  cout<<solve()<<endl;
//  cout<<f()<<endl;
  
  return 0;
}
