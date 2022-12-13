#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<char,char>;
set<pll> st;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--){
        st.clear();
        ll N; cin>>N;
        string s; cin>>s;
        if(N < 4) {
            cout << "NO\n";
            continue;
        }
        bool ans = false;
        st.insert(pll(s[0],s[1]));
        for(int i = 2; i < N-1; i++){
            if(st.find(pll(s[i],s[i+1])) != st.end()) ans = true;
            st.insert(pll(s[i-1],s[i]));
        }
        cout << (ans ? "YES" : "NO") << '\n';
    }
}

