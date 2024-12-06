#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5 + 5;
ll a[maxn];
ll b[maxn];


ll L; ll extL;
ll R; ll extR;


void moveLL() {
    ll prevL = L;
    L = extL;
    if (a[L] == prevL) extL = b[L];
    else extL = a[L];
}

void moveLR() {
    ll prevL = L;
    if (a[L] == extL) L = b[L];
    else L = a[L];
    extL = prevL;
}

void moveRR() {
    ll prevR = R;
    R = extR;
    if (a[R] == prevR) extR = b[R];
    else extR = a[R];
}

void moveRL() {
    ll prevR = R;
    if (a[R] == extR) R = b[R];
    else R = a[R];
    extR = prevR;
}

void flip() {
    if (a[extL] == L) a[extL] = R;
    else b[extL] = R;


    if (a[extR] == R) a[extR] = L;
    else b[extR] = L;

    if (a[L] == extL) a[L] = extR;
    else b[L] = extR;

    if (a[R] == extR) a[R] = extL;
    else b[R] = extL;

    swap(L,R);
    //swap(extL, extR);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N >> L >> R;
    extL = L-1; 
    extR = R+1;

    for (int i = 0; i<=N+1; i++) {
        a[i] = i-1;
        b[i] = i+1;
    }

    string s; cin>>s;
    ll M; cin >> M;
    while (M--) {
        char c; cin >> c;
        if (c == 'R') {
            flip(); continue;
        }
        if (c == 'Q') {
            char l; cin >> l;
            if (l == 'L') cout << s[L-1];
            else cout << s[R-1];
            continue;
        }
        char a,b; cin >> a >> b;
        if (a == 'L' && b == 'L') moveLL();
        if (a == 'L' && b == 'R') moveLR();
        if (a == 'R' && b == 'L') moveRL();
        if (a == 'R' && b == 'R') moveRR();
    }
    cout << '\n';
}
