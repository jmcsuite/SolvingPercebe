#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N, X;
        cin >> N >> X;
        if(N%X != 0) {
            cout << -1 << '\n';
            continue;
        }
        queue<int> q;
        for(int i = 2; i <= N; i++){
            if(i == X) continue;
            if(N%i == 0) q.push(i);
        }

        cout << X << ' ';
        ll prev = X;
        for(int i = 2; i < N; i++){
            if(i == prev){
                ll a = q.front();
                q.pop();
                if(a%i == 0){
                    cout << a << ' ';
                    prev = a;
                    continue;
                }
                i--;
                continue;
            }
            cout << i << ' ';
            continue;
        }
        cout << 1 << '\n';
    }
}
            