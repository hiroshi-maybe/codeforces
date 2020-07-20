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

// $ cp-batch DubiousCyrpto | diff DubiousCyrpto.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address DubiousCyrpto.cpp && ./a.out

/*

 7/19/2020

 3:00-4:01 give up

 12:00-12:40, 21:10-22:50 AC after reading editorials
 23:17 add proof in https://twitter.com/hanseilimak/status/1284922952333451264

 https://codeforces.com/blog/entry/80216
 https://twitter.com/laycrs/status/1284806347435896832
 https://twitter.com/kzyKT_M/status/1284806170138439680

 */

LL L,R,M;

void solve() {
  for(LL a=L; a<=R; ++a) {
    LL maxn=(M+R-L)/a;
    if(maxn<=0) continue;
    LL x=M-maxn*a;
    if(x>R-L) continue;
    LL b,c;
    if(x>=0) c=L,b=c+x;
    else b=L,c=b-x;
    //dump(a,maxn,x,c,b);
    assert(L<=b&&b<=R);
    assert(L<=c&&c<=R);
    cout<<a<<" "<<b<<" "<<c<<endl;
    return;
  }
  assert(false);
}

template<typename Integer>
vector<Integer> divisors(Integer N) {
  assert(N>=1);
  vector<Integer> res;
  for(Integer p=1; p*p<=N; ++p) if(N%p==0) {
    res.push_back(p);
    if(p!=N/p) res.push_back(N/p);
  }
  sort(res.begin(),res.end());
  return res;
}
void solve_wrong() {
  for(LL a=L; a<=R; ++a) {
    LL mm=M%a;
    LL maxk1=(M-mm+a-1)/a-1,maxk2=(R-L-mm)/a;
    LL hbk=min(maxk1,maxk2);
    //LL lbk=(L-R-mm+a-1)/a;
    /*
    if(hbk-lbk>=0) {

    }*/
    LL k=hbk;
    LL bc=a*k+mm;
    //dump(a,hbk,bc);
    LL c,b;
    if(bc>=0) {
      c=L,b=L+bc;
    } else {
      b=L,c=L-bc;
    }
    if(b<L||b>R||c<L||c>R) continue;
    if((M+c-b)%a==0&&M+c-b>0) {
      cout<<a<<" "<<b<<" "<<c<<endl;
      return;
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;

  int t; cin>>t;
  while(t--) {
    cin>>L>>R>>M;
    solve();
  }

  return 0;
}
