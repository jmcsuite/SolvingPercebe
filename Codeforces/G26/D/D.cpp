#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

vector<int> z_func(string a) {
    // z[i] = max x such that [0, 1, ..., x) = [i, i+1, ..., i+x)
    // z[i] is the length
    vector<int> z(a.size(),0);
    for(int i = 1, l = 0, r = 0; i < (int)a.size(); ++i){
        if(i <= r) z[i] = min(r-i+1, z[i-l]);
        while(z[i] + i < (int)a.size() && a[z[i]] == a[z[i]+i])z[i]++;
        if(i+z[i]-1 > r)l = i, r = z[i]+i-1;
    }
    // optional: z[0] = a.size();
    return z;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        string a; cin >> a;
        ll N = a.size();
        vll nex(N+1, -1);
        for (int i = N-1; i >= 0; i--) {
            if (a[i] == 'a') nex[i] = nex[i+1];
            else nex[i] = i;
        }
        if (nex[0] == -1) {
            cout << N-1 << '\n';
            continue;
        }
        auto z = z_func(a.substr(nex[0]));
        z[0] = N-nex[0];

        ll ans = 0;
        for (int i = 1; i <= N; i++) {
            ll a_count = nex[0];
            ll j = nex[0];
            bool se = true;
            while (true) {
                if (z[j-nex[0]] < i) {
                    se = false;
                    break;
                }
                j += i;
                if (j == N) break;
                if (nex[j] == -1) break;
                a_count = min(a_count, nex[j] - j);
                j = nex[j];
            }
            if (se) ans += a_count + 1;
        }
        cout << ans << '\n';
    }
}
