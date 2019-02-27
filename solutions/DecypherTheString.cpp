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

// $ cp-batch DecypherTheString | diff DecypherTheString.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DecypherTheString.cpp && ./a.out

/*
 
 2/26/2019
 
 17:26-18:10 give up
 
 Data: T is given
 Condition:
  - S*P=T (P is permutation)
  - Query can be issued at most only three times
  - S[i] ∈ { a..z }
 Unknown: S
 
 1. Reduce some number to maximal query times
 
 Three times query is pretty small.
 I tried to dig relevant upper-bound log2(1e4)<=14, log2(26)<=5, ... However I had no luck.
 
 2. Try to leverage condition of 26 chars
 
 Another possible key was condition of only 26 chars.
 I analyzed small cases where string consists of 2 chars like "aabaababbaaa"
 However I had no idea.
 
 3. Inverse of permutation
 
 If we can generally find P^-1 such that T*P^-1=S. Then we can compute P = (P^-1)^-1
 However I have no idea to get P^-1 generally...
 
 I got in stuck...
 
 20:50-23:11 read editorials and got AC
 
 https://codeforces.com/blog/entry/65365
 
 log_26(1e4) = log2(1e4)/log2(26) <= 3
 
 Imagine segtree with 26 edges from a segment node.
 26-ary tree corresponds to unique representation in 26-ary number.
 Therefore we can uniquely determine permutation P in log_26(1e4) query.
 
 Inversion is easy to find. Suppose we got below by permutatin P
 abc => cab
 
 c=>2,b=>1,a=>0 shows inverse permutation.
 
 */

const int MAX_N=1e4+1;
int P[MAX_N];
string T;

string query(string a) {
  cout<<"? "<<a<<endl;
  string t;
  cin>>t;
  assert(t!="0");
  if(t=="0") exit(1);
  return t;
}
string answer(string s) {
  cout<<"! "<<s<<endl;
  exit(0);
}

void solve() {
  int N=SZ(T);
  REP(i,3) {
    string s(N,'?');
    int b=1; REP(j,2-i) b*=26;
    REP(i,N) s[i]='a'+i/b%26;
    string t=query(s);
    REP(i,N) P[i]=P[i]*26+t[i]-'a';
  }
  string res(N,'?');
  REP(i,N) {
    int j=P[i];
    assert(j<N);
    res[j]=T[i];
  }
  assert(count(ALL(res),'?')==0);
  answer(res);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  cin>>T;
  solve();
  
  return 0;
}
