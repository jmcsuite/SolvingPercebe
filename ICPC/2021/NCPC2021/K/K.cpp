#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vll vl(N);
    for (int i = 0; i < N; i++) cin >> vl[i];
    set<ll> st;
    for (int i = 0; i < N-1; i++) {
        ll x; cin >> x; st.insert(x);
    }

    for (int i = 0; i < N; i++) {
        if (st.find(vl[i]) == st.end()) {
            cout << vl[i] << '\n';
            return 0;
        }
    }
}

