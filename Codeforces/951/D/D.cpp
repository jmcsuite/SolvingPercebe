#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> kmp(string& s) {
    int n = s.size();
    vector<int> vs(n);
    for (int i = 1; i < n; i++) {
        int j = vs[i-1];
        while (j != 0 && s[i] != s[j]) j = vs[j-1];
        if (s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}

ll solve(string& a, string& b) {
    string c = a + "#" + b;
    int N = b.size();
    vector<bool> inv(N+1, false); inv[0] = true;
    for (int i = 1; i <= N; i++) {
        if (b[i-1] == a[N - i]) inv[i] = true;
        else break;
    }
    auto k = kmp(c);
    int M = c.size();

    /*
    cout << a << endl;
    for (int i = 1; i <= N; i++) cout << inv[i] << ' ';
    cout << endl;
    for (int i = 0; i < M; i++) cout << k[i] << ' ';
    cout << endl;
    */

    if (inv[N-k[M-1]]) return N-k[M-1];
    return -1;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, K; cin >> N >> K;
        string b; cin >> b;
        string a = b;
        for(int i = 0; i < N; i++) {
            if ((i/K)%2) a[i] = '1';
            else a[i] = '0';
        }
        ll aa = solve(a, b);
        for (int i = 0; i < N; i++) {
            if ((i/K)%2) a[i] = '0';
            else a[i] = '1';
        }
        ll bb = solve(a, b);
        aa = max(aa, bb);
        if (aa == 0) aa += N;
        cout << aa << '\n';
    }
}
