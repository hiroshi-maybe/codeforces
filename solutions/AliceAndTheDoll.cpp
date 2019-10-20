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

// $ cp-batch AliceAndTheDoll | diff AliceAndTheDoll.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AliceAndTheDoll.cpp && ./a.out

/*
 
 10/17/2019
 
 7:13-8:35 give up
 
 10/20/2019
 
 10:50-12:15 read editorials and got AC
 
 https://codeforces.com/blog/entry/70654
 https://twitter.com/hanseilimak/status/1185978525532033024
 
 
 */

const int MAX_N=1e6+1;
VI R[MAX_N],C[MAX_N];
int N,M,K;

void solve() {
  REP(i,N) sort(ALL(R[i]));
  REP(j,M) sort(ALL(C[j]));
  LL sum=1;
  int i=0,j=0,dir=0; // 0:R,1:D,2:L,3:U
  int r0=-1,r1=N,c0=-1,c1=M;
  int prevdel=-1,del=-1;
  while(del!=0||prevdel!=0) {
    prevdel=del,del=0;
    if(dir==0||dir==2) if(r0<i&&i<r1) {
      // hor
      if(dir==0) {
        // right
        auto it=upper_bound(ALL(R[i]),j);
        int hb=min(*it,c1);
        del=hb-j-1,r0=i,j=hb-1;
      } else {
        // left
        auto it=lower_bound(ALL(R[i]),j);
        --it;
        int lb=max(*it,c0);
        del=j-(lb+1),r1=i,j=lb+1;
      }
    }
    if(dir==1||dir==3) if(c0<j&&j<c1) {
      // ver
      if(dir==1) {
        // down
        auto it=upper_bound(ALL(C[j]),i);
        int hb=min(*it,r1);
        del=hb-(i+1),c1=j,i=hb-1;
      } else {
        // up
        auto it=lower_bound(ALL(C[j]),i);
        --it;
        int lb=max(*it,r0);
        del+=i-(lb+1),c0=j,i=lb+1;
      }
    }
//    dump(i,j,dir,r0,r1,c0,c1,sum);
    sum+=del;
    dir=(dir+1)%4;
  }
  bool res;
  if(sum==(LL)N*M-K) res=true;
  else res=false;
  cout<<(res?"Yes":"No")<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  REP(i,N) R[i].push_back(-1),R[i].push_back(M);
  REP(j,M) C[j].push_back(-1),C[j].push_back(N);
  REP(i,K) {
    int a,b; cin>>a>>b;
    --a,--b;
    R[a].push_back(b),C[b].push_back(a);
  }
  solve();
  
  return 0;
}
