#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll A,B;
    cin >> A >> B;
    ll ans = A/B;
    if(A%B) ans++;
    cout << ans << '\n';
}