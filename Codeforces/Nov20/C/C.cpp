#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;

void DFS(ll x, unordered_set<ll>& st, vector<vll>& vadj){
    if(st.find(x) != st.end()) return;
    st.insert(x);
    for(int i = 0; i<vadj[x].size(); i++){
        if(st.find(vadj[x][i]) != st.end()) continue;
        //cout << x << ' ' << vadj[x][i] << endl;
        DFS(vadj[x][i], st, vadj);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--){
        ll N; cin>>N;
        vector<vll> vadj(N);
        for(int i = 0; i<N; i++){
            string s; cin >> s;
            for(int j = 0; j<N; j++){
                if(s[j] == '1') vadj[j].push_back(i);
            }
        }

        for(int i=0; i<N;i++){
            unordered_set<ll> st;
            DFS(i,st, vadj);
            auto it = st.begin();
            cout << st.size();
            while(it != st.end()){
                cout << ' ' << (*it) + 1;
                it++;
            }
            cout << '\n';
        }
    }
}