#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5;
ll vl[maxn];
map<ll,ll> mp;

ll T,N;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while(T--) {
        cin >> N;
        mp.clear();
        for (int i = 0; i < N; i++) cin >> vl[i];
        vll a,b;
        ll x = 0;
        for (int i = 0; i < N; i++) {
            if (vl[i] == 1) x = i%2;
        }
        for (int i = 0; i < N; i++) {
            if (i%2 == x) a.push_back(vl[i]);
            else b.push_back(vl[i]);
        }
        sort(a.rbegin(), a.rend());
        sort(b.begin(), b.end());
        for (int i = 0; i < N/2; i++) mp[a[i]] = i+1;
        for (int i = 0; i < N/2; i++) mp[b[i]] = N-i;
        for (int i = 0; i < N; i++) {
            cout << mp[vl[i]] << (i == N-1 ? '\n' : ' ');
        }
    }
}
