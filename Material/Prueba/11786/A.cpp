#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        stack<ll> st;
        string s; cin >> s;
        ll ans = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] == '\\') st.push(i);
            else if (s[i] == '_') continue;
            else if (st.empty()) continue;
            else {
                ll x = st.top();
                st.pop();
                ans += i-x;
            }
        }
        cout << ans << '\n';
    }
}
