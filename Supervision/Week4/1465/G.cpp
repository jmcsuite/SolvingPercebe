#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100;

set<ll> st;
ll getmex() {
    ll i=0;
    auto it = st.begin();
    while (it != st.end()) {
        if (*it != i) return i;
        i++;
        it++;
    }
    return i;
}

ll vl[maxn+1];

ll iter(ll x) {
    st.clear();
    if (x == 0) return 0;
    if (x == 1) return 1;
    if (x == 2) return 1;
    st.insert(vl[x-2]);
    for (int i=0; i<=x-3; i++) st.insert(vl[i] ^ vl[x-3-i]);
    return getmex();
}

string getbin(ll x) {
    string s;
    for (int i=0; i<20; i++) {
        if (x%2) s.push_back('1');
        else s.push_back('0');
        x/=2;
    }
    reverse(s.begin(), s.end());
    return s;
}

string sol(ll x) {
    return (x == 0 ? "Black" : "White");
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i=0; i<maxn; i++) vl[i] = iter(i);
    ll N; cin>>N;
    if (N < maxn) cout << sol(vl[N]) << '\n';
    else cout << sol(vl[(N-42)%34 + 42]) << '\n';
    /*
    for (int i=0; i<maxn; i++) {
        if (i >= 42) {
            assert((vl[i] == 0) == (vl[(i-42)%34 + 42] == 0));
            if (vl[i] != vl[(i-38)%34 + 38]) {
                cout << "ERROR: " << i << '\n';
                return 0;
            }
            //assert(vl[i] == vl[i%34 + 38]);
        }
        maxvi = max(maxvi, vl[i]);
        if (vl[i] == 0) {
            if (mostdiff < (i-prev)) mostdiff = (i-prev);
            prev = i;
            cout << i << ": " << getbin(i) << ' ' << vl[i] << '\n';
        }
    }
    cout << mostdiff << '\n';
    cout << maxvi << '\n';
    */
}
