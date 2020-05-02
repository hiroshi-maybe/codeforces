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

// $ cp-batch PhoenixAndScience | diff PhoenixAndScience.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PhoenixAndScience.cpp && ./a.out

/*
 
 5/1/2020
 
 8:56-11:03 AC
 
 https://codeforces.com/blog/entry/76555
 https://twitter.com/hanseilimak/status/1256280099759898625
 https://codeforces.com/contest/1348/submission/78696877
 https://codeforces.com/contest/1348/submission/78692108
 https://twitter.com/laycrs/status/1256268565990137856
 https://twitter.com/kzyKT_M/status/1256268997810503680
 
 */

LL N;

int hb(LL x) {
  int res=0;
  while(x>0) ++res,x/=2;
  return res;
}
LL hb2(LL rem, int x) {
  if(x==1) return rem;
  return rem/2LL/(x-1);
}

void solve() {
  LL rem=N-1;
  LL cur=1;
  int L=hb(N);
  vector<LL> res={1};
  REP(i,L-1) {
    LL turn=L-i-1;
    LL h=min(2LL*cur,rem/turn);
    rem-=h,res.push_back(h);
    cur=h;
  }
  LL sum=accumulate(ALL(res),0LL);
  dumpc(res);
  dump(sum,N);
  assert(sum==N);
    
//  assert(rem==0);
  cout<<SZ(res)-1<<endl;
  REP(i,SZ(res)-1) cout<<res[i+1]-res[i]<<" ";
  cout<<endl;
}

void solve_org() {
  LL rem=N;
  LL cnt=1;
  int L=hb(N);
  dump(L);
  vector<LL> res={1};
  REP(i,L-1) {
    rem-=cnt;
    int x=L-i-1;
    LL cnt2=min(hb2(rem,x),2LL*cnt);
    dump(i,x,rem,cnt2);
    res.push_back(cnt2);
    cnt=cnt2;
  }
  LL sum1=accumulate(ALL(res),0LL);
  dump(sum1,cnt,rem,N-sum1);
  
  dumpc(res);
  LL sum=accumulate(ALL(res),0LL);
  dump(rem,sum,N);
  assert(sum==N);
  
//  assert(rem==0);
  cout<<SZ(res)-1<<endl;
  REP(i,SZ(res)-1) cout<<res[i+1]-res[i]<<" ";
  cout<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int t; cin>>t;
  while(t--) {
    cin>>N;
    solve();
  }
  
  return 0;
}
