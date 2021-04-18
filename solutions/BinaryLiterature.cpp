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

// $ cp-batch BinaryLiterature | diff BinaryLiterature.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address BinaryLiterature.cpp && ./a.out

/*

 4/16/2021

 8:45-9:36 WA
 9:50 give up

 17:45-18:48 read editorials

 4/18/2021

 11:10-12:22 read editorials and got AC

 https://codeforces.com/blog/entry/89644
 https://docs.google.com/document/d/1Yq384PEooRVsmlzB103YMLWwE_JhPN8AbxZagNrF_vY/edit#bookmark=id.wvucwbokorby

 https://twitter.com/laycrs/status/1383102241255530499
 https://twitter.com/kiri8128/status/1383101939148214275
 https://twitter.com/kzyKT_M/status/1383101359566688264
 https://twitter.com/SSRS_cp/status/1383100679003070465

 */

//const int MAX_N=1e6+1;
string S[3];
int N;

string f(string s, string t, int c) {
  vector<string> ss={s,t};
  VV<int> ps(2,{-1});
  REP(i,2) {
    REP(j,SZ(ss[i])) if(ss[i][j]=='0'+c) ps[i].push_back(j);
    //dumpc(ps[i]);
  }

  string res;

  auto push=[&](int cnt, int d) {
    while(cnt--) res.push_back('0'+d);
  };

  int cnt=min(SZ(ps[0]),SZ(ps[1]));
  if(cnt<N) return "";

  //dump(cnt);
  REP(i,cnt-1) {
    //dump(i,ps[0][i],ps[0][i+1]);
    //dump(i,ps[1][i],ps[1][i+1]);
    push(ps[0][i+1]-ps[0][i]-1,1-c);
    push(ps[1][i+1]-ps[1][i]-1,1-c);
    push(1,c);
    //dump(i,res);
  }

  //dump(ps[0][cnt-1],ps[1][cnt-1]);
  REP(i,2) FOR(j,ps[i][cnt-1]+1,SZ(ss[i])) res.push_back(ss[i][j]);

  return res;
}

string solve() {
  REP(j,3)REP(i,j)REP(p,2) {
    string res=f(S[i],S[j],p);
    //dump(S[i],S[j],p,res);
    if(2*N<=SZ(res)&&SZ(res)<=3*N) return res;
  }
  assert(false);
}

string solve_wrong() {
  REP(i,3) {
    string s=S[i];
    REP(j,3) if(i!=j) {
      string t=S[j];
      int i2=0;
      REP(i1,2*N) if(s[i1]==t[i2]) ++i2;
      string res=s;
      if(2*N+(2*N-i2)>3*N) continue;
      FOR(k,i2,2*N) res.push_back(t[k]);
      return res;
    }
  }
  assert(false);
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
  N=3;
  REP(i,3) {
    VI as=genRandSeq(2*N,0,2);
    S[i]=string(2*N,'0');
    REP(j,2*N) S[i][j]='0'+as[j]-0;
    //dumpc(as);
    dump(S[i]);
  }
  solve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  //while(true) test();

  int t; cin>>t;
  while(t--) {
    cin>>N;
    REP(i,3) cin>>S[i];
    cout<<solve()<<endl;
  }

  return 0;
}
