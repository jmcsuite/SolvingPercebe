#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using rp = pair<ll,pll>;

 rp mygcd(ll a, ll b) {
     if (a==0) return {b,{0,1}};
     if(b==0) return {a,{1,0}};
     rp prev=mygcd(b%a,a);

     ll bd = b/prev.first;
     ll ax = prev.second.second-prev.second.first*(b/a);
     ax = (ax%bd+bd)%bd;
     ll bx=(prev.first-a*ax)/b;
     rp ans={prev.first, {ax, bx}};
     return ans;
 }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll p,q; cin>>p>>q;
    ll i,j,k,l; cin>>i>>j>>k>>l;
    ll dx = (k-i);
    ll dy = (l-j);
    dx = max(dx, dx*-1);
    dy = max(dy, dy*-1);

    auto gg = mygcd(p, q);
    ll g = gg.first;
    if (dx % g) {
        cout << "NO\n"; return 0;
    }
    if (dy % g) {
        cout << "NO\n"; return 0;
    }

    ll A = gg.second.first * (dx/g);
    ll B = gg.second.second * (dx/g);

    ll X = gg.second.first * (dy/g);
    ll Y = gg.second.second * (dy/g);

    A%=2; B%=2; X%=2; Y%=2;
    
    ll pp = p/g;
    ll qq = q/g;
    if (pp%2 == 0) {
        cout << "YES\n";
        return 0;
    }

    if (qq%2 == 0) {
        cout << "YES\n";
        return 0;
    }

    if ((A == Y) && (B == X)) {
        cout << "YES\n";
        return 0;
    }

    if ((A != Y) && (B != X)) {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";
}

