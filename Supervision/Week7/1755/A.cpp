#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main() {
    ll a1, b1, a2, b2, n, m; 
    cin >> a2 >> b2 >> a1 >> b1 >> n >> m;

    bool sw = false;
    if (b1*a2 < a1*b2) {
        sw = true;
        swap(a1, b1);
        swap(a2, b2);
        swap(n, m);
    }

    double x = 0; 
    double y = 0;
    double c = double(a1*n) + double(b1*m);
    c /= 2;

    x = double(n);
    if (a1 != 0) x = min(x, c/a1);
    double res = c - x*double(a1);
    y = m; 
    if (b1 != 0) y = min(y, res/double(b1));

    if (sw) swap(x,y);
    cout << fixed << setprecision(9);
    cout << x << ' ' << y << '\n';
}
