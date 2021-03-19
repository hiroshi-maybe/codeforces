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

// $ cp-batch GuessingTheGreatest | diff GuessingTheGreatest.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address GuessingTheGreatest.cpp && ./a.out

/*

 2/18/2021

 7:14-8:14 easy AC
 8:50 give up hard

 22:10-23:04 read editorials and got AC

 https://twitter.com/hanseilimak/status/1362646125505744898

 https://codeforces.com/blog/entry/87849
 https://twitter.com/laycrs/status/1362444399003664386
 https://twitter.com/kzyKT_M/status/1362444443878531074

 */

const bool LOC=false;

const int MAX_N=1e6+1;
int A[MAX_N];
int N;
int q=0;

int ask(int l, int r) {
  //dump(l,r);
  if(r-l<2) return -1;
  assert(++q<=20);
  assert(r-l>=2);

  if(LOC) {
    vector<II> xs;
    FOR(i,l,r) xs.emplace_back(A[i],i);
    sort(ALL(xs));
    //dumpc(xs);
    return xs[SZ(xs)-2].second;
  }

  cout<<"? "<<l+1<<" "<<r<<endl;
  int res; cin>>res;
  return res-1;
}

void ans(int i) {
  if(LOC) {
    //dumpC(A,A+N);
    //dump(i,A[i]);
    vector<II> xs;
    REP(i,N) xs.emplace_back(A[i],i);
    sort(ALL(xs));
    assert(i==xs[SZ(xs)-1].second);
  }

  cout<<"! "<<i+1<<endl;
}

void solve() {
  q=0;
  int p=ask(0,N);
  int l=0,r=N;
  while(abs(r-l)>2) {
    //dump(p,l,r);
    int m=(l+r)/2;
    if(p<m) {
      int ll=min(p,l);
      int pp=ask(ll,m);
      (pp==p?r:l)=m;
    } else {
      int rr=max(r,p+1);
      int pp=ask(m,rr);
      (pp==p?l:r)=m;
    }
  }

  int res=ask(l,r);
  ans(res==l?l+1:l);
}

void solve_c1() {
  q=0;
  int l=0,r=N;
  while(abs(r-l)>1) {
    //dump(l,r);
    int m=(l+r)/2;
    int p=ask(l,r);
    if(r-l==2) {
      int res=p==l?l+1:l;
      ans(res);
      return;
    }

    if(p<m) {
      //dump(l,m);
      if(m==l+1) l=m;
      else {
        int pp=ask(l,m);
        (pp==p?r:l)=m;
      }
    } else {
      //dump(m,r);
      if(r==m+1) r=m; else {
        int pp=ask(m,r);
        (pp==p?l:r)=m;
      }
    }
  }

  ans(l);
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
vector<Integer> shuffle(vector<Integer> &A) {
  int N = A.size();
  vector<Integer> res(N);
  for(int i=0; i<N; ++i) {
    // res[0..i-1] has org[0..i-1]
    res[i] = A[i];
    int r = rnd() % (i+1);
    swap(res[i],res[r]);
  }
  return res;
}

void test() {
  N=(int)1e5;
  VI as(N);
  REP(i,N) as[i]=i+1;
  as = shuffle(as);
  REP(i,N) A[i]=as[i];
  solve();
  dump(q);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

/*
  while(true) {
    test();
  }*/

  cin>>N;
  if(LOC) {
    REP(i,N) cin>>A[i];
  }

  solve();

  return 0;
}
