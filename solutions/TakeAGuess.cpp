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

// $ cp-batch TakeAGuess | diff TakeAGuess.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address TakeAGuess.cpp && ./a.out

/*

 8/29/2021

 9:12-9:40 give up
 16:30-17:05 AC after reading the editorial

 https://codeforces.com/blog/entry/94384
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.2dm14kq71sth

 https://twitter.com/kzyKT_M/status/1432028623117053953
 https://twitter.com/maspy_stars/status/1432027653247143938
 https://twitter.com/laycrs/status/1432027042254520324
 https://twitter.com/ei1333/status/1432026980451446786

 */

const bool local=false;

const int MAX_N=1e4+1;
LL A[MAX_N]={1,6,4,2,3,5,4};
int N,K;

const int AND=0,OR=1;

int qcnt=0;
LL ask(int qtype, int i, int j) {
  qcnt++;
  assert(qcnt<=2*N);

  string qstr=(qtype==AND?"and ":"or ");
  cout<<qstr<<(i+1)<<" "<<(j+1)<<endl;

  if(local) {
    if(qtype==AND) return A[i]&A[j];
    else return A[i]|A[j];
  }

  LL res; cin>>res;
  assert(res>=0);
  if(res==-1) exit(1);
  return res;
}

void done(LL res) {
  cout<<"finish "<<res<<endl;
}

LL aij(int i, int j) {
  LL a=ask(AND,i,j),b=ask(OR,i,j);
  return a+b;
}

void solve() {
  vector<LL> as(N,-1);
  LL a01=aij(0,1),a12=aij(1,2),a20=aij(2,0);
  LL a0=(a01+a20-a12)/2;
  dump(a01,a12,a20,a0);
  as[0]=a0,as[1]=a01-a0,as[2]=a20-a0;
  FOR(i,3,N) {
    LL a0i=aij(0,i);
    as[i]=a0i-a0;
  }

  dumpC(A,A+N);
  dumpc(as);

  if(local) {
    REP(i,N) assert(as[i]==A[i]);
  }

  sort(ALL(as));
  done(as[K-1]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  cin>>N>>K;
  solve();

  return 0;
}
