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

// $ cp-batch SillyMistake | diff SillyMistake.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SillyMistake.cpp && ./a.out

/*
 
 11/16/2019
 
 6:48-7:14 WA
 7:17 AC
 
 11/17/2019
 
 Add simpler solution
 https://codeforces.com/blog/entry/71489
 
 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void nope() { cout<<-1<<endl; exit(0); }
void solve() {
  VI res;
  SETI viz, in;
  int cnt=0;
  REP(i,N) {
    int a=abs(A[i]);
    if(A[i]>0) {
      if(viz.count(a)) nope();
      in.emplace(a),viz.emplace(a);
    } else {
      if(!in.count(a)) nope();
      in.erase(a);
    }
    ++cnt;
    if(in.empty()) {
      res.push_back(cnt),cnt=0;
      viz.clear();
    }
  }
  if(SZ(in)) nope();
  println("%d", SZ(res));
  REP(i,SZ(res)) printf("%d ", res[i]);
  println("");
}

void solve_org() {
  VI X;
  MAPII cnt;
  REP(i,N) {
    int a=abs(A[i]);
    if(A[i]>0) {
      cnt[a]++;
    } else {
      cnt[a]--;
    }
//    dump(i,a,cnt[a]);
    if(cnt[a]>1||cnt[a]<0) {
      cout<<-1<<endl;
      return;
    }
    if(cnt[a]==0) cnt.erase(a);
    if(SZ(cnt)==0) X.push_back(i);
  }
//  dumpc(cnt);
  if(SZ(cnt)!=0) {
    cout<<-1<<endl;
    return;
  }
  assert(SZ(X)>0);
    
  int j=0;
  REP(i,N) {
    int a=A[i];
    if(a>0) {
      cnt[a]++;
    }
    if(i==X[j]) {
      FORR(kvp,cnt) if(kvp.second>1) {
        cout<<-1<<endl;
        return;
      }
      cnt.clear();
      ++j;
    }
  }
  
//  dumpc(X);
  println("%d", SZ(X));
  REP(i,SZ(X)) {
    int x=(i==0)?(X[0]+1):(X[i]-X[i-1]);
    printf("%d ", x);
  }
  println("");
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N;
  REP(i,N) cin>>A[i];
  solve();
  
  return 0;
}
