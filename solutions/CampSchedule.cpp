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
//#define __KUMATRACE__ true
#ifdef __KUMATRACE__
#define dump(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); __kumaerr(_it, args); }
#define dumpc(ar) { cerr<<#ar<<": "; FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
#define dumpC(beg,end) { cerr<<"~"<<#end<<": "; __kumaerrc(beg,end); }
#else
#define dump(args...)
#define dumpc(ar)
#define dumpC(beg,end)
#endif

// $ cp-batch CampSchedule | diff CampSchedule.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address CampSchedule.cpp && ./a.out

/*
 
 3/8/2019
 
 19:50-20:27 AC
 
 https://codeforces.com/blog/entry/65825
 
 */

vector<int> buildPrefixFunction(const string S) {
  int L=S.size();
  vector<int> pi(L+1,-1);
  int j=-1;
  for(int i=0; i<L; ++i) {
    while(j>=0&&S[i]!=S[j]) j=pi[j];
    pi[i+1]=++j;
  }
  return pi;
}

//const int MAX_N=1e6+1;
string S,T;
int N,M;

void solve() {
  int N=SZ(S),M=SZ(T);
  VI P=buildPrefixFunction(T);
  int cnt[2]={0};
  REP(i,N) {
    if(S[i]=='0') ++cnt[0];
    else cnt[1]++;
  }
  string res;
  int j=0;
  
  int nextj=P[M];
  //  string s="1001";
  //  VI X=buildPrefixFunction(s);
  REP(i,N) {
    int a=T[j]-'0';
    if(cnt[a]>0) res.push_back('0'+a),cnt[a]--;
    else break;
    ++j;
    dump(i,j,a,cnt[0],cnt[1],res);
    if(j==M) j=nextj;
  }
  REP(a,2) while(cnt[a]>0) res.push_back('0'+a),cnt[a]--;
  cout<<res<<endl;
}

void solve_wrong() {
  int N=SZ(S),M=SZ(T);
  VI P=buildPrefixFunction(T);
  int p0=0,p1=0;
  while(p0<N&&S[p0]!='0') ++p0;
  while(p1<N&&S[p1]!='1') ++p1;
  string res=S;
  int j=0;
  
  int nextj=P[M];
//  string s="1001";
//  VI X=buildPrefixFunction(s);
  REP(i,N) {
    char a=T[j];
    if(res[i]!=a) {
      if(a=='0'&&p0<N) {
        swap(res[i],res[p0]);
        while(p0<N&&S[p0]!='0') ++p0;
        ++j;
      } else if(a=='1'&&p1<N) {
        swap(res[i],res[p1]);
        while(p1<N&&S[p1]!='0') ++p1;
        ++j;
      }
    } else {
      ++j;
      if(p0==i) while(p0<N&&S[p0]!='0') ++p0;
      if(p1==i) while(p1<N&&S[p1]!='0') ++p1;
    }
    dump(i,j,a,res);
    if(res[i]!=a) break;
    if(j==M) j=nextj;
  }
  cout<<res<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>S>>T;
  solve();
  
  return 0;
}
