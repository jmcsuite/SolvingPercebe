#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
const int maxn = 100;

bool vis[maxn][maxn];
pll nn[maxn][maxn];
ll dis[maxn][maxn];
pll pp[maxn][maxn];

ll n;
bool valid(ll x, ll y) {
    if (x < 0 || y < 0) return false;
    if (x >=n || y >= n) return false;
    return true;
}

pll d[4] = {{0,1}, {1,0}, {-1, 0}, {0,-1}};
void calc() {
    queue<pll> q;
    vis[1][0] = true;
    pp[1][0] = {1,0};
    q.push({1,0});

    while (!q.empty()) {
        pll x = q.front(); q.pop();
        for (int i=0; i<4; i++) {
            pll z = {x.first + d[i].first, x.second + d[i].second};
            if (!valid(z.first, z.second)) continue;
            if (vis[z.first][z.second]) continue;
            vis[z.first][z.second] = true;
            pp[z.first][z.second] = x;
            q.push(z);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll k;
    cin >> n >> k;
    if(k%2) {
        cout << "Unsuitable device\n";
        return 0;
    }
    if (n*n < k) {
        cout << "Unsuitable device\n";
        return 0;
    }
    // row 0;
    for (int i=0; i<n; i++) nn[0][i] = {0,i+1};
    nn[0][n-1] = {1,n-1};
    // alternating columns
    bool dd = true;
    for (int j=n-1; j>=0; j--) {
        for (int i=1; i<n; i++) {
            pll a = {i+1,j};
            pll b = {i-1,j};
            nn[i][j] = (dd ? a : b);
        }
        dd = !dd;
    }
    // connect columns
    dd = true;
    for (int j=n-1; j>=0; j--) {
        if (dd) {
            nn[n-1][j] = {n-1, j-1};
        }
        else {
            nn[1][j] = {1, j-1};
        }
        dd = !dd;
    }

    // odd case
    dd = true;
    if (n%2) {
        for (int i = n-1; i>=1; i--) {
            if (dd) {
                nn[i][1] = {i,0};
                nn[i][0] = {i-1, 0};
            }
            else {
                nn[i][0] = {i,1};
                nn[i][1] = {i-1, 1};
            }
            dd = !dd;
        }
    }

    vpll ans;
    ll x = 0; ll y = 0;
    while (k) {
        k--;
        ans.push_back({x,y});

        ll dx = max(1-x, x-1);
        dx += y;
        if (dx != k) {
            vis[x][y] = true;
            pll p = nn[x][y];
            x = p.first; 
            y = p.second;
            continue;
        }
        calc();

        while (x != 1 || y != 0) {
            pll p = pp[x][y];
            x = p.first; y = p.second;
            ans.push_back({x,y});
        }
        break;
    }

    cout << "Overwhelming power of magic\n";
    for (pll p: ans) {
        cout << p.first + 1 << ' ' << p.second + 1 << '\n';
    }
}
