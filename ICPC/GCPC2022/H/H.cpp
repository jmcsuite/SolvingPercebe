#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=10000;
char ans[maxn];
ll qs[3][3][maxn];


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll maxi=0;


    for(int i=0; i<2; i++){
        for(int j=9; j>0; j/=3){
            ll idx=2;
            if(j == 3) idx=1;
            if(j == 1) idx=0;
           
            string q;
            for(int z = 0; z< 9/j; z++){
                for(int k=0; k<j; k++){
                    q.push_back(char(k+3*j*z +i*j + 'a'));
                }
            }
            cout << "? " << q << endl;
            ll M; cin>>M;
            for(int kk = 0; kk<M; kk++){
                ll aa; cin>>aa;
                aa--;
                maxi=max(aa+1,maxi);
                qs[i][idx][aa] = 1;
            }
        }
    }

    for(int j=0; j<3; j++){
        for(int i=0; i<maxi; i++) qs[2][j][i] = 1;
        for(int kk =0; kk<2; kk++){
            for(int i=0; i<maxi; i++){
                if(qs[kk][j][i] == 1) qs[2][j][i] = 0;
            }
        }
    }


    for(int i=0; i<26; i++){
        ll idx0 = i%3;
        ll idx1 = (i/3)%3;
        ll idx2 = (i/9)%3;
        for(int j=0; j<maxi; j++){
            if(qs[idx0][0][j] == 1 && qs[idx1][1][j] == 1 && qs[idx2][2][j] == 1) ans[j] = char(i + 'a');
        }
    }

    cout << "! ";
    for(int i=0; i<maxi; i++){ 
        cout << ans[i];
    }
    cout << endl;

}

