#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 5;
const int maxm = 1e4+1;

double sec[maxn][maxn][maxm];

pll vl[maxn];
double cant[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<N; i++) cin>>vl[i].first>>vl[i].second;
    for (int i=0; i<N; i++) cant[i]=vl[i].second-vl[i].first+1;

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (i == j) continue;
            for (int k=0; k<maxm; k++) {
                sec[i][j][k] = (k <= vl[j].second && k >= vl[j].first ? k/cant[j] : 0);
                double p=1;
                for (int l=0; l<N; l++) {
                    if (l == i) continue;
                    if (l == j) continue;
                    if (k < vl[l].first) {
                        p=0;
                        continue;
                    }
                    ll nk = k;
                    if (l < j) nk--;
                    double cc = min(ll(nk),vl[l].second)-vl[l].first+1;
                    cc /= cant[l];
                    p *= cc;
                }
                sec[i][j][k] *= p;
            }
        }
    }

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=1; k<maxm; k++) sec[i][j][k]+=sec[i][j][k-1];
        }
    }

    double ans = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            for (int k=vl[i].first; k<=vl[i].second; k++) {
                ll nk = k;
                if (j < i) nk--;
                ans += sec[i][j][nk]/cant[i];
            }
        }
    }

    cout << fixed << setprecision(10);
    cout << ans << '\n';
}
