#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1<<9;
const int N = 3;
int dp[maxn];
ll vl[N][N];
ll tmp[N][N];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

bool valid(ll i, ll j) {
    if (i < 0 || i >= N) return false;
    if (j < 0 || j >= N) return false;
    return true;
}

void apply() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll s = 0;
            for (int k = 0; k < 4; k++) {
                ll ni = i + dx[k];
                ll nj = j + dy[k];
                if(!valid(ni, nj)) continue;
                s += vl[ni][nj];
            }
            tmp[i][j] = s % 2u;
        }
    }
    swap(tmp, vl);
}


ll get() {
    ll s = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll idx = i*N + j;
            s += vl[i][j] * (1 << idx);
        }
    }
    return s;
}

void debug() {
    return;
    cout << "print \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << vl[i][j];
        }
        cout << '\n';
    }
    cout << get() << '\n';
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin >> T; 
    while (T--) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char a; cin >> a;
                vl[i][j] = a-'0';
            }
        }
        for (int i = 0; i < maxn; i++) dp[i] = -1;

        for (int j = 0; j < maxn; j++) {
            debug();
            ll p = get();
            if (dp[p] != -1) {
                cout << dp[p] - 1 << '\n';
                break;
            }
            dp[p] = j;
            apply();
        }
    }
}
