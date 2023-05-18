#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=5001;

ll vl[maxn];
ll pr[maxn];


ll memLim[maxn][maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    pr[0]=-1;
    for(int i=1; i<maxn; i++) pr[i]=1;
    for(int i=1; i<maxn; i++) memLim[i][i]=1;

    for(int k=maxn; k>=1; k--){
        ll j=0;
        for(int i=0; i<maxn; i++){
            while(((i-j) > k || (pr[j] == 1)) && (j<i)) j++;
            if(j==i) vl[i]=-1;
            else vl[i]=1;
        }
        /*cout << "Case: " << k << endl;
        for(int i=0; i<maxn; i++) cout << vl[i] << ' ';
        cout << endl;*/
        swap(vl,pr);
    }

    ll N; cin>>N;
    cout << (pr[N]  == 1 ? "Jane" : "John")<< '\n';
}
