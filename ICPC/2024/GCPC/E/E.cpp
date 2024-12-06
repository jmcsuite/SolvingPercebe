#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 300;
int dp[maxn+1][maxn+1][maxn+1][2][2];

void ff() {
    // a set *2
    // b set +1
    // c set +0
    dp[0][0][0][0][0] = 1;
    dp[0][0][0][1][1] = 1;
    for (int a = 0; a <= maxn; a++) {
        for (int b = 0; b <= maxn; b++) {
            for (int c = 0; c <= maxn; c++) {
                for (int k = 0; k < 2; k++) {
                    for (int x = 0; x < 2; x++) {
                        int ia = 1; 
                        int ib = 1;
                        int ic = 1;
                        if (a > 0) ia = dp[a-1][b][c][(k+1)%2][0];
                        if (b > 0) ib = dp[a][b-1][c][(k+1)%2][(x+1)%2];
                        if (c > 0) ic = dp[a][b][c-1][(k+1)%2][x];
                        if (ia == 0) dp[a][b][c][k][x] = 1;
                        if (ib == 0) dp[a][b][c][k][x] = 2;
                        if (ic == 0) dp[a][b][c][k][x] = 3;
                    }
                }
            }
        }
    }
}


set<pair<char,int>> a;
set<pair<char,int>> b;
set<pair<char,int>> c;

void read() {
    ll N; cin >> N;
    for (int i = 0; i < N; i++) {
        char o; int x; cin >> o >> x;
        if (o == '+' && x%2) b.insert({o,x});
        else if (o == '*' && (x%2 == 0)) a.insert({o,x});
        else c.insert({o,x});
    }
}

void out(set<pair<char,int>>& s) {
    cout << s.begin()->first << ' ' << s.begin()->second << endl;
    s.erase(s.begin());
}

int play(int k, int x) {
    int p = dp[a.size()][b.size()][c.size()][k][x];
    if (p == 1) {
        x = 0;
        out(a);
    }
    if (p == 2) {
        x = (x+1)%2;
        out(b);
    }
    if (p == 3) out(c); 
    return x;
}

int wait(int px) {
    char o; int x; cin >> o >> x;
    if (o == '+' && x%2) b.erase({o,x});
    else if (o == '*' && (x%2 == 0)) a.erase({o,x});
    else c.erase({o,x});

    if(o == '+') px = (px + x)%2;
    else px = (px*x)%2;
    return px;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    read();
    ff();
    int x; cin >> x; x%=2;
    int k = 0;
    if (dp[a.size()][b.size()][c.size()][1][x] > 0) {
        cout << "me" << endl;
        k = 1;
    }
    else {
        cout << "you" << endl;
        x = wait(x);
    }

    while(1) {
        if (a.empty() && b.empty() && c.empty()) break;
        x = play(k,x);
        if (a.empty() && b.empty() && c.empty()) break;
        x = wait(x);
    }
}
