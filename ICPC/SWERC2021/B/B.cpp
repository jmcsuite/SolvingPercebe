#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1500;

ll row[maxn];
ll col[maxn];

ll r2[maxn];
ll c2[maxn];

ll rowMatrix[maxn][maxn];
ll colMatrix[maxn][maxn];
ll ans=0;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vector<pair<ll,pll>> vp(N*N);
    ll idx=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>vp[idx].first;
            vp[idx].second.first=i;
            vp[idx].second.second=j;
            idx++;
        }
    }

    sort(vp.rbegin(),vp.rend());

    //cout << "FIRST FOR" << endl;
    for(pair<ll,pll> xx: vp){
        ll i=xx.second.first;
        ll j=xx.second.second;
        //cout << i << ' ' << j << endl;
        rowMatrix[i][j]=row[i];
        colMatrix[i][j]=col[j];
        row[i]++;
        col[j]++;
    }
    //cout << "FIN" << endl;

    //cout << "MAYORES EN MI ROW" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            //cout << rowMatrix[i][j] << ' ';
        }
        //cout << endl;
    }
    //cout << "FIN" << endl;
    /*
    cout << "MAYORES EN MI COL" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << colMatrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "FIN" << endl;*/

    for(pair<ll,pll> xx: vp){
        ll i=xx.second.first;
        ll j=xx.second.second;
        ans+=r2[i]; 
        ans+=c2[j];
        c2[j]+=rowMatrix[i][j];
        r2[i]+=colMatrix[i][j];
    }
    cout << ans/2 << '\n';
}



