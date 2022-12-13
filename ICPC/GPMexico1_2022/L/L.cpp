#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
ll mod = 1e9+7;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N; cin>>N;
    vll input(N+10);
    // set<pll> st;
    for(int i = 3; i < N+3; i++){
        ll a; cin >> a;
        input[i] = a;
        //st.insert(pll(a,i));
    }

    vll izq(N+10);
    vll der(N+10);
    stack<int> st;
    for(int i = 3; i < N+3; i++){
        while(!st.empty() && input[st.top()] <= input[i]) st.pop();
        if(st.empty()) izq[i] = 3;
        else izq[i] = st.top() + 1;
        st.push(i);
    }

    while(!st.empty()) st.pop();
    for(int i = N+2; i >= 3; i-- ){
        while(!st.empty() && input[st.top()] <= input[i]) st.pop();
        if(st.empty()) der[i] = N+2;
        else der[i] = st.top()-1;
        st.push(i);
    }



    //auto it = st.rbegin();

    //unordered_set<long long> unset;
    //set<long long> mayores;
    //int prev = 0;
    
    //mayores.insert(N+3);
    //mayores.insert(2);
    /*
    while(it != st.rend()){
        pll x = *it;
        it++;

        int val = x.first;
        int index = x.second;

        if(prev != val){
            auto itUnset = unset.begin();
            while(itUnset != unset.end()){
                mayores.insert(*itUnset);
                itUnset++;
            }
            unset.clear();
        }

        auto search = mayores.lower_bound(index);
        int dd = *search;
        search--;
        int ii = *search;
        izq[index] = ii+1;
        der[index] = dd -1;

       
        
    
        
        unset.insert(index);
        prev = val;
    }*/
    

    vll ansIzq(N+10);
    vll ansDer(N+10);

    for(int i = 3; i < N+3; i++){
        ll disToDer = der[i]-i+1;
        ll disToIzq = i - izq[i] + 1;
        ansIzq[izq[i]] += disToDer;
        ansIzq[izq[i]] %= mod;
        ansIzq[i+1] -= (disToIzq+1)*disToDer;
        ansIzq[i+1] %= mod;
        ansIzq[i+2] += (disToIzq)*disToDer;
        ansIzq[i+2] %= mod;

        ansDer[der[i]] += disToIzq;
        ansDer[der[i]] %= mod;
        ansDer[i] -= (disToIzq)*disToDer;
        ansDer[i] %= mod;
        ansDer[i-1] += (disToIzq)*(disToDer-1);
        ansDer[i-1] %= mod;
    }


    for(int i = 3; i < N+3; i++){
        
        ansIzq[i] = (ansIzq[i] + ansIzq[i-1])%mod;
    }
    
    for(int i = 3; i < N+3; i++){
        ansIzq[i] = (ansIzq[i] + ansIzq[i-1])%mod;
        
    }
    

    


    for(int i = N+2; i >= 3; i--){
        ansDer[i] = (ansDer[i] + ansDer[i+1])%mod;
    }

    for(int i = N+2; i >= 3; i--){
        ansDer[i] = (ansDer[i] + ansDer[i+1])%mod;
    }

    



    ll ans = 0;
    for(int i = 3; i < N+3; i++) ans = (ans+((ansDer[i]+ansIzq[i])%mod *input[i])%mod)%mod;
    cout << (ans+mod)%mod << '\n';
}

