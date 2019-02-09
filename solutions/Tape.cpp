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

// $ cp-batch Tape | diff Tape.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address Tape.cpp && ./a.out

/*
 
 2/7/2019
 
 5:40-6:23, 8:20-8:45 got AC
 
 No need to maintain merged intervals because it's possible to choose merging intervals independently.
 Just flag merged ones to check later. I was crazy enough to do redundant work during the contest 👎👎.
 
 https://codeforces.com/blog/entry/65079
 https://twishort.com/O7vnc
 
 All the broken segments must be fixed. Thus res>=N.
 If K<N, we need to choose intervals between broken segments N-K times.
 In order to minimize the total length, we can choose N-K smallest intervals.
 
 Analyze from backward. If the final state is clear, it should be straighforward to come up with independent merge of intervals (gaps)
 
 */

const int MAX_N=1e6+1;
LL B[MAX_N];
LL M;
int N,K;

void solve() {
  vector<LL> gaps;
  REP(i,N-1) gaps.push_back(B[i+1]-B[i]-1);
  sort(ALL(gaps));
//  dump(N,N-K);
//  dumpc(gaps);
  LL res=(LL)N+accumulate(gaps.begin(),gaps.begin()+N-K,0LL);
  cout<<res<<endl;
}

void solve_org() {
  vector<II> gaps;
  REP(i,N-1) gaps.emplace_back(B[i+1]-B[i],i);
  sort(ALL(gaps));
//  dumpc(gaps);
  VI merged(N,0);
  REP(i,N-K) merged[gaps[i].second]=1;
//  dumpc(merged);
  LL res=0;
  int l=MAX_N;
  REP(i,N) {
    if(merged[i]) SMIN(l,i);
    else {
      LL dif=1;
      if(l<N) dif=B[i]-B[l]+1;
//      dump(l,i,dif);
      res+=dif;
      l=MAX_N;
    }
  }
  cout<<res<<endl;
}

void solve_wrong() {
  if(N<=K) {
    cout<<N<<endl;
  }
  //set<II> ranges;
  map<LL,vector<II>> gaps;
  REP(i,N-1) {
    //ranges[{i,i+1}]=B[i+1]-B[i];
    //gaps[B[i+1]-B[i]]={i,i+1};
  }
  int X=N-K;
  LL res=N-X;
  while(X--) {
    auto it=gaps.begin();
    assert(SZ(it->second));
  //  auto p=it->second.front();
    res+=it->first;
    
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>M>>K;
  REP(i,N) cin>>B[i];
  solve();
  
  return 0;
}
