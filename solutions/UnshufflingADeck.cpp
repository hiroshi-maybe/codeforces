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

// $ cp-batch UnshufflingADeck | diff UnshufflingADeck.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address UnshufflingADeck.cpp && ./a.out

/*

 10/10/2020

 9:19-10:05 AC

 https://twitter.com/hanseilimak/status/1318435429339688963
 https://codeforces.com/blog/entry/83553

 */

const int MAX_N=1e2+1;
int C[MAX_N];
int N;

VI build(VI A, int a) {
  VI res={0};
  REP(i,N) {
    res.back()+=1;
    if(A[i]<=a) res.push_back(0);
  }
  if(res.back()==0) res.pop_back();
  return res;
}

void solve() {
  bool tor=(N%2)==0;

  VV<int> ans;

  FORE(a,1,N) {
    int k=-1;
    REP(i,N) if(C[i]==a) k=i;
    assert(k!=-1);
    VI A(C,C+N);
    VI res;
    if(tor) {
      res=build(A, a);
    } else {
      reverse(ALL(A));
      res=build(A, a);
      reverse(ALL(res));
    }

    tor^=1;

    if(SZ(res)<2) continue;

    ans.push_back(res);

    VV<int> xs;
    int i=0;
    FORR(cnt,res) {
      VI ys;
      while(cnt--) {
        ys.push_back(C[i++]);
      }
      xs.push_back(ys);
    }
    reverse(ALL(xs));
    VI cc;
    FORR(ns,xs) FORR(n,ns) cc.push_back(n);
    assert(SZ(cc)==N);
    //dumpc(cc);
    REP(i,N) C[i]=cc[i];
  }

  REP(i,N) assert(C[i]==i+1);

  cout<<SZ(ans)<<endl;
  FORR(res,ans) {
    cout<<SZ(res)<<" ";
    REP(i,SZ(res)) cout<<res[i]<<" ";
    cout<<endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N;
  REP(i,N) cin>>C[i];
  solve();

  return 0;
}
