#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;

double dis(ll a, ll b, ll da, ll db){
    return sqrt((da-a)*(da-a) + (db-b)*(db-b));
}

int main(){
    ll N; cin>> N;
    vll pa(N);
    vll pb(N);
    for(int i=0;i<N;i++) cin>>pa[i]>>pb[i];
    if(N < 4) {
        cout << 0 << '\n';
        return 0;
    }
    ll ans = N*(N-1)*(N-2)*(N-3);
    ans = ans/ll(4*3*2*1);

    ll tres = 0;
    ll cuat = 0;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            ll tt = 0;
            for(int k=j+1;k<N;k++){
                //double ij = dis(pa[i], pb[i], pa[j], pb[j]);
                //double jk = dis(pa[j], pb[j], pa[k], pb[k]);
                //double ik = dis(pa[i], pb[i], pa[k], pb[k]);


                //ll aaaa = pa[i]*(pb[j]-pb[k]) + pa[j]*(pb[k]-pb[i])+pa[k]*(pb[i]-pb[j]);
                ll x = pa[j] - pa[i];
                ll y = pb[j] - pb[i];

                ll a = pa[k] - pa[i];
                ll b = pb[k] - pb[i];

                ll aaaa = x*b - a*y;

                
                if(aaaa == 0){
                    //cout << i << ' ' << j << ' ' << k << endl;
                    //cout << ij << ' ' << ik << ' ' << jk << endl;
                    tres++;
                    tt++;
                }
            }
            cuat = cuat + ((tt)*(tt-1))/2;
        }
    }
    //cout << tres << endl;
    tres = tres * (N-3);
    cuat *= 3;
    //cout << ans << endl;
    //cout << tres << endl;
    //cout << cuat << endl;
    cout << ans - tres + cuat << '\n';
}


