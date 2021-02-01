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

// $ cp-batch NezzarAndSymmetricArray | diff NezzarAndSymmetricArray.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address NezzarAndSymmetricArray.cpp && ./a.out

/*

 1/28/2021

 7:11-8:31 WA
 8:41 WA

 1/31/2021

 15:40-16:18 AC

 https://twitter.com/hanseilimak/status/1356042807232798721

 https://codeforces.com/blog/entry/87294
 https://twitter.com/prd_xxx/status/1354834846749605888
 https://twitter.com/kzyKT_M/status/1354835551879192576

 */

const int MAX_N=1e6+1;
LL D[MAX_N];
int N;

bool solve() {
  map<LL,int> cnt;
  REP(i,2*N) {
    if(D[i]==0) return false;
    if(D[i]%2==1) return false;
    cnt[D[i]]++;
  }
  vector<LL> xs;
  FORR(kvp,cnt) {
    if(kvp.second!=2) return false;
    xs.push_back(kvp.first);
  }
  assert(SZ(xs)==N);
  //dumpc(xs);

  // Bug during the contest...
  // if(xs.back()%N!=0) return false;

  if(xs.back()%(2*N)!=0) return false;

  vector<LL> as(N);
  as[N-1]=xs.back()/(2*N);
  LL sum=as[N-1];
  for(int i=N-2; i>=0; --i) {
    LL d=xs[i]/2-sum;
    if(d%(i+1)!=0) return false;
    d/=i+1;
    if(d<=0) return false;
    as[i]=d,sum+=as[i];
  }

  //dumpc(as);
  /*
  REP(i,SZ(xs)-1) {
    LL di=xs[i],dii=xs[i+1];
    LL d=dii-di;
    assert(d%2==0);
    d/=2;
    if(d%(i+1)!=0) return false;
  }*/
  set<LL> S(ALL(as));
  return SZ(S)==N;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,2*N) cin>>D[i];
    cout<<(solve()?"YES":"NO")<<endl;
  }

  return 0;
}
