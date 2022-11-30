#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, P;
    cin >> N >> P;
    vll fac(N+2);
    
    fac[0] = 1;
    for(int i = 1; i < N+2; i++){
        fac[i] = (fac[i-1]*i)%P;
    }

    vector<vll> Pasc;
    Pasc.resize(N+2);
    for(int i = 0; i < N+2 ; i++) Pasc[i].resize(i+2);
    Pasc[0][0] = 1;
    for(int i = 1; i<N+2; i++){
        for(int j = 0; j<=i; j++){
            if(j == 0 || j == i){
                Pasc[i][j] = 1;
                //cout << 1 << ' ';
                continue;
            }
            Pasc[i][j] = (Pasc[i-1][j-1]+Pasc[i-1][j])%P;
            //cout << Pasc[i][j] << ' ';
        }
        //cout << endl;
    }



    ll ans = 0;
    for(int i = 1; i <= N; i++){
        ll aaa = i -1;
        cout << i << ' ' << aaa << ' ' << N << ' ' << N-aaa << endl;
        if(N-aaa < aaa) continue;
        if((i-1)*2 == N) continue;
        ll lit = 0;
        ll big = 0;
        ll X = 0;
        for(int j = 2; j <= N; j++){
            if(((i-1)*2 < N && j > i)){
                big++;
                if((j-i)*2 <= N && (1+N-j)*2 <= N) X++;
            }
            else if((i-1)*2 > N && j < i){
                big++;
                if((j-1)*2 <= N && (i-j)*2 <= N) X++;
            }
            else if(j != i && j != 1){
                lit++;
            }
        }
        cout << 1 << ' ' << i << ' ' << X << ' ' << lit << ' ' << big << endl;
        for(int j = 0; j <= lit; j++){
            ans = (ans + N*(((X*Pasc[lit][j])%P) * fac[big-1+j])%P)%P;
            cout << "j " << j << " " << ((((X*Pasc[lit][j])%P) * fac[big-1+j])%P)%P << endl;
            //cout << Pasc[lit][0] << "PP " << endl;
        }
    } 
    cout << ans << '\n';

}