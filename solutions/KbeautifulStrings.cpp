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

// $ cp-batch KbeautifulStrings | diff KbeautifulStrings.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address KbeautifulStrings.cpp && ./a.out

/*

 3/6/2021

 6:48-7:28 AC

 https://twitter.com/hanseilimak/status/1368379437633265665

 https://codeforces.com/blog/entry/88422

 */

//const int MAX_N=1e6+1;
int N,K;
string S;

string solve() {
  if(N%K!=0) return "-1";
  VI cnt(26);
  REP(i,N) cnt[S[i]-'a']++;
  auto ok=[&](VI &cnt) {
    REP(i,26) if(cnt[i]%K!=0) return false;
    return true;
  };

  if(ok(cnt)) return S;
  for(int i=N-1; i>=0; --i) {
    char cur=S[i]-'a';
    cnt[cur]--;
    int badget=N-i-1;
    FOR(c,cur+1,26) {
      cnt[c]++;

      VI gap(26);
      REP(c,26) gap[c]=(K-cnt[c]%K)%K;
      int filla=badget-accumulate(ALL(gap),0);

      if(filla>=0) {
        assert(filla%K==0);
        gap[0]+=filla;
        string res=S;
        res[i]='a'+c;
        //dump(res);
        //dumpc(gap);
        FOR(j,i+1,N) {
          REP(c,26) if(gap[c]>0) {
            res[j]='a'+c;
            gap[c]--;
            break;
          }
        }
        //dump(res);
        VI cnt2(26);
        REP(i,N) cnt2[res[i]-'a']++;
        assert(ok(cnt2));
        return res;
      }
      cnt[c]--;
    }
  }
  return "-1";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>N>>K>>S;
    cout<<solve()<<endl;
  }

  return 0;
}
