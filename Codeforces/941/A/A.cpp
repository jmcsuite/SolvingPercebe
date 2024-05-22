#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        set<ll> st;
        for (int i = 0; i < N; i++) {
            ll x; cin >> x;
            st.insert(x);
        }

        ll cc = 0;
        ll idx = 1;
        auto it_end = st.end(); 
        it_end--;
        for(auto it = st.begin(); it != it_end; it++, idx++) {
            if (*it != idx) break;
            cc++;
        }
        cout << (cc%2 ? "Bob\n" : "Alice\n");
    }
}
