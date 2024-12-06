#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
using vll = vector<ll>;

const int maxn = 1e5 + 2;

const int mod[2] = {999999197, 999999353};
ll powpow[2][maxn];

void build() {
    for (ll k = 0; k < 2; k++) {
        powpow[k][0] = 1;
        for (int i = 1; i < maxn; i++) powpow[k][i] = (powpow[k][i-1]*mod[k]);
    }
}

ll p1[2][maxn];
ll p2[2][maxn];

void prefixes(string& s) {
    int N = s.size();
    for (int k = 0; k < 2; k++) {
        for (int i = N-1; i>=0; i--) {
            p1[k][i] = s[i]-'a';
            if (i != N-1) p1[k][i] = (p1[k][i] + p1[k][i+1]*mod[k]);
        }
    }

    for (int k=0; k < 2; k++) {
        for (int i=0; i<N; i++) {
            p2[k][i] = ((s[i]-'a')*powpow[k][N-1-i]);
            if (i != 0) p2[k][i] = (p2[k][i] + p2[k][i-1]);
        }
    }
}

ll getSum1(int i, ll x, ll N, ll k) {
    if (i+x >= N) return p1[k][i];
    return (p1[k][i] - p1[k][i+x]*powpow[k][x]);
}

ll getSum2(int i, ll x, ll N, ll k) {
    if (i == 0) return 0;
    if (i+x <= N) return 0;
    if (x == N) return p2[k][i-1];
    return (p2[k][i-1] - p2[k][N-x-1]);
}

ll getHash(int i, ll x, ll N, ll k) {
    ll s1 = getSum1(i,x,N,k);
    ll s2 = getSum2(i,x,N,k);
    return (s1+s2);
}

bool eqString(int i, int j, ll x, ll N) {
    ll h1 = getHash(i,x,N,0) - getHash(j,x,N,0);
    ll h2 = 0;//getHash(i,x,N,1) - getHash(j,x,N,1);
    if (h1 == 0 && h2 == 0) return true;
    return false;
}

// pos x
char getChar(int i, ll x, string& s) {
    ll N = s.size();
    if (i+x < N) return s[i+x];
    return s[N-x-1];
}

// remember call build and prefixes;
int prefixSize;
string prefix;

bool leq(int a, int b) {
    ll N = prefixSize;
    ll ans = 0; ll dis = N-1;
    if (eqString(a,b,N,N)) return false;
    while (dis) {
        if (ans + dis < N && eqString(a,b,ans+dis,N)) ans+=dis;
        else dis/=2;
    }
    return getChar(a,ans,prefix) < getChar(b,ans,prefix);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    build();
    ll T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int N = s.size();
        if (N == 1) {
            cout << s << '\n';
            continue;
        }

        vector<int> vl(N);
        for (int i = N-1; i>=0; i--) {
            vl[i] = s[i];
            if (i+1 != N) vl[i] = min(vl[i], vl[i+1]);
        }
        int pos=N-1;
        for (int i = N-2; i>=0; i--) {
            if (s[i] > vl[i+1]) pos=i;
        }

        if (pos == N-1) {
            cout << s << '\n';
            continue;
        }

        prefix = "";
        for (int i = N-1; i>=pos; i--) prefix.push_back(s[i]);
        prefixSize = prefix.size();
        prefixes(prefix);

        ll pf = 0;
        for (int i = 0; i < prefixSize; i++) if (leq(i, pf)) pf = i;

        for (int i = 0; i < pos; i++) cout << s[i];
        for (int i = pf; i < prefixSize; i++) cout << prefix[i];
        for (int i = pf-1; i >= 0; i--) cout << prefix[i];
        cout << '\n';
    }
}
