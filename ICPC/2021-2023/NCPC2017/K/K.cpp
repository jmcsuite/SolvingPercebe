#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll vlSb; ll vlSn; ll vlSm;
    cin>>vlSb >> vlSn >> vlSm;

    ll sb,sn, sm; cin>>sb>>sn>>sm;

    ll N = vlSb+ vlSn + vlSm;
    N/=2;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    sort(vl.begin(),vl.end());

    ll ans=0;
    ll it = 1000000000;
    auto can = [&](ll x, ll vlSb, ll vlSn, ll vlSm){
        for(int i=0; i<N; i++){
            if(vl[i]*(sb*2) >= x && vlSb >= 2){
                vlSb-=2;
                continue;
            }
            if(vl[i]*(sb+sn) >= x && vlSb >= 1 && vlSn >= 1){
                vlSb--;
                vlSn--;
                continue;
            }
            if((sb+sm) <= (sn+sn)){
                if(vl[i]*(sb+sm) >= x && vlSb && vlSm){
                    vlSb--;
                    vlSm--;
                    continue;
                }
                if(vl[i]*(sn+sn) >= x && vlSn >= 2){
                    vlSn -= 2;
                    continue;
                }
            }else{
                if(vl[i]*(sn+sn) >= x && vlSn >= 2){
                    vlSn -= 2;
                    continue;
                }
                if(vl[i]*(sb+sm) >= x && vlSb && vlSm){
                    vlSb--;
                    vlSm--;
                    continue;
                }
            }

            if(vl[i]*(sn+sm) >= x && vlSn && vlSm){
                vlSn--;
                vlSm--;
                continue;
            }

            if(vl[i]*(sm+sm) >= x && vlSm >= 2){
                vlSm-= 2;
                continue;
            }
            return false;
        }
        return true;
    };
    while(it != 0){
        if(can(ans+it, vlSb, vlSn, vlSm)) ans+= it;
        else it/=2;
    }
    cout << ans << endl;
}
