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
struct Manacher {
public:
  string S,T;
  vector<int> P;
  Manacher(string S) : S(S) {
    int N=S.size();
    T="^";
    for(int i=0; i<N; ++i) T+="#"+S.substr(i,1)+(i==N-1?"#":"");
    T+="$";
  }
  vector<int> solve() {
    int M=T.size();
    vector<int> P(M);
    int C=0, R=-1, rad;
    for(int i=0; i<M; ++i) {
      if(i<=R) rad=min(P[2*C-i], R-i);
      else rad=0;

      // expand rad based on `i`-mirror
      while (i+rad<M&&i-rad>=0&&T[i-rad]==T[i+rad]) ++rad;
      P[i]=rad;
      if(i+rad-1>R) C=i,R=i+rad-1;
    }
    return this->P=P;
  }
  int si2pi(int si) { return 2*(si+1); } // map string position `i` to `i` in P
  // returns the half-open range of the palidrome at center `c` in `P`
  pair<int,int> range(int c) {
    if(!P.size()) solve();
    int s=c-P[c]+2,ss=s/2-1;
    int l=P[c]-1;
    return {ss,ss+l};
  }
  string longestPalindrome() {
    vector<int> P=solve();
    int c=-1,M=T.size();
    for(int i=1; i<M-1; ++i) if(c==-1||P[i]>P[c]) c=i;
    if(c==-1) return "";
    auto r=range(c);
    return S.substr(r.first,r.second-r.first);
  }
};
// $ cp-batch PrefixSuffixPalindrome | diff PrefixSuffixPalindrome.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address PrefixSuffixPalindrome.cpp && ./a.out

/*
 
 3/19/2020
 
 8:19-9:10 WA
 10:05 give up
 
 3/21/2020
 
 18:00-19:25 WA
 
 3/22/2020
 
 10:10-11:00 AC
 11:30-11:44 add simpler solution inspired by @yosupot
 
 https://codeforces.com/contest/1326/submission/73685358
 https://codeforces.com/blog/entry/74961
 https://twitter.com/hanseilimak/status/1241789736408121345
 https://twitter.com/kzyKT_M/status/1240685812259254274
 https://twitter.com/ei1333/status/1240686151041597440
 https://twitter.com/tempura_cpp/status/1240685748568743938
 
 */

string S;

string f(string S) {
  dump(S);
  Manacher man(S);
  VI P=man.solve();
  VI X(SZ(S),1);
  dumpc(P);

  int lb=0,rb=SZ(S)-1;
  while(lb<rb) {
    if(S[lb]!=S[rb]) break;
    ++lb,--rb;
  }
  
  auto len=[&](int pi) -> int {
    auto ran=man.range(pi);
    int l=ran.first,r=ran.second;
    if(l>lb&&r<=rb) return 0;
    l=max(lb,l),r=min(rb+1,r);
    int add=0,rad=0;
    int c=pi/2-1;
    if(r<=l) return 0;
    else if((ran.second-ran.first)%2==1) {
      rad=min(c-l,r-c-1);
      rad=max(rad,0);
      add=2*rad+1;
    } else {
      rad=min(c-l+1,r-c-1);
      rad=max(rad,0);
      add=2*rad;
    }
    if(pi==2) dump(pi,l,r,rad,lb,rb,add);
    return lb*2+add;
  };
  
  int maxi=lb;
  FOR(pi,man.si2pi(lb),SZ(P)-1) {
    if(len(pi)>len(maxi)) maxi=pi;
  }
  
  auto ran=man.range(maxi);
  int l=ran.first,r=ran.second;
  l=max(lb,l),r=min(rb+1,r);
  string s;
  int c=maxi/2-1;
  if(ran.first>=ran.second) {
    s="";
  } else if((ran.second-ran.first)%2==1) {
    int rad=min(c-l,r-c-1);
    rad=max(rad,0);
    dump(c,rad,c-rad,2*rad+1);
    s=S.substr(c-rad,2*rad+1);
  } else {
    int rad=min(c-l+1,r-c-1);
    rad=max(rad,0);
    dump(c,l,r,c-l+1,r-c-1,rad,c-rad+1,2*rad);
    s=S.substr(c-rad+1,2*rad);
  }
  dump(lb,maxi,len(maxi),s);
  return S.substr(0,lb)+s+S.substr(SZ(S)-lb);
}

bool ispalin(string res) {
  int l=0,r=SZ(res)-1;
  while(l<r) {
    if(res[l]!=res[r]) return false;
    ++l,--r;
  }
  return true;
}

string solve_org() {
  string s=S;
  string rs=s; reverse(ALL(rs));
  if(s==rs) return s;
  string res=f(s);
  dump(S,res);
  assert(ispalin(res));
  
  return res;
}

string fff(string s) {
  Manacher man(s);
  VI P=man.solve();
  int N=SZ(P);
  int maxc=0;
  REP(i,N) if(P[i]==i) maxc=i;
  auto r=man.range(maxc);
  assert(r.first==0);
  return s.substr(0,r.second);
}

string ff(string S) {
  string s=S;
  string rs=s; reverse(ALL(rs));
  if(s==rs) return s;
  string res=fff(s),res2=fff(rs);
  if(SZ(res2)>SZ(res)) res=res2;
  return res;
}

string g(string s) {
  int lb=0,rb=SZ(S)-1;
  while(lb<rb) {
    if(S[lb]!=S[rb]) break;
    ++lb,--rb;
  }
  
  string s1=s.substr(0,lb),s3=s1;
  reverse(ALL(s3));
  string s2=ff(s.substr(lb,SZ(s)-2*lb));
  return s1+s2+s3;
}

string solve() {
  string s=S;
  string rs=s; reverse(ALL(rs));
  if(s==rs) return s;
  string res=g(s),res2=g(rs);
  if(SZ(res2)>SZ(res)) res=res2;
  dump(S,res);
  assert(ispalin(res));
  
  return res;
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
  int N=genRandNum(1,11);
  VI A=genRandSeq(N,0,3);
  S=string(N,'?');
  REP(i,N)S[i]='a'+A[i];
  dump(S);
  
  string act=solve();
  dump(act);
  
  string exp;
  REPE(r,N)REPE(l,r) {
    string s=S.substr(0,l)+S.substr(r);
    if(ispalin(s)&&SZ(s)>SZ(exp)) exp=s;
  }
  if(SZ(act)!=SZ(exp)) dump(S,act,exp);
  assert(SZ(act)==SZ(exp));
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  int T; cin>>T;
  REP(i,T) {
    cin>>S;
    cout<<solve()<<endl;
  }
  
  return 0;
}
