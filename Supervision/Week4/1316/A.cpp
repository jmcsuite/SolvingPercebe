#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
using map_t = tree<pll,null_type,less<pll>,rb_tree_tag,
      tree_order_statistics_node_update>;

map_t st;


ll cc;
ll ans;

void bid() {
    ll x; cin >> x; x*=100;
    if (cin.peek() == '.') {
        char c;
        cin >> c;
        ll base = 10;
        while (cin.peek() != ' ' && cin.peek() != '\n') {
            char a; cin >> a;
            x += base * (a-'0');
            base/=10;
        }
    }

    st.insert({-1*x,cc});
    cc++;
}

void del() {
    ll x; cin >> x; x*=100;
    if (cin.peek() == '.') {
        char c;
        cin >> c;
        ll base = 10;
        while (cin.peek() != ' ' && cin.peek() != '\n') {
            char a; cin >> a;
            x += base * (a-'0');
            base/=10;
        }
    }
    
    st.erase(st.lower_bound({-1*x, 0}));
}

void sale() {
    ll x; cin >> x; x*=100;
    if (cin.peek() == '.') {
        char c;
        cin >> c;
        ll base = 10;
        while (cin.peek() != ' ' && cin.peek() != '\n') {
            char a; cin >> a;
            x += base * (a-'0');
            base/=10;
        }
    }

    ll k;
    cin >> k;

    ll cons = st.order_of_key({-1*x, 1e9});
    ans += min(cons, k);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    while (cin>>s, s!="QUIT") {
        if (s == "BID") bid();
        if (s == "SALE") sale();
        if (s == "DEL") del();
    }
    cout << fixed << setprecision(2);
    cout << double(ans)/100.0 << '\n';
}

