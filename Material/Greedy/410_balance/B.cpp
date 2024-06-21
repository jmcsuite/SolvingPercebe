#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M, N;
    ll T = 0;
    while (cin >> M >> N) {
        vll vl(N);
        for (int i = 0; i < N; i++) cin >> vl[i];
        while ((int)vl.size() < 2*M) vl.push_back(0);
        sort(vl.rbegin(), vl.rend());

        double sum = 0;
        for (int i = 0; i < N; i++) sum += vl[i];
        double med = sum / M;
        double imb = 0;

        cout << "Set #" << ++T << '\n';
        for (int i = 0; i < M; i++) {
            cout << ' ' << i << ":";
            if (vl[i] == 0) {
                cout << '\n';
                continue;
            }
            if(vl[2*M-i-1] == 0) {
                cout << " " << vl[i] << '\n';
            }
            else {
                cout << " " << vl[i] << ' ' << vl[2*M-i-1] << '\n';
            }
            double t = vl[i] + vl[2*M-i-1];
            imb += abs(t-med);
        }
        cout << "IMBALANCE = " << fixed << setprecision(5) << imb << "\n\n";
    }
}

