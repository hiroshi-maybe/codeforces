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

// $ cp-batch AllTheVowelsPlease | diff AllTheVowelsPlease.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address AllTheVowelsPlease.cpp && ./a.out

/*
 
 5/17/2019
 
 8:13-8:40 RE
 8:45 AC
 
 https://codeforces.com/blog/entry/67081
 
 Simply putting C[(i+j)%5] at (i,j) is sufficient
 https://codeforces.com/contest/1166/submission/54368403
 
 */

const int MAX_N=1e4+1;
set<char> R[MAX_N],C[MAX_N];
int K;

vector<char> V={'a', 'e', 'i', 'o' ,'u'};
void solve() {
  FORE(N,5,100) if(K%N==0) {
    int M=K/N;
    if(M<5) continue;
    REP(i,N)REP(j,M) cout<<V[(i+j)%5];
    cout<<endl;
    return;
  }
  cout<<-1<<endl;
}

void solve_org() {
  FORE(N,5,100) if(K%N==0) {
    int M=K/N;
    if(M<5) continue;
    vector<string> res(N,string(M,'x'));
    
//    dump(K,N,M);
    
    REP(o,(M+4)/5)REP(c,5) {
      REP(i,N) {
        int j=5*o+(5+i-c)%5;
        if(j<M){
          res[i][j]=V[c];
        }
      }
    }
    REP(i,N){
      REP(j,M) {
        R[i].emplace(res[i][j]),C[j].emplace(res[i][j]);
      }
    }

//    FORR(s,res)dump(s);
    REP(i,N) assert(SZ(R[i])>=5);
    REP(j,M) assert(SZ(C[j])>=5);
    FORR(s,res)cout<<s;
    cout<<endl;
    return;
  }
  cout<<-1<<endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
//  FORE(k,1,10000) K=k,solve();
  
  cin>>K;
  solve();
  
  return 0;
}
