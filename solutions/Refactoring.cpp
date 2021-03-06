#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
#include <iomanip>
using namespace std;
// type alias
typedef long long LL;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
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
#define TRACE false
#define dump(x) if(TRACE) { cerr << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cerr << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpf(args...) if(TRACE) { fprintf(stderr, ##args); putchar('\n'); }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cerr << x << ','; } cerr << endl; }
template<class Iter> void dumpc(Iter begin, Iter end) { if (TRACE) { for(; begin!=end; ++begin) { cerr<<*begin<<','; } cerr<<endl; } }

/*
 
 11/11/2018
 
 14:50-16:25 give up
 
 11/12/2018
 
 14:30-15:17 test case #12 doesn't pass.
 
 https://codeforces.com/blog/entry/63099
 
 Idea is same. There seems to exist some implementation bug...

 Tons of bugs:
  - wrong usage of rolling hash library
  - there was a bug in rolling hash library
  - my rolling hash library is too slow. it does not pass test case #14
  - wrong pre/post cut
 
 18:15 got AC by KMP
 
 Summary:
  - bug of rolling hash screwed up everything
 
 */

// 16:25 give up
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG x.cpp && ./a.out
const int MAX_N=3010+1;
string W1[MAX_N],W2[MAX_N];
int N;

namespace RollingHash {
  template<int MOD> struct ModInt {
    unsigned int val;
    ModInt(): val(0) {}
    ModInt(int v) { norm(v%MOD); }
    ModInt(long long v) { norm(v%MOD); }
    ModInt& norm(long long v) {
      v=v<0?v%MOD+MOD:v; // negative
      v=v>=MOD?v-MOD:v; // mod
      val=(unsigned int)v;
      return *this;
    }
    explicit operator bool() const { return val!=0; }
    ModInt operator-() const { return ModInt(0)-*this; }
    ModInt &operator+=(ModInt that) { return norm((long long)val+that.val); }
    ModInt &operator-=(ModInt that) { return norm((long long)val-that.val); }
    ModInt &operator*=(ModInt that) { val=(unsigned long long)val*that.val%MOD; return *this; }
    ModInt &operator/=(ModInt that) { return *this*=that.inv(); }
    ModInt operator+(ModInt that) const { return ModInt(*this)+=that; }
    ModInt operator-(ModInt that) const { return ModInt(*this)-=that; }
    ModInt operator*(ModInt that) const { return ModInt(*this)*=that; }
    ModInt operator/(ModInt that) const { return ModInt(*this)/=that; }
    ModInt pow(long long n) const {
      ModInt x=*this, res=1;
      while(n>0) {
        if(n&1) res*=x;
        x*=x,n>>=1;
      }
      return res;
    }
    ModInt inv() const { return (*this).pow(MOD-2); }
    bool operator==(ModInt that) const { return val==that.val; }
    bool operator!=(ModInt that) const { return val!=that.val; }
  };
  const int MOD0=1e9+7,MOD1=1e9+9;
  using M0=ModInt<MOD0>;
  using M1=ModInt<MOD1>;
  M0 p0=rand()%MOD0,pinv0=p0.inv();
  M1 p1=rand()%MOD1,pinv1=p1.inv();
  vector<M0> P0{1}, PINV0{1};
  vector<M1> P1{1}, PINV1{1};
  struct H {
    vector<pair<M0,M1>> hcum;
    string str;
    H(string s) : str(s) {
      int N=(int)s.size();
      while ((int)P0.size()<=N) {
        P0.push_back(P0.back()*p0);
        PINV0.push_back(PINV0.back()*pinv0);
        P1.push_back(P1.back()*p1);
        PINV1.push_back(PINV1.back()*pinv1);
      }
      hcum.resize(N+1);
      hcum[0]={M0(0),M1(0)};
      for(int i=0; i<N; ++i) {
        hcum[i+1]={hcum[i].first+M0(s[i])*P0[i],hcum[i].second+M1(s[i])*P1[i]};
      }
    }
    // half-open range [l,r)
    pair<M0,M1> hash(int r) { return { hcum[r].first, hcum[r].second }; }
    pair<M0,M1> hash(int l, int r) {
      return {
        (hcum[r].first-hcum[l].first)*PINV0[l],
        (hcum[r].second-hcum[l].second)*PINV1[l]
      };
    }
  };
  // Rabin-Karp algorithm
  vector<int> match(H &s, H &p) {
    int N=s.str.size(),M=p.str.size();
    auto pp=p.hash(0,M);
    vector<int> res;
    for(int i=0; i<=N-M; ++i) if(s.hash(i,i+M)==pp) res.push_back(i);
    return res;
  }
};

typedef long long ll;
struct RollingHash2 {
  static const ll mo0=1000000021,mo1=1000000009;
  static ll mul0,mul1;
  static const ll add0=1000010007, add1=1003333331;
  static vector<ll> pmo[2];
  string s; int l; vector<ll> hash_[2];
  void init(string s) {
    this->s=s; l=s.size();
    hash_[0]=hash_[1]=vector<ll>(1,0);
    if(!mul0) mul0=10009+(((ll)&mul0)>>5)%259,mul1=10007+(((ll)&mul1)>>5)%257;
    if(pmo[0].empty()) pmo[0].push_back(1),pmo[1].push_back(1);
    REP(i,l) hash_[0].push_back((hash_[0].back()*mul0+add0+s[i])%mo0);
    REP(i,l) hash_[1].push_back((hash_[1].back()*mul1+add1+s[i])%mo1);
  }
  pair<ll,ll> hash(int l,int r) { // s[l..r]
    if(l>r) return make_pair(0,0);
    while(pmo[0].size()<r+2)
      pmo[0].push_back(pmo[0].back()*mul0%mo0), pmo[1].push_back(pmo[1].back()*mul1%mo1);
    return make_pair((hash_[0][r+1]+(mo0-hash_[0][l]*pmo[0][r+1-l]%mo0))%mo0,
                     (hash_[1][r+1]+(mo1-hash_[1][l]*pmo[1][r+1-l]%mo1))%mo1);
  }
  pair<ll,ll> hash(string s) { init(s); return hash(0,s.size()-1); }
  static pair<ll,ll> concat(pair<ll,ll> L,pair<ll,ll> R,int RL) { // hash(L+R) RL=len-of-R
    while(pmo[0].size()<RL+2) pmo[0].push_back(pmo[0].back()*mul0%mo0), pmo[1].push_back(pmo[1].back()*mul1%mo1);
    return make_pair((R.first + L.first*pmo[0][RL])%mo0,(R.second + L.second*pmo[1][RL])%mo1);
  }
};
vector<ll> RollingHash2::pmo[2]; ll RollingHash2::mul0,RollingHash2::mul1;

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
vector<int> doKMP(string s, string p) {
  vector<int> res;
  vector<int> pi=buildPrefixFunction(p);
  
  int j=0, L=s.size(), M=p.size();
  for(int i=0; i<L; ++i) {
    while(j>=0&&s[i]!=p[j]) j=pi[j];
    ++j;
    if(j>=M) { // matched
      res.push_back(i-j+1);
      j=pi[j];
    }
  }
  return res;
}

void end() {
  println("NO");
  exit(0);
}

II boundary2(string s, string t, int l, int r) {
  int resl=0,resr=0,M=SZ(s);
  
//  dump4(s,t,l,r);
  
  int j=l-1;
  for(; j>=0; --j) {
    if(s[j]!=t[j]) break;
  }
  resl=l-j-1;
//  dump(j);
  assert(resl>=0);
  j=r+1;
  for(; j<M; ++j) if(s[j]!=t[j]) break;
  resr=j-r-1;
  assert(resr>=0);
  return {resl,resr};
}

int si=-1,sp=-1;
II boundary1(string s, string t, int l, int r, string x) {
  int resl=0,resr=0,M=SZ(s);
  
//  dump4(s,t,l,r);
  
  int j=l-1;
  for(; j>=0; --j) {
    int d=l-j;
    if(s[j]!=t[j]||sp-d<0||s[j]!=W1[si][sp-d]) break;
  }
  resl=l-j-1;
//  dump(j);
  assert(resl>=0);
  j=r+1;
  for(; j<M; ++j) {
    int d=j-r;
    int jj=sp+SZ(x)+d-1;
    if(s[j]!=t[j]||jj>=SZ(W1[si])||s[j]!=W1[si][jj]) break;
  }
  resr=j-r-1;
  assert(resr>=0);
//  dump2(resl,resr);
  return {resl,resr};
}

void solve_wrong() {
  string s="",t="";
  int lb,rb;
  REP(i,N) {
    int M=SZ(W1[i]);
    int l=3010,r=-1;
    REP(j,M) if(W1[i][j]!=W2[i][j]) SMIN(l,j),SMAX(r,j);
    if(r!=-1) {
      if(s.empty()) {
        s=W1[i].substr(l,r-l+1);
        t=W2[i].substr(l,r-l+1);
        lb=l,rb=SZ(W1[i])-r-1;
        sp=l,si=i;
      } else {
        if(r-l+1!=SZ(s)) end();
        int L=SZ(s);
        REP(j,L) {
          if(W1[i][l+j]!=s[j]) end();
          if(W2[i][l+j]!=t[j]) end();
        }
        auto p=boundary1(W1[i],W2[i],l,r,s);
        SMIN(lb,p.first);
        SMIN(rb,p.second);
      }
    } else {
      VI ps=doKMP(W1[i],s);
      if(ps.empty()) continue;
      int j=ps.front();
      /*
      RollingHash<LL> rh(W1[i]);
      int j = rh.doRabbinKarpMatch(s);
      if(j==-1) continue;*/
      auto p=boundary2(W1[i],W2[i],j,j+SZ(s)-1);
      if(p.first>=lb&&p.second>=rb) end();
    }
  }
  if(s.empty()) {
    s+=W1[0][0],t+=W1[0][0];
  } else {
    dump4(s,t,lb,rb);
    dump4(sp,si,W1[si],W2[si]);
    s=W1[si].substr(sp-lb,lb+rb+SZ(s));
    t=W2[si].substr(sp-lb,lb+rb+SZ(t));
  }
  println("YES");
  println("%s",s.c_str());
  println("%s",t.c_str());
}

II boundary(string s, string t, int l, int r) {
  int resl=0,resr=0,M=SZ(s);
  
  string u=W1[si];
  //  dump4(s,t,l,r);
  
  int j=l-1;
  for(; j>=0; --j) {
    int d=l-j;
    if(sp-d<0||s[j]!=u[sp-d]) break;
  }
  resl=l-j-1;
  //  dump(j);
  assert(resl>=0);
  j=r+1;
  for(; j<M; ++j) {
    int d=j-r;
    int jj=sp+r-l+d;
    if(jj>=SZ(u)||s[j]!=u[jj]) break;
  }
  resr=j-r-1;
  assert(resr>=0);
  //  dump2(resl,resr);
  return {resl,resr};
}

void solve() {
  string s="",t="",pre="",post="";
  int lb,rb;
  REP(i,N) {
    int M=SZ(W1[i]);
    dump2(i,M);
    int l=3010,r=-1;
    REP(j,M) if(W1[i][j]!=W2[i][j]) SMIN(l,j),SMAX(r,j);

    if(r!=-1) {
      string ss=W1[i].substr(l,r-l+1);
      string tt=W2[i].substr(l,r-l+1);
      string prepre=W1[i].substr(0,l);
      string postpost=W2[i].substr(r+1);
      reverse(ALL(prepre));
      
      if(s.empty()) {
        s=ss,t=tt,pre=prepre,post=postpost;
        lb=l,rb=SZ(W1[i])-r-1;
        sp=l,si=i;
      } else {
        if(r-l+1!=SZ(s)) end();
        int L=SZ(s);
        REP(j,L) {
          if(W1[i][l+j]!=s[j]) end();
          if(W2[i][l+j]!=t[j]) end();
        }
        auto p=boundary(W1[i],W2[i],l,r);
        SMIN(lb,p.first);
        SMIN(rb,p.second);
      }
    }
  }
  s=W1[si].substr(sp-lb,lb+rb+SZ(s));
  t=W2[si].substr(sp-lb,lb+rb+SZ(t));
  
  REP(i,N) {
    string x=W1[i],y=W2[i];

    VI ps=doKMP(x,s);
    if(ps.empty()) continue;
    int j=ps.front();
    int M=SZ(x);
    assert(j+SZ(s)<=M);
    REP(o,SZ(s)) {
      assert(x[j+o]==s[o]);
      x[j+o]=t[o];
    }
    if(x!=y) end();
  }
  
  println("YES");
  println("%s",s.c_str());
  println("%s",t.c_str());
}

RollingHash2 rh[3030];
void solve_inspired_by_kmjp() {
  string s="",t="",pre="",post="";
  REP(i,N) {
    int M=SZ(W1[i]);
    int l=3010,r=-1;
    REP(j,M) if(W1[i][j]!=W2[i][j]) SMIN(l,j),SMAX(r,j);
    
    if(r!=-1) {
      string ss=W1[i].substr(l,r-l+1);
      string tt=W2[i].substr(l,r-l+1);
      string prepre=W1[i].substr(0,l);
      string postpost=W2[i].substr(r+1);
      reverse(ALL(prepre));
      
      if(s.empty()) {
        s=ss,t=tt,pre=prepre,post=postpost;
      } else {
        if(ss!=s||tt!=t) {
          dump4(ss,s,tt,t);
          end();
        }

        REP(j,SZ(pre)) if(j>=SZ(prepre)||prepre[j]!=pre[j]) {
          pre.resize(j);
          break;
        }
        REP(j,SZ(post)) if(j>=SZ(postpost)||postpost[j]!=post[j]) {
          post.resize(j);
          break;
        }
      }
    }
  }
  dump4(s,t,pre,post);
  reverse(ALL(pre));
  s=pre+s+post;
  t=pre+t+post;
  auto ha=rh[N].hash(s);
  
  REP(i,N) {
    rh[i].init(W1[i]);
    string x=W1[i],y=W2[i];
    for(int j=0;j+s.size()<=x.size();j++) {
      if(rh[i].hash(j,j+s.size()-1)==ha) {
        x=x.substr(0,j)+t+x.substr(s.size()+j);
        break;
      }
    }
    if(x!=y) end();
  }
  
  println("YES");
  println("%s",s.c_str());
  println("%s",t.c_str());
}

void solve_rh() {
  string s="",t="",pre="",post="";
  REP(i,N) {
    int M=SZ(W1[i]);
    int l=3010,r=-1;
    REP(j,M) if(W1[i][j]!=W2[i][j]) SMIN(l,j),SMAX(r,j);
    
    if(r!=-1) {
      string ss=W1[i].substr(l,r-l+1);
      string tt=W2[i].substr(l,r-l+1);
      string prepre=W1[i].substr(0,l);
      string postpost=W2[i].substr(r+1);
      reverse(ALL(prepre));
      
      if(s.empty()) {
        s=ss,t=tt,pre=prepre,post=postpost;
      } else {
        if(ss!=s||tt!=t) {
          dump4(ss,s,tt,t);
          end();
        }
        
        REP(j,SZ(pre)) if(j>=SZ(prepre)||prepre[j]!=pre[j]) {
          pre.resize(j);
          break;
        }
        REP(j,SZ(post)) if(j>=SZ(postpost)||postpost[j]!=post[j]) {
          post.resize(j);
          break;
        }
      }
    }
  }
  reverse(ALL(pre));
  s=pre+s+post;
  t=pre+t+post;
  auto ha=RollingHash::H(s).hash(0,s.size());
  
  REP(i,N) {
    auto myrh=RollingHash::H(W1[i]);
    string x=W1[i],y=W2[i];
    for(int j=0;j+s.size()<=x.size();j++) {
      if(myrh.hash(j,j+s.size())==ha) {
        x=x.substr(0,j)+t+x.substr(s.size()+j);
        break;
      }
    }
    if(x!=y) end();
  }
  
  println("YES");
  println("%s",s.c_str());
  println("%s",t.c_str());
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  /*
  REP(i,3000) {
    string s(3000,'x');
    cout<<s<<endl;
  }*/
  
  scanf("%d",&N);
//  cin>>N;
  dump(N);
  REP(i,N) {
    char c[3010];
    scanf("%s", c);
    W1[i]=string(c);
//    cin>>W1[i];
  }
  REP(i,N) {
    char c[3010];
    scanf("%s", c);
    W2[i]=string(c);
//    cin>>W2[i];
  }
  //solve();
  solve_rh();
  
  return 0;
}
