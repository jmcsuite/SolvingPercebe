#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N; cin >> N;
    ll a = N/2;
    ll b = N-a;
    ll sobra = a%2 + b%2;
    sobra /= 2;
    a = a/2;
    b = b/2;
    cout << a*b + sobra*max(a,b) << '\n';
}