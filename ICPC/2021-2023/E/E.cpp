#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=10;
ll vl[maxn];
ll tmp[maxn];

ll N,M,D;

ll transform(ll vl[maxn]){
    ll ans=0;
    for(int i=0; i<N+M; i++){
        ans*=7;
        ans+=vl[i];
    }
    return ans;
}

void get(ll x, ll tmp[maxn]){
    for(int i=N+M-1; i>=0; i--){
        tmp[i] = x%7;
        x/=7;
    }
}

bool check(ll tmp[maxn], ll vl[maxn]){
    for(int i=0; i<N+M; i++) if(tmp[i] > vl[i]) return false;
    for(int i=0; i<N+M; i++) if(i != 0 && i!= N && tmp[i] > tmp[i-1]) return false;
    return true;
}

map<ll,float> dp;
map<ll,bool> vis;

int main(){
    ios::sync_with_stdio(0);
    cin>>N>>M>>D;
    for(int i=0; i<N+M; i++) cin>>vl[i];
    sort(vl, vl+N, [](ll a, ll b){
            return a > b;
            });

    sort(vl+N, vl+N+M, [](ll a, ll b){
            return a > b;
            });
    
    ll totalSum=0;
    for(int i=0; i<N+M; i++) totalSum+=vl[i];
    D=min(D,totalSum);
    queue<ll> q;
    ll sevenN = 1;
    ll sevenM = 1;
    for(int i=0; i<N; i++) sevenN*=7;
    for(int i=0; i<M; i++) sevenM*=7;

    for(int i=0; i<sevenN; i++){
        get(i*sevenM, tmp);
        if(!check(tmp, vl));
        ll diff=0;
        for(int j=0; j<N+M; j++) diff+=vl[j]-tmp[j];
        if(diff != D) continue;
        q.push(i*sevenM);
        vis[i*sevenM]=1;
    }


    while(!q.empty()){
        ll x=q.front();
        q.pop();
        if(x % sevenM == 0) dp[x] = 1;
        get(x,tmp);

        for(int i=0; i<N+M; i++){
            tmp[i]++;
            if(!check(tmp,vl)){
                tmp[i]--;
                continue;
            }
            ll den=0;
            for(int i=0; i<N+M; i++) if(tmp[i]>0) den++;
            ll num=0;
            if(i >= N){
                for(int j=N; j<N+M; j++) if(tmp[i] == tmp[j]) num++;
            }else{
                for(int j=0; j<N; j++) if(tmp[i] == tmp[j]) num++;
            }
            ll nx = transform(tmp);
            dp[nx] = dp[nx] + dp[x]*num/den;
            if(!vis[nx]){
                vis[nx] = 1;
                q.push(nx);
            }
            tmp[i]--;
        }
    }
    ll x = transform(vl);
    cout << fixed << setprecision(6) << dp[x] << '\n';
}
