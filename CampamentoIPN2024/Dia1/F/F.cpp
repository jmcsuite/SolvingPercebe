#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        vll vl(N); 
        for (int i = 0; i < N; i++) cin >> vl[i]; 
        ll vf = 0;
        for (int i = 1; i < N-1; i++) if (vl[i] < vl[i-1] && vl[i] < vl[i+1]) vf = i;
        double sum = 0; 
        double ans = 0;
        sum = vl[vf] + vl[vf+1] + vl[vf-1];
        ans = sum / 3;
        ll cc = 3;

        for (int i = vf + 2; i < N; i++) {
            sum += vl[i];
            cc++;
            ans = max(ans, sum / cc);
        }

        for (int i = vf - 2; i >= 0; i--) {
            sum += vl[i];
            cc++;
            ans = max(ans, sum / cc);
        }

        cc = 3; sum = vl[vf] + vl[vf+1] + vl[vf-1];

        for (int i = vf - 2; i >= 0; i--) {
            sum += vl[i];
            cc++;
            ans = max(ans, sum / cc);
        }

        for (int i = vf + 2; i < N; i++) {
            sum += vl[i];
            cc++;
            ans = max(ans, sum / cc);
        }

        cout << fixed << setprecision(10) << ans << '\n';
    }
}
