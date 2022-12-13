#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll maxS = 31624;
    vector<bool> vs(maxS,true);
    ll cc = 0;
    for(int i = 2; i < maxS; i++){
        if(vs[i]){
            cc++;
            for(int j = 2; j*i < maxS; j++){
                vs[i*j] = false;
            }
        }
    }
    vll ind(cc);
    ll it = 0;
    for(int i = 2; i < maxS; i++){
        if(vs[i]){
            ind[it] = i;
            it++;
        }
    }

    ll T; cin >> T;
    while(T--){
        unordered_set<ll> st;
        ll N; cin >> N;
        bool ans = true;
        for(int i = 0; i < N; i++){
            ll a; cin >> a;
            if(!ans) continue;
            if(st.find(a) != st.end()) ans = false;
            if(!ans) continue;
            st.insert(a);
            for(int j = 0; j < cc; j++){
                if(ind[j] >= a) break;
                if(a%ind[j] == 0){
                    if(st.find(ind[j]) != st.end()) ans = false;
                    if(!ans) break;
                    st.insert(ind[j]);
                }
            }
        }
        cout << (ans ? "NO" : "YES") << '\n';
    }
}

