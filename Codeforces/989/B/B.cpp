#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N,M,K; cin >> N >> M >> K;
        string s; cin >> s;
        ll sum,ans;
        sum = ans = 0;

        for (int i=0; i<N; i++) {

            if (s[i] == '0') sum++;
            else sum=0;

            if (sum == M) {
                for (int j=i; j<N && j<i+K; j++) s[j]='1';
                ans++;
                sum=0;
            }
        }
        cout << ans << '\n';
    }
}
