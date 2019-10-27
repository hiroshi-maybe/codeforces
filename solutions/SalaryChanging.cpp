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

// $ cp-batch SalaryChanging | diff SalaryChanging.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SalaryChanging.cpp && ./a.out

/*
 
 10/24/2019
 
 9:17-10:05 give up
 
 10/26/2019
 
 17:45-17:50, 22:30-23:05 read editorial and got AC
 
 https://codeforces.com/blog/entry/70860
 https://twitter.com/hanseilimak/status/1188337860895637504
 
 */

const int MAX_N=1e6+1;
LL SC,A[MAX_N],L[MAX_N],R[MAX_N];
int N;

const LL Inf=1e15;
bool ok(LL x) {
  int m=N/2;
  VI S,A,B;
  REP(i,N) {
    if(R[i]<x) A.push_back(i);
    else if(x<L[i]) B.push_back(i);
    else S.push_back(i);
  }
  if(SZ(S)+SZ(B)<m+1) return false;
  vector<pair<LL,int>> SS;
  REP(i,SZ(S)) SS.emplace_back(L[S[i]],S[i]);
  sort(ALL(SS));
  int cnt=0;
  LL cost=0;
  FORR(i,B) cost+=L[i],cnt++;
  REP(i,SZ(SS)-(m+1-cnt)) cost+=SS[i].first;
  cost+=x*(m+1-cnt);
  FORR(i,A) cost+=L[i];
  return cost<=SC;
}

bool ok_wrong(LL x) {
  int m=N/2;
  VI S,A;
  REP(i,N) {
    if(L[i]<=x&&x<=R[i]) S.push_back(i);
    else A.push_back(i);
  }
  if(SZ(S)<m+1) return false;
  vector<pair<LL,int>> SS;
  REP(i,SZ(S)) SS.emplace_back(L[S[i]],i);
  sort(ALL(SS));
  REP(i,SZ(SS)-(m+1)) A.push_back(SS[i].second);
  LL cost=x*(m+1);
  assert(SZ(A)==m);
  FORR(i,A) cost+=L[i];
  return cost<=SC;
}

void solve() {
  vector<LL> L2(L,L+N);
  sort(ALL(L2));
  LL good=L2[N/2],bad=Inf;
  while(abs(good-bad)>1) {
    LL mid=(good+bad)/2;
    bool res=ok(mid);
//    dump(mid,res);
    (res?good:bad)=mid;
  }
  cout<<good<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int T; cin>>T;
  REP(i,T) {
    cin>>N>>SC;
    REP(j,N)cin>>L[j]>>R[j];
    solve();
  }
  
  return 0;
}
