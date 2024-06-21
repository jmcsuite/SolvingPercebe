#include <bits/stdc++.h>
using namespace std;
using ll = long long;


bool check(ll a, ll b) {
    string aa = to_string(a);
    string bb = to_string(b);
    vector<int> check(10, 0);
    for (char c : aa) check[c-'0']++;
    for (char c : bb) check[c-'0']++;
    for (int i = 1; i < 10; i++) if(check[i] != 1) return false;
    return true;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    bool se = false;
    while (cin>>N, N) {
        if (se) cout << '\n';
        se = true;

        bool ans = false;
        for (int i = 1; i <= 99999; i++) {
            if(i%N) continue;
            int j = i/N;
            if(check(i,j)) {
                ans = true;
                string ii = to_string(i);
                string jj = to_string(j);
                if (i < 10000) ii = "0" + ii;
                if (j < 10000) jj = "0" + jj;
                cout << ii << " / " << jj << " = " << N << '\n';
            }
        }
        if (ans == false) {
            cout << "There are no solutions for " << N << ".\n";
        }
    }
}
