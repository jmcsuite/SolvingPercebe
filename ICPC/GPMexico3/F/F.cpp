#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    cin >> N >> M;
    ll ans = 0; 
    string ast = "Z";
    unordered_map<string,ll> mp;
    for(int i = 0; i < N; i++){
        string aa;
        cin >> aa;
        for(int j = 0; j < M; j++){
            if(aa[j] != '*') continue;
            for(int k = 'a'; k <= 'z'; k++){
                aa[j] = k;
                mp[aa]++;
                if(mp[aa] < ans) continue;
                if(aa < ast || mp[aa] > ans){
                    ast = aa;
                    ans = mp[aa];
                }
            }
        }
    }

    cout << ast << ' ' << ans << '\n';
}