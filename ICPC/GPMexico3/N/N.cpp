#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vll A(2*N);
    vll B(2*N);
    vll Acum(2*N);
    for(int i = 0; i < N; i++) cin>>A[i];
    for(int i = 0; i < N; i++) cin>>B[i];
    ll K, L; cin >> K >> L;
    for(int i = 0; i < N; i++) A[i+N] = A[i];
    for(int i = 0; i < N; i++) B[i+N] = B[i];
    Acum[0] = A[0];
    for(int i = 1; i < 2*N; i++) Acum[i] = A[i] + Acum[i-1];

    auto ASum = [&](ll i, ll j){
        ll toRet = Acum[j];
        if(i > 0) toRet-=Acum[i-1];
        return toRet;
    };
    ll ans = 1e15;
    ans *= -1;

    set<pll> inSum;
    set<pll> outSum;
    ll sum = 0;
    for(int i = N-K; i < N; i++){
        sum+=B[i];
        inSum.insert(pll(B[i],i));
    }
    for(int i = K; i > L; i--){
        ll c = inSum.begin()->first;
        outSum.insert(*inSum.begin());
        inSum.erase(inSum.begin());
        sum-=c;
    }

    for(int i = N-K; i+K <= N+K; i++){
        if(i != N-K){
            pll p(B[i-1], i-1);
            if(inSum.find(p) != inSum.end()){
                sum-=p.first;
            }

            inSum.erase(p);
            pll n(B[i+K-1], i+K-1);
            outSum.insert(n);
            while(true){
                ll ind = outSum.rbegin()->second;
                ll cc = outSum.rbegin()->first;
                outSum.erase(pll(cc,ind));
                if(ind >= i){
                    sum+=cc;
                    inSum.insert(pll(cc,ind));
                    break;
                }
            }

            while(inSum.size() > size_t(L)){
                auto kek = *inSum.begin();
                inSum.erase(inSum.begin());
                outSum.insert(kek);
                sum-= kek.first;
            }

        }
        ans = max(ans, sum+ASum(i, i+K-1));
    }
    cout << ans << '\n';
}
