#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1000;

ll vadj[maxn][maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N, K;
        cin >> N >> K;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++) cin>>vadj[i][j];
        }

        ll notEq = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){ 
                if(vadj[i][j] != vadj[N-i-1][N-j-1]) notEq++;
            }
        }
        notEq/=2;
        K-=notEq;
        if(K < 0) {
            cout << "NO\n";
            continue;
        }
        if(N % 2 == 0){
            if(K % 2 == 0) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }

        cout << "YES\n";
    }
}
