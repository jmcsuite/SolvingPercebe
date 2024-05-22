#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<pll>;
ll N,M;
int check(ll a, ll b){
    if(a == 0) return 0;
    if(b == M) return 1;
    if(a == N) return 2;
    if(b == 0) return 3;
    return -1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    ll Q; cin>>Q;
    vll izq, aba, der, up;
    for(int i=0; i<Q; i++){
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        ll aa = check(a,b);
        ll bb = check(c,d);
        if(aa == -1) continue;
        if(bb == -1) continue;
        if(aa == 0) izq.push_back({b,i});
        if(aa == 1) aba.push_back({a,i});
        if(aa == 2) der.push_back({b,i});
        if(aa == 3) up.push_back({a,i});
        if(bb == 0) izq.push_back({d,i});
        if(bb == 1) aba.push_back({c,i});
        if(bb == 2) der.push_back({d,i});
        if(bb == 3) up.push_back({c,i});
    }
    stack<ll> st;
    sort(izq.begin(),izq.end());
    sort(aba.begin(), aba.end());
    sort(der.rbegin(), der.rend());
    sort(up.rbegin(), up.rend());
    for(int i=0; i<izq.size(); i++){
        ll x = izq[i].second;
        if(!st.empty() && (st.top() == x)) st.pop();
        else st.push(x);
    }
    for(int i=0; i<aba.size(); i++){
        ll x = aba[i].second;
        if(!st.empty() && (st.top() == x)) st.pop();
        else st.push(x);
    }
    for(int i=0; i<der.size(); i++){
        ll x = der[i].second;
        if(!st.empty() && (st.top() == x)) st.pop();
        else st.push(x);
    }
    for(int i=0; i<up.size(); i++){
        ll x = up[i].second;
        if(!st.empty() && (st.top() == x)) st.pop();
        else st.push(x);
    }
    if(st.empty()) cout << "Y" << endl;
    else cout << "N" << endl;
}
