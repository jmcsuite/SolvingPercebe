#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5+1;
vector<double> p[maxn];
double ex[maxn];
double v[maxn];

vll dv[maxn];

ll crib[maxn];

ll gcd(ll a, ll b) {
    if (a==0) return b;
    if (b==0) return a;
    return gcd(b%a, a);
}

void build() {
    for (int i=2; i<maxn; i++) {
        if (crib[i]) continue;
        for (int j=1; j*i<maxn; j++) {
            if (crib[i*j]) continue;
            crib[i*j]=i;
        }
    }


    for (ll i=1; i<maxn; i++) {
        for (ll j=1; j*i<maxn; j++) {
            dv[i*j].push_back(i);
        }
    }
}

int main() {
    build();
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vll vl(N);
    for (int i=0; i<N; i++) cin >> vl[i];
    ll T=0; for (int i=0; i<N; i++) T+=vl[i];
    for (int i=0; i<N; i++) v[i+1]=double(vl[i])/double(T);

    for (ll i=1; i<=N; i++) {
        p[i].push_back(0);
        for (ll k=1; k*i<=N; k++) {
            p[i].push_back(0);

            ll mult = k;
            for (ll p=i; p>1; p/=crib[p]) {
                if (k%crib[p] == 0) mult*=crib[p];
            }
            if (mult > N) continue;

            ll gk = gcd(mult,i);
            for (ll d: dv[i/gk]) {
                if (d*mult > N) continue;
                p[i][k] += v[d*gk*k];
            }
        }
    }

    for (ll i=N; i>=1; i--) {
        for (ll k=2; k*i<=N; k++) {
            ex[i] += p[i][k]*(1+ex[i*k]);
        }
        ex[i] += p[i][1];
        ex[i] /= (1-p[i][1]);
    }
    cout << fixed << setprecision(10);
    cout << ex[1] << '\n';
}
