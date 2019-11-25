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
struct TwoDimCumSum {
public:
  int R,C;
  TwoDimCumSum(vector<vector<int>> &X) {
    this->R=X.size();
    if(R==0) return;
    this->C=X[0].size();
    this->cum=vector<vector<int>>(R+1,vector<int>(C+1,0));
    
    for(int i=0; i<R; ++i) for(int j=0; j<C; ++j) {
      cum[i+1][j+1]=cum[i][j+1]+cum[i+1][j]-cum[i][j]+X[i][j];
    }
  }
  // query of sum in rectangle r in [i1,i2), c in [j1,j2)
  int query(int i1, int j1, int i2, int j2) {
    return cum[i2][j2]-cum[i1][j2]-cum[i2][j1]+cum[i1][j1];
  }
private:
  vector<vector<int>> cum;
};
// $ cp-batch ArsonInBerlandForest | diff ArsonInBerlandForest.out -
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address ArsonInBerlandForest.cpp && ./a.out

/*
 
 11/24/2019
 
 1:30-2:14 WA
 17:00-17:23 WA
 17:23-17:45 MLE
 17:55 MLE
 19:00 MLE resolved
 19:25 try binary search
 19:50 AC by referring to @hitonanode's code
 
 */

const int Inf=1e7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int N,M;
  cin>>N>>M;
  
  vector<string> A(N);
  
  VV<int>X(N+1,VI(M+1,0));
  REP(i,N) {
    cin>>A[i];
    REP(j,M) if(A[i][j]=='X') X[i][j]=1;
  }
  TwoDimCumSum cum(X);
    
  VV<int> cnt(N+1,VI(M+1,0));
  int good=0,bad=1e6+1;
  while(abs(good-bad)>1) {
    int mid=(good+bad)/2;
    REPE(i,N)REPE(j,M) cnt[i][j]=0;
    REP(i,N)REP(j,M) {
      int li=i,lj=j,ri=i+2*mid,rj=j+2*mid;
      if(ri>=N||rj>=M) continue;
      if(cum.query(li,lj,ri+1,rj+1)==(ri-li+1)*(rj-lj+1)) {
        cnt[i][j]++;
        cnt[i][j+2*mid+1]--;
        cnt[i+2*mid+1][j]--;
        cnt[i+2*mid+1][j+2*mid+1]++;
      }
    }
    REP(i,N)REP(j,M) cnt[i][j+1]+=cnt[i][j];
    REP(j,M)REP(i,N) cnt[i+1][j]+=cnt[i][j];
    bool ok=true;
    REP(i,N)REP(j,M) if(A[i][j]=='X'&&cnt[i][j]==0) {
      ok=false;
      break;
    }
    if(ok) good=mid;
    else bad=mid;
  }
  vector<string> res(N,string(M,'.'));
  REP(i,N)REP(j,M) {
    int li=i,lj=j,ri=i+2*good,rj=j+2*good;
    if(ri>=N||rj>=M) continue;
    if(cum.query(li,lj,ri+1,rj+1)==(ri-li+1)*(rj-lj+1)) {
      res[i+good][j+good]='X';
    }
  }
  println("%d",good);
  REP(i,N) println("%s",res[i].c_str());
}


int main_wrong() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout<<setprecision(12)<<fixed;
  
  int N,M;
  cin>>N>>M;
  N+=2,M+=2;
  vector<string> A;
  A=vector<string>(N, string(M, '.'));
  A[0]=string(M,'.');
  A[N-1]=string(M,'.');
  REP(i,N-2) {
    string s; cin>>s;
    REP(j,M-2) if(s[j]=='X') A[i+1][j+1]='X';
  }
  
  vector<pair<int,int>> movesd = { {0,1}/*R*/,{1,1}/*RD*/,{1,0}/*D*/,{1,-1}/*DL*/,{0,-1}/*L*/,{-1,-1}/*UL*/,{-1,0}/*U*/,{-1,1}/*UR*/ };
  queue<II> Q;
  
  int T=Inf;
  // hor
  REP(i,N) {
    VI cum(M+1,0);
    REP(j,M) {
      char c=A[i][j];
      if(c=='X') cum[j+1]=cum[j]+1;
      else {
        if(cum[j]>0) SMIN(T,(cum[j]-1)/2);
        cum[j+1]=0;
      }
    }
  }
  // ver
  REP(j,M){
    VI cum(N+1,0);
    REP(i,N) {
      char c=A[i][j];
      if(c=='X') cum[i+1]=cum[i]+1;
      else {
        if(cum[i]>0) SMIN(T,(cum[i]-1)/2);
        cum[i+1]=0;
      }
    }
  }
  // diagonal
  REP(r,N) {
    VI cum(N+M+1,0);
    REP(d,N+M) {
      int i=r+d,j=d;
      if(i<0||i>=N||j<0||j>=M) break;
      char c=A[i][j];
      if(c=='X') cum[d+1]=cum[d]+1;
      else {
        if(cum[d]>0) SMIN(T,(cum[d]-1)/2);
        cum[d+1]=0;
      }
      dump(d,i,j,cum[d],T);
    }
    dumpc(cum);
    cum=VI(N+M+1,0);
    REP(d,N+M) {
      int i=r+d,j=M-1-d;
      if(i<0||i>=N||j<0||j>=M) break;
      char c=A[i][j];
      if(c=='X') cum[d+1]=cum[d]+1;
      else {
        if(cum[d]>0) SMIN(T,(cum[d]-1)/2);
        cum[d+1]=0;
      }
    }
  }
  /*
  REP(c,M) {
    VI cum(N+M+1,0);
    REP(d,N+M) {
      int i=d,j=c+d;
      if(i<0||i>=N||j<0||j>=M) break;
      char c=A[i][j];
      if(c=='X') cum[d+1]=cum[d]+1;
      else {
        if(cum[d]>0) SMIN(T,(cum[d]-1)/2);
        cum[d+1]=0;
      }
    }
    cum=VI(N+M+1,0);
    REP(d,N+M) {
      int i=d,j=c-d;
      if(i<0||i>=N||j<0||j>=M) break;
      char c=A[i][j];
      if(c=='X') cum[d+1]=cum[d]+1;
      else {
        if(cum[d]>0) SMIN(T,(cum[d]-1)/2);
        cum[d+1]=0;
      }
    }
  }*/
  dump(T);
  VV<int> D(N,VI(M,Inf));
  VV<int> viz(N,VI(M,0));
  
  function<void(int,int)> dfs2 = [&](int i, int j) {
    if(viz[i][j]) return;
    viz[i][j]=1;
    FORR(m,movesd) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='X') {
        D[ii][jj]=0;
        continue;
      }
      dfs2(ii,jj);
    }
  };
  
  REP(i,N)REP(j,M)if(!viz[i][j]&&A[i][j]=='.') {
    dfs2(i,j);
  }
  REP(i,N)REP(j,M)if(D[i][j]==0) {
    Q.emplace(i,j);
  }
  
  while(SZ(Q)) {
    int i,j; tie(i,j)=Q.front(); Q.pop();
    int d=D[i][j];
    FORR(m,movesd) {
      int ii=i+m.first,jj=j+m.second;
      if(ii<0||ii>=N||jj<0||jj>=M) continue;
      if(A[ii][jj]=='.') continue;
      if(D[ii][jj]<=d+1) continue;
      D[ii][jj]=d+1;
      Q.emplace(ii,jj);
    }
  }

/*
  REP(i,N) {
    REP(j,M) printf("%c",D[i][j]<Inf?'0'+D[i][j]:'.');
    println("");
  }*/
  
//  dumpc(maxds);
//  vector<string> res(N-2,string(M-2,'.'));
//  REP(i,N-2)REP(j,M-2)if(D[i+1][j+1]<Inf&&D[i+1][j+1]>=T) res[i][j]='X';
  
  println("%d",T);
  REP(i,N-2){
    REP(j,M-2) printf("%c", D[i+1][j+1]<Inf&&D[i+1][j+1]>=T?'X':'.');
    println("");
  }
  
  return 0;
}
