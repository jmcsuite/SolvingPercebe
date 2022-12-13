#include<bits/stdc++.h>
using namespace std;
using ll =  long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        vector<string> vs(2);
        ll N; cin>>N;
        for(int i = 0; i < 2; i++) cin>>vs[i];
        vll cc(N);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < 2; j++) if(vs[j][i] == 'B') cc[i]++;
        }

        ll ans1 = 0;
        ll it = 0;
        for(int i = 0; i < N; i++){
            if(vs[it][i] == 'W') break;
            ans1 += cc[i];
            if(cc[i] == 2) it = (it+1)%2;
        }
        ll ans2 = 0;
        it = 1;
        for(int i = 0; i < N; i++){
            if(vs[it][i] == 'W') break;
            ans2 += cc[i];
            if(cc[i] == 2) it = (it+1)%2;
        }

        ll tot = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < 2; j++) if(vs[j][i] == 'B') tot++;
        }

        cout << (((ans1 == tot) || (ans2 == tot)) ? "YES" : "NO") << '\n';
    }
}
