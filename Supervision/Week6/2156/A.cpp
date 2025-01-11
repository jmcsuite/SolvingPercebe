#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5;
ll vl[maxn];
ll d[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N; cin>>N; 
    for (int i=0; i<N; i++) cin>>vl[i];
    for (int i=0; i<N-1; i++) d[i] = vl[i+1]-vl[i];
    d[N-1] = vl[0] - vl[N-1];

    vector<ll> a,b;
    for (int i=0; i<N; i++) {
        if (d[i] > 0) a.push_back(i+1);
        else if (d[i] < 0) b.push_back(i+1);
        else if (a.empty()) a.push_back(i+1);
        else b.push_back(i+1);
    }


    cout << "YES\n";
    cout << a.size() << '\n';
    for (size_t i=0; i<a.size(); i++) cout << a[i] << (i+1 == a.size() ? '\n' : ' ');
    cout << b.size() << '\n';
    for (size_t i=0; i<b.size(); i++) cout << b[i] << (i+1 == b.size() ? '\n' : ' ');
}

