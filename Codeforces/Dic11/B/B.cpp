#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,M;
        cin >> N >> M;
        vll vl(N,N);
        for(int i = 0; i < M; i++){
            ll a,b; cin >> a >> b; a--; b--;
            if (b < a) swap(a,b);
            vl[a] = min(vl[a],b);
        }
        ll mini = N;
        ll ans = 0;
        for(int i = N-1; i >= 0; i--){
            mini = min(mini, vl[i]);
            ans += (mini-i);
        }
        cout << ans << '\n';
    }
}

