#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 601;

ll perms[maxn][maxn];
ll used[maxn];
ll spoiled[maxn];
ll need[maxn];
ll a[maxn];

ll n,m;
bool valid() {
    for (int i=0; i<n; i++) spoiled[i] = used[i] = 0;
    ll t = 0;
    for (int i=0; i<m; i++) {
        for (int k=0; k<n; k++) {
            if (spoiled[perms[i][k]]) continue;
            if (used[perms[i][k]]) continue;
            if (need[perms[i][k]] == 0) {
                spoiled[perms[i][k]] = 1;
                break;
            }
            used[perms[i][k]] = ++t;
        }
        if (t > a[i]) return false;
    }
    for (int i=0; i<n; i++) if (need[i] && !used[i]) used[i] = ++t;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for (int i=0; i<m; i++) cin>>a[i];
    for (int k=0; k<m; k++) {
        for (int i=0; i<n; i++) cin>>perms[k][i];
        for (int i=0; i<n; i++) --perms[k][i];
    }

    for (int i=0; i<n; i++) {
        need[i] = 1;
        if (!valid()) need[i] = 0;
    }

    valid();
    vll ans(n-m+1);
    for (int i=0; i<n; i++) ans[used[i]] = i;
    for (int i=1; i<n-m+1; i++) cout << ans[i]+1 << (i == n-m ? '\n' : ' ');
}
