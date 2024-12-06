#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = 1e9 + 7;

ll sum, ans, no, br;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string s; cin >> s;
    ll N = s.size();

    for (int i = N-1; i>=0; i--) {
        if (s[i] == ')') {
            no++;
            br++;
            sum++;
        }
        else {
            ans = (ans + sum)%mod;
            sum = (sum*2)%mod + ((br-no)*no)%mod + (((no)*(no-1))/2)%mod - br;
            sum = ((sum%mod)+mod)%mod;
            no = 0;
        }
    }
    cout << ans << '\n';
}
