#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll a, b;
ll diag[16];
ll dif[16];
ll col[8];
ll ans[8];

ll cc = 0;
void print() {
    ++cc;
    if (cc < 10) cout << " " << cc;
    else cout << cc;
    cout << "      ";
    for (int i = 0; i < 8; i++) cout << ans[i]+1 << (i == 7 ? '\n' : ' ');
}

void print_header() {
    cout << "SOLN       COLUMN\n";
    cout << " #      1 2 3 4 5 6 7 8\n\n";
}

void queens(int x) {
    if (x == 8) {
        print();
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (x == a && i != b) continue;
        if (col[i]) continue;
        if (dif[i-x+7]) continue;
        if (diag[i+x]) continue;
        ans[x] = i;
        col[i] = dif[i-x+7] = diag[i+x] = 1;
        queens(x+1);
        col[i] = dif[i-x+7] = diag[i+x] = 0;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T;
    cin >> T;
    bool first = false;
    while(T--) {
        cc = 0;
        cin >> b >> a;
        a--; b--;
        if (first) cout << '\n';
        first = true;
        print_header();
        queens(0);
    }
}
