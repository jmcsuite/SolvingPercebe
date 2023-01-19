#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

vector<int> KMP(string& s){
    int n = s.size();
    vector<int> vs(n);
    
    for(int i=1; i<n; i++){
        int j = vs[i-1];
        while(j!=0 && s[i] != s[j]){
            j = vs[j-1];
        }
        if(s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}

int main(){
    ios::sync_with_stdio(0);
    string t;
    string p;
    getline(cin, t);
    getline(cin, p);
    ll k; cin>>k;
    string imp = "#";
    imp[0] = 1;
    string pt = p+imp+t;
    ll N = pt.size();
    vll ans(N+1);
    auto kmp = KMP(pt); 

    for(int i=N-1,j=0; j<t.size(); i--,j++){
        if(kmp[i] == 0) continue;
        ans[kmp[i]-1]++;
    }

    for(int i=p.size()-1; i>=0;i--){
        if(kmp[i] == 0) continue;
        ans[kmp[i]-1] += ans[i];
    }


    string aans = "IMPOSSIBLE";
    for(int i=p.size()-1; i>=0; i--){
        if(ans[i] >= k){
            for(int j=0;j<=i;j++) cout <<p[j];
            cout << '\n';
            return 0;
        }
    }
    cout <<aans << '\n';
}
