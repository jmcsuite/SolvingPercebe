#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100;

queue<int> q[maxn];
stack<int> s;

int main() {
    ll T; cin >> T;
    while (T--) {
        ll N; size_t S, Q;
        cin >> N >> S >> Q;
        ll M = 0;
        for (int i =0; i < N; i++) {
            ll x; cin >> x; 
            M += x; 
            for (int j = 0; j < x; j++) {
                ll y; cin >> y; y--;
                q[i].push(y);
            }
        }
        ll ans = 0, A = 0, i = 0;
        while (1) {
            // Unload
            while(1) {
                if (s.empty()) break;
                if (s.top() == i) {
                    A++; ans++; s.pop(); continue;
                }
                if (q[i].size() < Q) {
                    q[i].push(s.top());
                    s.pop();
                    ans++;
                    continue;
                }
                break;
            }
            if (A == M) break;
            // Load
            while(1) {
                if (q[i].empty()) break;
                if (s.size() == S) break;
                s.push(q[i].front()); q[i].pop(); 
                ans++;
            }
            // Move
            i = (i+1)%N;
            ans += 2;
        }
        cout << ans << '\n';
    }
}
