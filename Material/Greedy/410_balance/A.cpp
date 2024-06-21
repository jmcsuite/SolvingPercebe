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
        vector<pair<ll,ll>> vl(N);
        for (int i = 0; i < N; i++) cin >> vl[i].first;
        for (int i = 0; i < N; i++) vl[i].second = i;
        while ((int)vl.size() < 2*M) vl.push_back({0, N});
        sort(vl.rbegin(), vl.rend());

        double sum = 0;
        for (int i = 0; i < N; i++) sum += vl[i].first;
        double med = sum / M;
        double imb = 0;

        vector<pair<ll,pair<ll,ll>>> vp;
        for (int i = 0; i < M; i++) {
            double t = vl[i].first + vl[2*M-i-1].first;
            imb += abs(t-med);
            if (vl[i].second < vl[2*M-i-1].second) {
                vp.push_back({vl[i].second , {vl[i].first, vl[2*M-i-1].first}});
            }
            else
            {
                vp.push_back({vl[2*M-i-1].second, {vl[2*M-i-1].first, vl[i].first}});
            }
        }
        sort(vp.begin(), vp.end());
        cout << "Set #" << ++T << '\n';
        for (int i = 0; i < M; i++) {
            cout << " " << i << ":";
            if (vp[i].second.first == 0) {
                cout << '\n'; 
                continue;
            }
            if (vp[i].second.second == 0) {
                cout << ' ' <<  vp[i].second.first << '\n';
            }
            else {
                cout << ' ' << vp[i].second.first << ' ' << vp[i].second.second << '\n';
            }
        }
        cout << "IMBALANCE = " << fixed << setprecision(5) << imb << "\n\n";
    }
}
