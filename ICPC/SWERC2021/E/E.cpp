#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

string getStr(string& a){
    string st;
    for(char x: a){
        if(x == 'B') continue;
        st.push_back(x);
    }
    return st;
}

bool reduce(string& a){
    string ans=a;
    a.clear();
    for(size_t i=0; i<ans.size(); i++){
        if(i < ans.size()-1 && ans[i] == ans[i+1]){
            i++;
            continue;
        }
        a.push_back(ans[i]);
    }
    if(a == ans) return false;
    return true;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        string a,b;
        cin>>a>>b;
        ll ca=0;
        ll cb=0;
        for(char x: a){
            if(x == 'B') ca++;
        }
        for(char x: b){
            if(x == 'B') cb++;
        }
        if(ca%2 != cb%2) {
            cout << "NO\n";
            continue;
        }
        a = getStr(a);
        b = getStr(b);
        /*
        cout << "STRING A: " << a << endl;
        cout << "STRING B: " << b << endl;
        */
        while(reduce(a)) {}
        while(reduce(b)) {}
        if(a != b) {
            cout << "NO\n"; continue;
        }
        cout << "YES\n"; continue;
    }
}



