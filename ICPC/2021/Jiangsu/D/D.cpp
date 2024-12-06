#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

ll N, M;

void put2(ll i) {
    cout << i << ' ' << 1 << '\n';
    cout << i << ' ' << 2 << '\n';

    for (int j = 0; j + 2 < M; j++) {
        cout << (i+1) << ' ' << j+1 << '\n';
        cout << i << ' ' << j+3 << '\n';
    }

    cout << (i+1) << ' ' << M - 1 << '\n';
    cout << (i+1) << ' ' << M << '\n';
}


void put3(ll i) {

    ll j = 1; 
    if (M == 3) {
        cout << i << ' ' << j << '\n';
        cout << i << ' ' << j+1 << '\n';
        cout << i+2 << ' ' << j << '\n';
        cout << i+1 << ' ' << j+1 << '\n';
        cout << i+2 << ' ' << j+1 << '\n';
        cout << i << ' ' << j+2 << '\n';
        cout << i+1 << ' ' << j << '\n';
        cout << i+2 << ' ' << j+2 << '\n';
        cout << i+1 << ' ' << j+2 << '\n';
        return;
    }

    cout << i << ' ' << j << '\n';
    cout << i << ' ' << j+1 << '\n';
    cout << i+2 << ' ' << j << '\n';
    cout << i+1 << ' ' << j+1 << '\n';
    cout << i+2 << ' ' << j+1 << '\n';
    
    for (j = 2; j + 3 < M; j+=2) {
        cout << i <<  ' ' << j+1 << '\n';
        cout << i+1 <<  ' ' << j+1 << '\n';
        cout << i <<  ' ' << j+2 << '\n';
        cout << i+2 <<  ' ' << j+1 << '\n';
        cout << i+1 <<  ' ' << j+2 << '\n';
        cout << i+2 <<  ' ' << j+2 << '\n';
    }

    if (j == M) {
        cout << i+1 << ' ' << 1 << '\n';
        return;
    }

    
    if (M%2 == 0) {
        j = M-2;
        cout << i <<  ' ' << j+1 << '\n';
        cout << i+1 <<  ' ' << j+1 << '\n';
        cout << i <<  ' ' << j+2 << '\n';
        cout << i+2 <<  ' ' << j+1 << '\n';
        cout << i+1 <<  ' ' << j+2 << '\n';
        cout << i+2 <<  ' ' << j+2 << '\n';

        cout << i+1 << ' ' << 1 << '\n'; // last

        return;
    }

    j = M-3;
    cout << i <<  ' ' << j+1 << '\n';
    cout << i+1 <<  ' ' << j+1 << '\n';
    cout << i <<  ' ' << j+2 << '\n';
    cout << i+2 <<  ' ' << j+1 << '\n';
    cout << i+1 <<  ' ' << j+3 << '\n';
    cout << i+1 <<  ' ' << j+2 << '\n';
    cout << i+2 <<  ' ' << j+3 << '\n';
    cout << i+2 <<  ' ' << j+2 << '\n';
    cout << i <<  ' ' << j+3 << '\n';

    cout << i+1 << ' ' << 1 << '\n'; // last
    /*
    ll j = 1;
    cout << i << ' ' << j << '\n';
    cout << i << ' ' << j+1 << '\n';
    cout << i+2 << ' ' << j << '\n';
    cout << i+1 << ' ' << j << '\n';
    cout << i+2 << ' ' << j+1 << '\n';
    for (j = 2; j < M; j++) {
        cout << i << ' ' << j+1 << '\n';
        cout << i+1 << ' ' << j << '\n';
        cout << i+2 << ' ' << j+1 << '\n';
    }
    cout << i+1 << ' ' << j << '\n';
    */
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    ll i = 1;
    for (; i<=N-3; i+=2) {
        put2(i);
    }
    if (N%2 == 0) put2(i);
    else put3(i);
}
