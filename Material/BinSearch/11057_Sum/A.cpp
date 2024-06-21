#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 10000;
ll vl[maxn];
ll N; 

bool search(ll pos, ll s) {
    int ans = pos; 
    int dis = N/2 + 1;
    while (dis) {
        if (dis + ans < N && vl[dis+ans] <= s) ans += dis;
        else dis/=2;
    }
    if (ans == pos) return false;
    if (vl[ans] != s) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> N) {
        for (int i = 0; i < N; i++) cin >> vl[i];
        sort(vl, vl + N);
        ll M; cin >> M;
        ll a, b;
        for (int i = 0; i < N; i++) {
            if (search(i, M-vl[i])) {
                a = vl[i];
                b = M-vl[i];
            }
        }
        cout << "Peter should buy books whose prices are " << a << " and " << b << ".\n\n";
    }
}
