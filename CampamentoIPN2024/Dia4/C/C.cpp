#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll n,k;

bool query(ll a, ll b, ll c) {
    cout << "? " << a << ' ' << b << ' ' << c << endl;
    string ans; cin>>ans;
    return (ans == "Yes");
}
ll get_rand() {
    ll x = rand();
    return (x%n) + 1;
}

vll calc_dis(ll a, ll b) {
    vll ans;
    for (int i=1; i<=n; i++) {
        if (query(a,i,b)) ans.push_back(i);
    }
    return ans;
}

ll calc_depth() {
    ll sum = 0; 
    ll kpow = 1;
    for (int i=1; i<=30; i++) {
        sum += kpow;
        if (sum == n) return i;
        kpow *= k;
    }
    return 0;
}

ll objective(ll depth) {
    return depth * 2 - 1;
}

ll iters(ll depth) {
    return depth-1;
}

ll make_leaf(ll a, ll b) {
    for (int i=1; i<=n; i++) {
        if (query(a, b, i)) b = i;
    }
    return b;
}

void solve(ll a, ll b, vll ans, ll it) {
    for (int i=0; i<it; i++) {
        ll c = b;
        for (ll x:ans) {
            if (x == a) continue;
            if (query(a,x,c)) c = x;
        }
        a = c;
    }
    cout << "! " << a << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(NULL));
    cin>>n>>k;
    ll d = calc_depth();
    ll o = objective(d);
    ll a = make_leaf(1,1);
    for (int i=0; i<27; i++) {
        ll b = make_leaf(a, get_rand());
        vll ans = calc_dis(a,b);
        if ((ll)ans.size() == o) {
            solve(a,b,ans, iters(d));
            return 0;
        }
    }
    return 0;
}
