#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1000;
bool badRow[maxn];
bool needLight[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, K; 
    cin >> N >> M >> K;

    for (int i=0; i<N; i++) {
        string s; cin >> s;
        for(char c: s) if (c == '-') badRow[i]=true;
        cin >> s;
        for(char c: s) if (c == '*') needLight[i]=true;
        if (badRow[i] && needLight[i]) {
            cout << "N\n";
            return 0;
        }
    }
    cout << "Y\n";
}

