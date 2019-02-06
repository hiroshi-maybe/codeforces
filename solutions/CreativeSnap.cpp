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

// $ cp-batch CreativeSnap | diff CreativeSnap.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CreativeSnap.cpp && ./a.out

/*
 
 2/3/2019
 
 7:55-8:28 AC
 
 https://codeforces.com/blog/entry/64989
 https://misteer.hatenablog.com/entry/CF537
 
 I did coordinate compression though, it's not necessary if we know only # of elements.
 
 0:0
 1:0
 2:3
 4:0
 5:2
 6:0
 ...
 
 <=> 2,2,2,5,5,..
 
 We can binary search # of elements by difference of indices.
 
 */

const int MAX_N=1e6+1;
LL A[MAX_N],C1,C2;
int N,K,L;

int keys[MAX_N];
LL vals[MAX_N],cum[MAX_N];
LL f(int l, int r) {
  if(r<=l) return 0;
  int low=lower_bound(keys,keys+L,l)-keys,hi=lower_bound(keys,keys+L,r)-keys;
  LL sum=cum[hi]-cum[low];
//  dump(l,r,sum,low,hi);
  if(sum==0) return C1;
  
  LL res=sum*(r-l)*C2;
  if(r-l==1) return res;
  
  int m=(l+r)/2;
  SMIN(res,f(l,m)+f(m,r));
  return res;
}
void solve_org() {
  map<int,int> M;
  REP(i,K) M[A[i]]++;
  L=0;
  FORR(kvp,M) {
    keys[L]=kvp.first;
    vals[L]=kvp.second;
    ++L;
  }
  REP(i,L) cum[i+1]=cum[i]+vals[i];
  
  /*
  dumpC(keys,keys+L);
  dumpC(vals,vals+L);
  dumpC(cum,cum+L+1);
*/
  
  LL res=f(0,1<<N);
  cout<<res<<endl;
}

LL g(int l, int r) {
  LL cnt=lower_bound(A,A+K,r)-lower_bound(A,A+K,l);
  LL res=cnt==0?C1:C2*cnt*(r-l);
  if(r-l==1) return res;
  if(cnt==0) return res;
  int m=(l+r)/2;
  SMIN(res,g(l,m)+g(m,r));
  return res;
}
void solve() {
  sort(A,A+K);
  cout<<g(0,1<<N)<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>K>>C1>>C2;
  REP(i,K) cin>>A[i],A[i]--;
  solve();
  
  return 0;
}
