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

// $ cp-batch SashaAndOneMoreName | diff SashaAndOneMoreName.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address SashaAndOneMoreName.cpp && ./a.out

/*
 
 2/16/2019
 
 9:29-10:44 AC
 
 https://codeforces.com/blog/entry/65295
 https://twitter.com/hogeover30/status/1096850363221590016
 
 1) A+A or A+x+A
  => res = Impossible
 
 A+A => no way to construct different
 A+x+A => no pair to `x`. Thus no way to construct different
 
 2) S[i+1..N] + S[l..i] is palindrome for i=1..N-1
  => res = 1
 
 A+B (A!=rev(A)) => B+A should be palidrome and A+B!=B+A

 Thus remaining case is A+x+B or A+rev(A)
 
 3) Find first pref and suf with the same length s.t. S[1..i]!=S[N-i+1..N]
 
 S[N-i+1..N] = rev(S[1..i]) thus S[N-i+1..N] + palindrome + S[1..i] is also palindrome
  => res = 2
 
 Such `i` is always found.
 If # of characters contained in `A` where S=A+A or A+x+A is at least 2, we can find such `i`.
 In order to prove it, we can show that A contains only one char <=> S[1..i]=S[N-i+1..N] for all i=1..N-1.
 "A contains only one char => S[1..i]=S[N-i+1..N] for all i=1..N-1" is trivial.
 
 S[1..i]=S[N-i+1..N] for all i=1..N-1 => A contains only one char
 This is proved by induction.
 
 1) base case i=1
 A[1]=A[N] => S[1..i]="a", S[N-i+1..N]="a"
 2) suppose S[1..k]=string(k,'a'), S[N-k+1..N]=string(k,'a')
 S[1..k+1] = string(k,'a')+x
 S[N-k..N] = x+string(k,'a')
 
 S[1..k+1] = S[N-k..N] <=> x='a'. Thus proposition holds when i=k+1. Q.E.D.
 
 
 
 */

string S;
int N;

bool ispalin(string &s) {
  int N=SZ(s);
  int l=0,r=N-1;
  while(l<r) {
    if(s[l]!=s[r]) return false;
    ++l,--r;
  }
  return true;
}

int solve() {
  N=SZ(S);
  set<char> cs;
  REP(i,N/2) cs.emplace(S[i]);
  if(N<=2||SZ(cs)==1) return -1;
  FOR(i,1,N) {
    string s=S.substr(0,i),t=S.substr(i);
    string T=t+s;
    if(ispalin(T)&&S!=T) return 1;
  }
  return 2;
}

int solve_org() {
  N=SZ(S);
  
  FOR(i,1,N) {
    string s=S.substr(0,i),t=S.substr(i);
    string T=t+s;
    if(ispalin(T)&&S!=T) return 1;
  }
  
  const int Inf=1e7;
  int res=Inf;
  string L=S.substr(0,N/2),R=S.substr((N+1)/2);
  string RR=R; reverse(ALL(RR));
  if(RR!=R) {
    SMIN(res,1+(N%2));
  }
  int l=N/2-1,r=(N+1)/2,len=1;
  if(N%2==0)assert(r==l+1);
  else assert(r==l+2);
  while(l>=0) {
    string s=S.substr(l,len),t=S.substr((N+1)/2,len);
    if(s!=t) SMIN(res,3+(N%2));
    
    int m=(N+1)/2+len;
    string a=S.substr(0,l),b=S.substr(l,m-l),c=S.substr(m,N-m);
    string cand=c+b+a;
    if(ispalin(cand)&&cand!=S) {
//      dump(a,b,c,cand);
      SMIN(res,2);
    }
    
    ++len,--l;
  }
  return res==Inf?-1:res;
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

int res=-1;
void dfs(int i, string &cur, vector<string> &ss) {
  if(i==SZ(S)) {
    if(SZ(cur)) ss.push_back(cur);
    VI P(SZ(ss)); REP(i,SZ(ss)) P[i]=i;
    do {
      string T;
      FORR(p,P) T+=ss[p];
      if(ispalin(T)&&T!=S) {
        if(res==-1||res>SZ(ss)-1) {
          res=SZ(ss)-1;
          dumpc(ss);
          dump(S,T);
        }
      }
    } while(next_permutation(ALL(P)));
    if(SZ(cur)) ss.pop_back();
    return;
  }
  
  cur.push_back(S[i]);
  dfs(i+1,cur,ss);
  cur.pop_back();
  
  ss.push_back(cur);
  cur=string(1,S[i]);
  dfs(i+1,cur,ss);
  cur=ss.back();
  ss.pop_back();
}

void test() {
  res=-1;
  int N=3;
  VI x=genRandSeq(N,0,3);
  string l; REP(i,N) l.push_back('a'+x[i]);
  string r=l; reverse(ALL(r));
  
  S=l+r;
  dump(S);

  string cur;
  vector<string> ss;
  dfs(0,cur,ss);
  
  int act=solve();
  if(res!=act) dump(S,res,act);
  assert(res==act);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  while(true) test();
  
  cin>>S;
  int res=solve();
  if(res==-1) cout<<"Impossible"<<endl;
  else cout<<res<<endl;
  
  return 0;
}
