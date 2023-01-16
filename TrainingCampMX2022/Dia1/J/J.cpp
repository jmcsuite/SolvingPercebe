#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

int main(){
    ll N,H;
    cin>>N>>H;
    vpll vl(N);
    for(int i = 0; i < N; i++) cin>>vl[i].first;
    for(int i = 0; i < N; i++) vl[i].second = i;
    sort(vl.begin(),vl.end());
    if(N<=2){
        cout << 0 << endl;
        cout << 1 << ' ' << 1 << endl;
        return 0;
    }
    ll allsame = (vl[N-1].first+vl[N-2].first)-(vl[0].first+vl[1].first);
    ll diff = max((vl[N-1].first+vl[0].first+H),vl[N-1].first+vl[N-2].first)-min(vl[1].first+vl[2].first,vl[1].first+vl[0].first+H);
    diff = max(diff, -1*diff);
    vl[0].first = -1;
    for(int i = 0; i < N; i++) swap(vl[i].first,vl[i].second);
    sort(vl.begin(),vl.end());
    if(allsame < diff){
        cout << allsame << '\n';
        for(int i = 0; i < N; i++) cout << 1 << (i==N-1 ? '\n' : ' ');
        return 0;
    }
    cout << diff << '\n';
    for(int i = 0; i < N; i++) cout << (vl[i].second == -1 ? 2 : 1) << (i==N-1 ? '\n' : ' ');
}
    
            
