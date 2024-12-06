#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

vector<string> vs = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

ll query(int name, ll days){
    if(name == 1){
        days-=30;
        if(days<=0) return days;
        name+=2;
        return query(name, days);
    }
    if(name == 2){
        days-=30;
        if(days<=0) return days;
        name+=2;
        return query(name, days);
    }
    if(name == 3){
        days-=32;
        if(days<=0) return days;
        return query(0,days);
    }
    if(name == 4){
        days-=31;
        if(days<=0) return days;
        return query(0, days);
    }
    days%= 91;
    days-=30;
    if(days <=0) return days;
    name+=2;
    return query(name, days);
}

int main(){
    ios::sync_with_stdio(0);
    string A; int B; cin>>A>>B;
    int a = 0;
    for(int i=0; i<7; i++){
        if(vs[i] == A) a = i;
    }
    ll ans = 1e15*-1;
    for(int i=0; i<B; i++){
        ll pp; cin>>pp;
        ll dd = ((((a-pp)%7)+7)%7);
        ans = max(query(dd,pp),ans);
    }
    ans*=-1;
    cout << ans << endl;
}

        

