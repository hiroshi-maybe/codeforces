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

// $ cp-batch FrogJumping | diff FrogJumping.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address FrogJumping.cpp && ./a.out

/*
 
 4/20/2019
 
 12:31-1:31 give up
 
 I focused on Bezout's identity. However I couldn't find a condition for [0,x].
 If we cannot go further than `x`, some of s*A-t*B are not reachable.
 
 20:20-22:20, 22:40-22:55 read editorials
 
 4/24/2019
 
 16:00-17:50 read editorials and got AC
 
 https://cinnamo-coder.hatenablog.com/entry/2019/04/22/014951
 https://twitter.com/ei1333/status/1119721845656133632
 https://twitter.com/n_vip/status/1119702337231015936
 
 It's tough to understand why A+B-1 can cover [0..A+B-1] all 😡
  - https://twitter.com/xuzijian629/status/1119798136736587776
 
 https://codeforces.com/blog/entry/66639
 
 Official editorial is looking at (X,D) for i (mod A) where X=necessary position to reach k*i , D=left most position when X is reached
 
 */

LL M,A,B;

LL gcd(LL a, LL b) { return b==0?a:gcd(b,a%b); }

// [0,x]
LL f(LL g, LL x) {
  LL res=x+1;
  LL L=x/g;
  res+=g*L*(L-1)/2;
  res+=(x-g*L+1)*L;
  return res;
}
const int MAX_N=1e6+1;
int viz[MAX_N];
void solve() {
  LL g=gcd(A,B);
  LL res=0;
  ZERO(viz);
  int cnt=0;
  viz[0]=1,++cnt;
  REPE(x,min(M,A+B)) {
    queue<int> Q;
    if(x-A>=0&&viz[x-A]) Q.emplace(x),viz[x]=1,++cnt;
    while(SZ(Q)) {
      int y=Q.front(); Q.pop();
      int yy=y;
      while(yy-B>=0) {
        yy-=B;
        if(!viz[yy]) Q.emplace(yy),viz[yy]=1,++cnt;
        else break;
      }
      while(yy+A<=x) {
        yy+=A;
        if(!viz[yy]) Q.emplace(yy),viz[yy]=1,++cnt;
        else break;
      }
    }
    res+=cnt;
//    dump(x,cnt);
//    dumpc(viz);
  }
//  dump(res);
  if(M>A+B) {
    LL a=f(g,M),b=f(g,A+B);
    res+=a-b;
  }
//  dump(res);
  cout<<res<<endl;
}

void solve_wrong() {
  LL g=gcd(A,B);
  LL res=0;
  dump(A,B,g);
  REPE(i,M) {
    LL maxs=i/A,sub=max(0LL,(A*maxs-B)/g);
    LL x;
    if(maxs>0) x=1+i/g-sub;
    else x=1;
    dump(i,maxs,sub,x);
    res+=x;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>M>>A>>B;
  solve();
  
  return 0;
}
