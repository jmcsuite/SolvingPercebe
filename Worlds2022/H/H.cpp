#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;

ll A,B,C,D,N,M,Q;

bool func(pair<pll,ll> A, pair<pll,ll> B){
    return (A.first.first + A.first.second > B.first.first + B.first.second);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    vpll input(N);
    for(ll k = 0; k < N; k++){
        string s;
        cin >> s;
        ll bal = 0;
        ll mini = 0;
        for(ll i = 0; i < s.size(); i++){
            bal += (s[i] == '(' ? 1 : -1);
            mini = min(mini, bal);
        }
        input[k].first = mini*-1;
        input[k].second = bal;
    }

    vector<pair<pll,ll>> positiveBalance;
    vector<pair<pll,ll>> negativeBalance;
    ll S = 0;
    for(ll k = 0; k < N; k++){
        if(input[k].second >= 0) positiveBalance.push_back(pair<pll,ll>(pll(input[k].first, input[k].second), k+1));
        else negativeBalance.push_back(pair<pll,ll>(pll(input[k].first, input[k].second),k+1));
    }

    sort(positiveBalance.begin(), positiveBalance.end());
    
    sort(negativeBalance.begin(), negativeBalance.end(), func);

    vll ans(N);
    ll ii = 0;
    for(ll k = 0; k < positiveBalance.size(); k++){
        if(positiveBalance[k].first.first > S) {
            cout << "impossible\n";
            return 0;
        }
        ans[ii] = positiveBalance[k].second;
        S += positiveBalance[k].first.second;
        ii++;
    }

    for(ll k = 0; k < negativeBalance.size(); k++){
        if(negativeBalance[k].first.first > S) {
            cout << "impossible\n";
            return 0;
        }
        ans[ii] = negativeBalance[k].second;
        S += negativeBalance[k].first.second;
        ii++;
    }

    if(S != 0){
        cout << "impossible\n";
        return 0;
    }
    for(ll i = 0; i < N; i++){
        cout << ans[i] << '\n';
    }

         



}
