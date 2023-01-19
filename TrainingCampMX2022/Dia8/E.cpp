#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

ll gcd(ll a, ll b){
    if(a==0) return b;
    if(b==0) return a;
    return gcd(b%a,a);
}

const double pi = std::acos(-1);

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vpll vl(N);
    for(int i=0; i<N; i++){
        cin>>vl[i].first>>vl[i].second;
    }
    ll ansdx=1;
    ll ansdy = 0;
    for(int i=1; i<N; i++){
        ll dx = vl[i].first-vl[0].first;
        ll dy = vl[i].second-vl[0].second;
        ll gg = gcd(dx,dy); //dy / dx;
        dx/=gg;
        dy/=gg;
        if(dx*ansdy < dy*ansdx){
            ansdx=dx;
            ansdy=dy;
        }
    }

    for(int i=0; i<N; i++){
        vl[i].first*=-1;
    }

    sort(vl.begin(),vl.end());
    for(int i=1; i<N; i++){
        ll dx = vl[i].first-vl[0].first;
        ll dy = vl[i].second-vl[0].second;
        ll gg = gcd(dx,dy); //dy / dx;
        dx/=gg;
        dy/=gg;
        if(dx*ansdy < dy*ansdx){
            ansdx=dx;
            ansdy=dy;
        }
    }

    // double ans = asin(double(ansdx)/double(ansdy))*2*pi/double(360);
     double ans = atan(double(ansdy)/double(ansdx))*double(360)/(2*pi);
    cout << fixed << setprecision(9) << ans << endl;
}
    



