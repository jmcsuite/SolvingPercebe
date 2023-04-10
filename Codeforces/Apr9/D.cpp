#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=1000;
ll vl[maxn];

void solve(){
    ll N; cin>>N;
    if(N == 2){
        ll res;
        cout << "! 1 2 2 1" << endl;
        cin>>res;
        return;
    }
        
    vl[0] = 1;
    ll izq = 2;
    ll der = N;
    for(int i=1; i<N; i++){
        if(i%2 == 1){
            vl[i] = izq;
            izq++;
        }else{
            vl[i] = der;
            der--;
        }
    }

    cout << "+ " << N + 2 << endl;
    ll res; cin >>res;
    cout << "+ " << N+3 << endl;
    cin >> res;
    ll one=1;
    ll finalOne = 1;
    for(int i=2; i<=N; i++){
        cout << "? " << 1 << ' ' << i << endl;
        cin >> res;
        if(res == -1 && one != 1) finalOne = 1;
        else if(res == -1){
            finalOne = i;
            one = i;
        }
    }

    vll ans(N,-1);
    ans[finalOne-1]=1;
    cout << "+ 3" << endl;
    cin>> res;
    ll Q = 0;
    set<ll> st;
    for(int i=2; i<=N; i++) st.insert(i);

    for(int i=1; i<=N; i++){
        if(i == finalOne) continue;
        cout << "? " << finalOne << ' ' << i << endl;
        cin >> res;
        ans[i-1] = vl[res];
        st.erase(vl[res]);
        Q++;
        if(Q == N-2) break;
    }

    cout << "! ";
    for(int i=0; i<N; i++){
        if(ans[i] == -1) cout << *st.rbegin() << ' ';
        else cout << ans[i] << ' ';
    }
    for(int i=0; i<N; i++){
        if(ans[i] == -1) cout << *st.begin() << ' ';
        else cout << ans[i] << ' ';
    }
    cout << endl;
    cin >> res;
}


        




int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        solve();
    }
}
