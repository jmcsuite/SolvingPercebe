#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    stack<pll> st;
    vll izq(N);
    vll der(N);
    st.push({1e16,-1});
    for(int i=0; i<N; i++){
        while(st.top().first <= vl[i]) st.pop();
        if(i == 1){
            cout << "HARD " << st.top().first << endl;
            cout << vl[i] << endl;
        }
        izq[i] = st.top().second;
        st.push({vl[i],i});
    }
    while(!st.empty()) st.pop();
    st.push({1e16, N});
    for(int i=N-1; i>=0; i--){
        while(st.top().first <= vl[i]) st.pop();
        der[i] = st.top().second;
        st.push({vl[i],i});
    }

    vll sumIzq(N);
    vll sumDer(N);
    for(int i=0; i<N; i++){
        ll dis = i-izq[i]+1;
        if(der[i] == -1){ sumIzq[0]++; }
        else{

            sumIzq[i-dis+1]++;
        }
        if(i < N-1) sumIzq[i+1]--;
    }

    for(int i=N-1; i>=0; i--){
        ll dis = der[i]-i+1;
        cout << dis << endl;
        cout << izq[i] << endl;
        cout << "NEX" << endl;
        dis/=2;
        if(izq[i] == N){ sumDer[N-1]++;}
        else
        { 
            sumDer[i+dis-1]++;

        }
        if(i > 0){
            sumDer[i-1]--;
        }
    }

    for(int i=1; i<N; i++) sumIzq[i] += sumIzq[i-1];
    for(int i=N-2; i>=0; i--) sumDer[i] += sumDer[i+1];
    for(int i=0; i<N; i++){
        cout << sumIzq[i]+sumDer[i] << ((i == N-1) ? '\n' : ' ') ;
    }
}



    
