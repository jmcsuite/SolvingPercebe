#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    double ans = 0;
    N-=2;

    for (int k=0; k<N; k++) {
        for (int j=0; j<=k; j++) {
            double sum=1;
            for (int i = j, kk = k+1; i>0; i--,kk--) {
                sum *= (double(1) / double(kk));
            }
            sum *= 1.0 / double (k-j+1);
            ans += sum * 10;
        }
    }
    cout << fixed << setprecision(7);
    cout << ans << '\n';
}

