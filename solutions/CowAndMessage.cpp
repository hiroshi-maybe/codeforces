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

// $ cp-batch CowAndMessage | diff CowAndMessage.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CowAndMessage.cpp && ./a.out

/*
 
 2/17/2020
 
 8:21-9:23 WA
 9:36-9:50 fix overflow and got AC
 
 https://codeforces.com/blog/entry/73953
 
 */

//const int MAX_N=1e6+1;
string S;
int N;

LL solve() {
  N=SZ(S);
  
  VV<int> pos(26);
  REP(i,N) pos[S[i]-'a'].push_back(i);
  vector<LL> res;
  REP(i,26) res.push_back(SZ(pos[i]));
  
  REP(c1,26) REP(c2,26) {
//    dump(c1,c2);
    LL cnt=0;
    REP(i,SZ(pos[c1])) {
      int p1=pos[c1][i];
//      int d=(N-p1+1)/2;
//      assert(p1+2*d>=N);
      int j=upper_bound(ALL(pos[c2]),p1)-pos[c2].begin();
      if(SZ(pos[c2])>0) {
//        dump(p1,p2,SZ(pos[c2])-p2);
//        dumpc(pos[c2]);
      }
      cnt+=SZ(pos[c2])-j;
    }
    res.push_back(cnt);
  }
//  dumpc(res);
  return *max_element(ALL(res));
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int genRandNum(int lb, int ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  int x = rnd() % (int)(ub - lb);
  return x + lb;
}
vector<int> genRandSeq(int size, int lb, int ub) {
  if (size==0) return {};
  vector<int> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}

void test() {
  N=3;
  VI A=genRandSeq(N,0,2);
  S =string(N,'?');
  REP(i,N)S[i]='a'+A[i];
  
  map<string,int> cnt;
  REP(a,N) {
    set<pair<VI,string>> SS;
    string s0(1,S[a]);
    VI seq0={a};
    SS.emplace(seq0,s0);

    FOR(d,1,N) {
      string s=s0;
      VI seq=seq0;
      int i=a+d;
      while(i<N) s.push_back(S[i]),seq.push_back(i),SS.emplace(seq,s),i+=d;
    }
    FORR(kvp,SS) cnt[kvp.second]++;
  }
  
  string res; int maxcnt=0;
  FORR(kvp,cnt) if(kvp.second>maxcnt) {
    res=kvp.first,maxcnt=kvp.second;
  }
  assert(SZ(res)<=2);
  int act=solve();
  if(act!=maxcnt) {
    dump(act,maxcnt,res,S);
  }
  assert(act==maxcnt);
  dump(S,res,maxcnt);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>S;
  cout<<solve()<<endl;
  
  return 0;
}
