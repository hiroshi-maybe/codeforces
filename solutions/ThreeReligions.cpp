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

// $ cp-batch ThreeReligions | diff ThreeReligions.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ThreeReligions.cpp && ./a.out

/*
 
 6/26/2019
 
 17:04-18:25 WA
 22:00-22:50 read editorials
 
 6/27/2019
 
 9:00-11:20 read editorials and got AC
 
 It was unclear how order in WoU (=S) should be preserved.
 Sounds like query order between deifferent religion does not matter.
 Then dp seems to be plausible. I could not figure out explicitly from problem statement 😡.
 Statement is saying that each religion should be subsequence of S.
 At each moment, we can find optimal allcation in S.
 "Paint" metaphor is pretty misleading. It sounds that painted characte in S is persistent in following queries 😡😡
 Thus my solution gives NO instead of YES for fifth query below:
 
 5 5
 abcab
 + 1 a
 + 1 b
 + 2 a
 + 2 b
 + 2 c
 
 We want to solve each query regardless of previous query. Then dp comes up.
 
 https://codeforces.com/blog/entry/66783

 In dp transition, we need to compute dp[a][x][y] for T[0].
 However dp[a][x][y] may not come from dp[a-1][x][y] because we may have transition from dp[a][x-1][y] or dp[a][x][y-1].
 If we solve dp[0..a][0..x][0..y] every time, runtime complexity is O(Q*250^3), which does not fit TL.
 However we just need to compute dp[a][0..x][0..y] because dp[a-1][x][y] is already computed.
 This is the key insight to solve this problem. I would call this technique as "progressive dp in queries"
 
 https://cinnamo-coder.hatenablog.com/entry/2019/05/01/162353
 https://naoyat.hatenablog.jp/entry/CodeforcesRound556Div1
 https://qiita.com/vain0x/items/80cc96b3c83dfd5f17a6#codeforces-round-556-div-2
 https://betrue12.hateblo.jp/entry/2019/05/28/214439
 https://twitter.com/tempura_cpp/status/1122904977016360964
 https://twitter.com/HIR180/status/1122904811207217152
 https://twitter.com/kyort0n/status/1122902438187376641
 
 */

string S;
int N,Q;

const int MAX_N=1e6;
const int Inf=1e7;
int nxt[MAX_N][26];
void buildnext() {
  REP(c,26) nxt[N][c]=N;
  for(int i=N-1; i>=0; --i) {
    REP(c,26) nxt[i][c]=nxt[i+1][c];
    nxt[i][S[i]-'a']=i;
  }
}
const int MAX_M=260;
int memo[MAX_M][MAX_M][MAX_M];
VI T[3];
int f(int x, int y, int z) {
//  dump(x,y,z);
  assert(x>=0&&y>=0&&z>=0);
  int &res=memo[x][y][z];
  if(res>=0) return res;
  if(x==0&&y==0&&z==0) return res=0;
  res=Inf;
  int ps[3]={x,y,z};
  REP(i,3) {
    int p=ps[i];
    if(p==0) continue;
//    dump(i,p-1,)
    assert(p-1<SZ(T[i]));
    assert(p-1>=0);
    int c=T[i][p-1];
    ps[i]--;
    int a=f(ps[0],ps[1],ps[2]);
    if(a>N) continue;
    int b=nxt[a][c]+1;
    if(b>N) b=Inf;
    SMIN(res,b);
    ps[i]++;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q>>S;
  buildnext();
  MINUS(memo);
  REP(i,Q) {
    char t; cin>>t;
    if(t=='+') {
      int r; char x; cin>>r>>x; --r;
      int c=x-'a';
      T[r].push_back(c);
    } else {
      int r; cin>>r;
      --r;
      int L=SZ(T[r]);
      T[r].pop_back();
      if(r==0) REP(j,MAX_M)REP(k,MAX_M) memo[L][j][k]=-1;
      if(r==1) REP(i,MAX_M)REP(k,MAX_M) memo[i][L][k]=-1;
      if(r==2) REP(i,MAX_M)REP(j,MAX_M) memo[i][j][L]=-1;
    }
    int res=f(SZ(T[0]),SZ(T[1]),SZ(T[2]));
    cout<<(res>N?"NO":"YES")<<endl;
  }
  
  return 0;
}

int main_wrong() {
  /*
   
   Counter example:
   
   5 5
   abcab
   + 1 a
   + 1 b
   + 2 a
   + 2 b
   + 2 c
   
   */
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>N>>Q>>S;
  VI cpos[26];
  VI viz[26];
  REP(i,N) {
    int c=S[i]-'a';
    cpos[c].push_back(i);
    viz[c].push_back(false);
  }
  
  queue<II> ng[26];
  auto out = [&]() {
    bool ok=true;
    REP(i,26) ok&=ng[i].empty();
    cout<<(ok?"YES":"NO")<<endl;
  };
  vector<II> rpos[3];
  REP(i,Q) {
//    dump(i);
    char t; cin>>t;
    if(t=='+') {
      int r; char x; cin>>r>>x; --r;
      int c=x-'a';
      int curp=SZ(rpos[r])?rpos[r].back().first:-1;
      int nextp=upper_bound(ALL(cpos[c]),curp)-cpos[c].begin();
//      dump(curp,nextp);
      if(nextp>=SZ(cpos[c])) {
        ng[c].emplace(r,SZ(rpos[r]));
        rpos[r].emplace_back(c,Inf);
      } else {
        bool ok=false;
        FOR(i,nextp,SZ(cpos[c])) if(!viz[c][i]) {
          viz[c][i]=true;
          rpos[r].emplace_back(cpos[c][i], i);
          ok=true;
          break;
        }
//        dump(ok);
        if(!ok) {
          ng[c].emplace(r,SZ(rpos[r]));
          rpos[r].emplace_back(c,Inf);
        }
      }
      dump(i,r);
      dumpc(rpos[r]);
      out();
    } else {
      int r; cin>>r;
      --r;
      assert(SZ(rpos[r])>0);
      II p=rpos[r].back(); rpos[r].pop_back();
      if(p.second<Inf) {
        assert(p.first<N);
        int c=S[p.first]-'a';
        viz[c][p.second]=false;
        if(SZ(ng[c])) {
          int rr=ng[c].front().first;
          rpos[rr][ng[c].front().second]=p;
          viz[c][p.second]=true;
          ng[c].pop();
        }
      } else {
        int c=p.first;
        queue<II> fuck;
        bool del=false;
        while(SZ(ng[c])) {
          if(!del&&ng[c].front().first==r) {
            del=true;
            ng[c].pop();
            continue;
          }
          fuck.push(ng[c].front()), ng[c].pop();
        }
        ng[c]=fuck;
      }
      out();
    }
  }
  
  return 0;
}
