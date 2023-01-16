#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int dd[101][101];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        for(int i = 0; i < 101; i++){
            for(int j = 0; j < 101; j++){
                dd[i][j] = 0;
            }
        }

        vll vl(N);
        for(int i=0; i<N; i++) cin>>vl[i];
        map<ll,ll> mp;
        for(int i=0; i<N; i++) mp[vl[i]]++;
        bool se = true;
        for(int i=0; i<N; i++) if(mp[vl[i]] > 1) se=false;
        if(!se){
            cout << "NO\n";
            continue;
        }
        for(int i = 0; i<N; i++){
            for(int j = 2; j< 101; j++){
                dd[j][vl[i] % j]++;
            }
        }
        for(int i = 2; i < 101; i++){
            bool num = false;
            for(int j = 0; j < i; j++){
                if(dd[i][j] < 2) num = true;
            }
            if(!num) se = false;
        }
        if(!se){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}

