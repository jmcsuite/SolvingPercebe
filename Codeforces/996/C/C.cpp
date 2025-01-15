#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1000;
ll vl[maxn][maxn];
ll vis[maxn][maxn];
pll ans[maxn * 2];

ll sumrow[maxn];
ll sumcol[maxn];

void solve() {
    ll n,m; cin>>n>>m;
    string s; cin>>s;
    for (int i=0; i<n; i++) for(int j=0; j<m; j++) cin>>vl[i][j];
    for (int i=0; i<n; i++) for(int j=0; j<m; j++) vis[i][j] = 0;
    ll x,y; x=y=0;
    vis[x][y]=1;
    ll k=1;
    for (char c: s) {
        if (c == 'D') x++; 
        else y++;
        k++;
        vis[x][y]=k;
    }
    s.push_back(s.back());


    for (int i=0; i<n; i++) {
        sumrow[i] = 0;
        for (int j=0; j<m; j++) sumrow[i] += vl[i][j];
    }

    for (int j=0; j<m; j++) {
        sumcol[j] = 0;
        for (int i=0; i<n; i++) sumcol[j] += vl[i][j];
    }

    ll xprev = 0;
    ll sumprev = 0;

    char p = s[0];
    x=y=0;
    for (size_t i=0; i<s.size(); i++) {
        ll sum = 0;
        if (s[i] == 'D') {
            sum = sumrow[x];
            x++;
        }
        else {
            sum = sumcol[y];
            y++;
        }

        if (s[i] != p) {
            ans[i].first = 1 - xprev;
            ans[i].second = -1 * sum - sumprev;
            xprev = ans[i].first;
            sumprev = ans[i].second;
        }
        else {
            ans[i].first = 1;
            ans[i].second = -1 * sum;
            xprev += ans[i].first;
            sumprev += ans[i].second;
        }
        p = s[i];
    }

    pll eq; 
    ll sum = 0;
    if (s[s.size() - 1] == 'D') sum = sumrow[n-1];
    else sum = sumcol[m-1];

    eq.first = 1; 
    eq.second = -1 * sum;

    x=0;
    if (eq.first - ans[s.size() - 1].first != 0) {
        ll delta = eq.first - ans[s.size() - 1].first;
        ll yy = ans[s.size() - 1].second - eq.second;
        x = yy / delta;
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (vis[i][j] == 0) cout << vl[i][j];
            else cout << ans[vis[i][j]-1].first * x + ans[vis[i][j]-1].second;
            cout << (j+1 == m ? '\n' : ' ');
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}
