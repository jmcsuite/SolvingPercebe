#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


bool pos(ll N, ll K) {
    ll ans=1;
    for (ll i=1; i<=N; i++) {
        ans = i*ans;
        if (ans >= K) return true;
    }
    return false;
}


bool check(vll& perm, vll& inv, vll& b, vll& c) {
    ll n = perm.size();
    bool se=true;
    for (int i=0; i<n; i++) {
        if (perm[i] != c[i]) {
            se=false;
            break;
        }
    }
    if (se) return false;

    se=true;
    for (int i=0; i<n; i++) {
        if (inv[i] != b[i]) {
            se=false;
            break;
        }
    }
    if (se) return false;

    se=true;
    for (int i=0; i<n; i++) {
        if (inv[i] != c[i]) {
            se=false;
            break;
        }
    }
    if (se) return false;

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin >> T;
    while (T--) {
        ll N,K;
        cin >> N >> K;
        if (K == 1) {
            if (N == 1) {
                cout << "YES\n";
                cout << 1 << '\n';
                continue;
            }
            cout << "NO\n";
            continue;
        }

        ll need=K;
        if ((N%2 == 0) && (K%2 == 1)) {
            cout << "NO\n";
            continue;
        }

        

        vll a(N);
        vll b(N);
        vll c(N);

        if (K%2) {
            if (!pos(N,K+3))  {
                cout << "NO\n";
                continue;
            }
            need = K-3;
            for (int i=0; i<N; i++) a[i] = i+1;
            for (int i=0; i<N; i++) b[i] = (N - i*2);
            for (int i=0; i<N; i++) if (b[i] <= 0) b[i]+=N;
            for (int i=0; i<N; i++) c[i] = 3*(N+1)/2 - a[i] - b[i];
        }
        else if (!pos(N,K)) {
            cout << "NO\n";
            continue;
        }

        vll perm(N);
        for (int i=0; i<N; i++) perm[i]=i+1;
        if (K%2) next_permutation(perm.begin(), perm.end());

        vll inv(N);
        vector<vll> ans;
        while (need) {
            for (int i=0; i<N; i++) inv[i] = (N+1) - perm[i];
            if (check(perm,inv,b,c)) {
                need-=2;
                ans.push_back(perm);
                ans.push_back(inv);
            }
            next_permutation(perm.begin(), perm.end());
        }
        cout << "YES\n";
        if (K%2) {
            for (int i=0; i<N; i++) cout << a[i] << ' ';
            cout << '\n';
            for (int i=0; i<N; i++) cout << b[i] << ' ';
            cout << '\n';
            for (int i=0; i<N; i++) cout << c[i] << ' ';
            cout << '\n';
        }
        for (int i=0; i<(int)ans.size(); i++) {
            for (int j=0; j<N; j++) cout << ans[i][j] << ' ';
            cout << '\n';
        }
    }
}
