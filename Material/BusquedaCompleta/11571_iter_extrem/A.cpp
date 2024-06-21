#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long maxn = 1817120;

bool ans = false;
ll a,b,c;
ll A,B, C;


bool solve(ll x) {
    ll nA = A-x;
    ll nC = C - (x*x);
    if (x == -1000000000) cout << "HERE" << endl;
    if (nA <= 0) return false;
    if (nC <= 0) return false;
    unsigned long long uA = nA;
    unsigned long long uC = nC;
    if ((2*uC)/uA < uA) return false;
    unsigned long long sq = 2*uC - nA*nA;
    sq = sqrt(sq);
    if (sq*sq != (2*uC - nA*nA)) return false;
    
    ll z1 = nA + sq;
    if (z1 % 2) return false;
    z1 /= 2;
    ll y1 = nA - z1;
    if (((B/x)%z1)) return false;

    if (y1 == (B/z1)/x) {
        a = x;
        b = y1;
        c = z1;
        return true;
    }
    return false;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> A >> B >> C;
        bool s = false;
        for (ll i = -1*maxn; i <= maxn; i++) {
            if (i == 0) continue;
            if (B%i) continue;
            if (i*i*i >= B) break;
            if(!solve(i)) {
                continue;
            }
            s = true;
            cout << a <<  ' ' << b << ' ' << c << '\n';
            break;
        }
        if (s) continue;
        cout << "No solution.\n";
    }
}
