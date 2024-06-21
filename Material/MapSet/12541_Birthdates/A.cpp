#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 100;
pair<ll,pair<ll,pair<ll,string>>> vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> vl[i].second.second.second;
        cin >> vl[i].second.second.first;
        cin >> vl[i].second.first;
        cin >> vl[i].first;
    }
    sort (vl, vl + N);
    cout << vl[N-1].second.second.second << '\n';
    cout << vl[0].second.second.second << '\n';
}
