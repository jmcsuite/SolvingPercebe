#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = (1 << 17);
ll dp[maxn];
ll vl[maxn];
ll freq[17];

ll N, M;

void add_dp() {
    string x; cin >> x;
    ll mask = 0;
    for (char c : x) {
        mask |= (1 << (c-'a'));
    }
    dp[mask] = 1;
}

void calc() {
    for (ll j = 1; j < maxn; j *= 2) {
        for (ll i = 0; i < maxn; i++) {
            if (i&j) dp[i] |= dp[i-j];
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> M;
    for (int i = 0; i < M; i++) add_dp();
    calc();
    string s; cin >> s;
    N = s.size(); 
    for (int i = 0; i < N; i++) vl[i] = s[i]-'a';

    ll i,j, mask, ans; 
    i = j = mask = ans = 0;
    // [), agregar [0, 1);
    while(1) {
        if (dp[mask]) {
            ans += N-j + 1; 
            freq[vl[i]]--;
            if (freq[vl[i]] == 0) mask -= (1<<vl[i]);
            i++;
            continue;
        }
        if(j == N) break;
        freq[vl[j]]++;
        if (freq[vl[j]] == 1) mask |= (1<<vl[j]);
        j++;
    }
    cout << ans << '\n';
}
        
