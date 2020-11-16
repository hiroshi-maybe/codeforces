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

// $ cp-batch PowerfulKsenia | diff PowerfulKsenia.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PowerfulKsenia.cpp && ./a.out

/*

 11/14/2020

 0:28-0:48 give up

 11/16/2020

 9:00-11:10 AC after reading the editorial

 https://twitter.com/hanseilimak/status/1328128702413230094

 https://codeforces.com/blog/entry/84589
 https://twitter.com/laycrs/status/1327289027549007872?s=20

 */

const int MAX_N=1e6+1;
int A[MAX_N];
int N;

void solve() {
  vector<III> res;

  auto proc=[&](int i) {
    res.emplace_back(i,i+1,i+2);
    int x=A[i]^A[i+1]^A[i+2];
    A[i]=A[i+1]=A[i+2]=x;
  };

  for(int i=0; i+2<N; i+=2) proc(i);
  if(N%2==0) {
    if(A[N-2]!=A[N-1]) {
      cout<<"NO"<<endl;
      return;
    }
  }

  int nn=N-(N%2==0);
  for(int i=nn-3; i-2>=0; i-=2) proc(i-2);

  assert(set<int>(A,A+N).size()==1);
  cout<<"YES"<<endl;
  cout<<SZ(res)<<endl;
  FORR(t,res) {
    int i,j,k; tie(i,j,k)=t;
    cout<<i+1<<" "<<j+1<<" "<<k+1<<endl;
  }
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
