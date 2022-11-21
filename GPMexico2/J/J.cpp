#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll M;
ll N;
vll vl;
vll ans;
ll C = 0;

void BACK(ll x, ll cant){
    //cout << x << endl;
    //cout << N << endl;
    //if(x == N) return;
    if(x == cant){
        C++;
        return;
    }

    //cout << N << endl;
    for(int i = 0; i<'z'-'a'+1; i++){
        //cout << i << endl;
        //cout << i << ' ' << vl[i] << endl;
        if(vl[i] == 0) continue;
        
        ans[x] = i;
        vl[i]--;
        if(C == M) return;
        BACK(x+1, cant);
        if(C == M) return;
        vl[i]++; 
        ans[x] = -1;
    }
}



int main(){
    
    cin >> N >> M;
    vl.resize('z'-'a'+1);
    for(int i = 0; i<N; i++) {
        char a; cin >> a;
        vl[a-'a']++;
        //cout << vl[a-'a'] << endl;
    }
    ans.resize(N);
    for(int i = 0; i<N; i++) ans[i] = -1;
    for(int i = 1; i<=N; i++){
        //cout << i << ' ' << C << ' ' << vl[0] << endl;
        BACK(0, i);
        
        if(M == C) break;
    }
    //scout << C << endl;
    for(int i = 0; i<N; i++) {
        if(ans[i] == -1) break;
        cout << char(ans[i] + 'a');
    }
    cout << endl; 
}