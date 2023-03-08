#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

string s;
ll N,T;
bool div2(){
    N = s.size();
    int a = s[N-1]-'0';
    if(a%2 == 0) return true;
    return false;
}

bool div3(){
    int ans = 0;
    N = s.size();
    for(int i=0; i<N; i++){
        ans += s[i]-'0';
    }
    if(ans%3 == 0) return true;
    return false;
}

bool div4(){
    int ans = 0;
    N = s.size();
    ans = s[N-1]-'0';
    if(N>1){
        ans += 10*(s[N-2]-'0');
    }
    if(ans%4 == 0) return true;
    return false;
}

bool div5(){
    int ans = 0;
    N = s.size();
    if(s[N-1] == '0') return true;
    if(s[N-1] == '5') return true;
    return false;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>T;
    while(T--){
        cin>>s;
        vll ans;
        if(div2()) ans.push_back(2);
        if(div3()) ans.push_back(3);
        if(div4()) ans.push_back(4);
        if(div5()) ans.push_back(5);
        if(div3() && div2()) ans.push_back(6);
        if(ans.size() == 0) cout<<-1<<'\n';
        else{
            for(int i=0; i<ans.size(); i++){
                cout << ans[i] << (i == ans.size()-1 ? '\n' : ' ');
            }
        }
    }
}
