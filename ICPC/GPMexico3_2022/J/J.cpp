#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<long long>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll sCard = 14;
    vll cards(sCard);
    for(int i = 1; i < sCard; i++) cards[i] = 4;
    
    
    ll N; cin >> N;
    ll John, Mary;
    John = 0; Mary = 0;
    ll a,b; cin >> a >> b;
    cards[a]--; cards[b]--;
    a = min(a,ll(10)); b = min(b,ll(10));
    John = a +b;

    cin >> a >> b;
    cards[a]--; cards[b]--;
    a = min(a,ll(10)); b = min(b,ll(10));
    Mary = a +b;

    for(int i = 0; i<N; i++){
        cin >> a;
        cards[a]--;
        a = min(a, ll(10));
        Mary+=a;
        John+=a;
    }
    //cout << Mary << ' ' << John << endl;
    ll ans = -1;
    for(int i = 1; i<sCard; i++){
        if(cards[i] <= 0) continue;
         ll val = min(i, int(10));
         if(Mary + val == 23 || (Mary + val <= 23 && John + val > 23)){
            ans = i;
            break;
         }
    }
    cout << ans << '\n';
}


