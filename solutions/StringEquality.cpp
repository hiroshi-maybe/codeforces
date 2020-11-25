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

// $ cp-batch StringEquality | diff StringEquality.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address StringEquality.cpp && ./a.out

/*

 11/22/2020

 0:13-0:34 WA
 1:00 pause
 1:35-1:50 give up

 11/25/2020

 15:55-16:55 found challenge case in original solution and got AC

 https://codeforces.com/blog/entry/84885

 https://twitter.com/laycrs/status/1330191798740856834
 https://twitter.com/kzyKT_M/status/1330191920958754818
 https://twitter.com/ei1333/status/1330192028479746050

 */

int N,K;
string A,B;

bool solve() {
  VI cnt1(26),cnt2(26);
  REP(i,N) cnt1[A[i]-'a']++,cnt2[B[i]-'a']++;

  REP(c,26) {
    int d=cnt1[c]-cnt2[c];
    //dump(c,d);
    if(d<0||d%K!=0) return false;
    if(c<25)cnt1[c+1]+=d;
  }
  return true;
}

bool solve_verywrong() {
  sort(ALL(A)),sort(ALL(B));
  string s,t;
  REP(i,N) if(A[i]!=B[i]) s.push_back(A[i]),t.push_back(B[i]);
  int M=SZ(t);
  vector<II> rl;
  REP(i,M) {
    if(i==0||t[i]!=t[i-1]) {
      rl.emplace_back(i,0);
    }
    rl.back().second++;
  }
  FORR(p,rl) {
    int i,len; tie(i,len)=p;
    map<char,int> cnt;
    FOR(j,i,i+len) {
      if(s[j]>t[j]) return false;
      if(s[j]!=t[j]) cnt[s[j]]++;
    }
    FORR(kvp,cnt) if(kvp.second%K!=0) return false;
  }
  return true;
}

bool solve_wrong() {
  sort(ALL(A)),sort(ALL(B));
  vector<II> rl;
  REP(i,N) {
    if(i==0||B[i]!=B[i-1]) {
      rl.emplace_back(i,0);
    }
    rl.back().second++;
  }
  FORR(p,rl) {
    int i,len; tie(i,len)=p;
    map<char,int> cnt;
    FOR(j,i,i+len) {
      if(A[j]>B[j]) return false;
      if(A[j]!=B[j]) cnt[A[j]]++;
    }
    dump(i,len);
    dumpc(cnt);
    FORR(kvp,cnt) if(kvp.second%K!=0) return false;
  }
  return true;
}

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename Integer>
Integer genRandNum(Integer lb, Integer ub) {
  assert(lb<ub);
  // Helper to generate random integer in range [lb, ub)
  Integer x = rnd() % (Integer)(ub - lb);
  return x + lb;
}
template <typename Integer>
vector<Integer> genRandSeq(int size, Integer lb, Integer ub) {
  if (size==0) return {};
  vector<Integer> res(size);
  generate(res.begin(), res.end(), [&]() {
    return genRandNum(lb, ub);
  });
  return res;
}
void test() {
  N=5,K=genRandNum(1,N+1);
  VI as=genRandSeq(N,0,3),bs=genRandSeq(N,0,3);
  A=string(N,'?'),B=string(N,'?');
  REP(i,N) A[i]='a'+as[i],B[i]='b'+bs[i];

  bool exp=solve(),act=solve_wrong();
  cerr<<N<<" "<<K<<endl;
  cerr<<A<<endl;
  cerr<<B<<endl;
  dump(exp,act);
  assert(exp==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>A>>B;
    cout<<(solve()?"Yes":"No")<<endl;
  }

  return 0;
}
