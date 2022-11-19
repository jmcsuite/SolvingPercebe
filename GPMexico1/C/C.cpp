#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M;
    cin >> N >> M;
    vll vl(N+1);
        
    for(int i=1;i<=N;i++) cin>>vl[i];
    while(M--){
        ll K; cin>>K;
        vll a(K);
        vll b(K);
        vll c(K);
        for(int j=0;j<K;j++) cin>>a[j]>>b[j]>>c[j];
        ll ans = 0;
        for(int j=0;j<K;j++) ans += (b[j]-a[j]+1)*c[j];
        //cout << ans << 'n' << endl;
        auto func = [&](ll x){
            int ini = 0;
            int inc = N/2+1;
            while(inc != 0){
                ll tr = ini + inc;
                ll cc = 0;
                if(tr >= N+1){
                     inc/= 2;
                     continue;
                }
                for(int j=0;j<K;j++){
                    cc += max(ll(0), min(b[j],tr)-a[j]+ll(1))*c[j];
                }
                
                if(cc >= x) inc/=2;
                else ini+= inc;
            }
            return ini+1;
        };

        ll med = vl[func((ans+1)/2)];
        if(ans%2 == 0){
            double mm = vl[func((ans+2)/2)];
            mm += med;
            mm /= 2;
            cout << fixed << setprecision(2) << mm << '\n';
        }else{
            cout << med << '\n';
        }
    }
}
