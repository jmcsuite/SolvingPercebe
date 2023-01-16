#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--){
        ll N,M; cin>>N>>M;
        multiset<ll> st;
        for(int i = 0; i<N; i++){
            ll a; cin>>a;
            st.insert(a);
        }

        for(int i = 0; i<M; i++){
            ll a; cin>>a;
            st.erase(st.begin());
            st.insert(a);
        }

        ll sum = 0;
        for(auto it = st.begin(); it != st.end(); it++){
            sum += *it;
        }
        cout << sum << '\n';
    }
}

