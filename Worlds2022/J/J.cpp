#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll N,M,A,Q;


// si vengo de split multiplico *2 o *2 + 1

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M >> Q;
    ll d = 1e5;
    
    vll pa(d+10, -1);
    vll pb(d+10, -1);
    vll ha(d+10, -1);
    vll hb(d+10, -1);
    vll si(d+10);

    si[1] = N;
    for(int i = 0; i < M; i++){
        char aa; int a, b,c;
        cin >>aa >> a >> b >> c;
       
        if(aa == 'S') {
            pa[b] = a;
            pb[c] = a;
            ha[a] = b;
            hb[a] = c;
            //si[b] = (si[a]%2 + si[a])/2;
            //si[c] = si[a]/2;
        }
        else {
            //si[c] = si[a] + si[b];
            pa[c] = a;
            pb[c] = b;
            ha[a] = c;
            ha[b] = c;
        }
    }

    for(int i = 1; i < d + 10; i++){
        if(ha[i] == -1) continue;
        if(hb[i] == -1){
            si[ha[i]] += si[i];
        }else{
            si[ha[i]] = (si[i]%2 + si[i])/2;
            si[hb[i]] = si[i]/2;
        }
    }
    
    while(Q--){
        ll a, k;
        cin >> a >> k;
        while(a != 0){
            
            if(k > si[a]){
                cout << "none\n";
                break;
            }
            if(a == 1){
                cout << k << '\n';
                break;
            }
            if(pb[a] == -1){
                k = k*2 - 1;
                a = pa[a];
            }
            else if(pa[a] == -1){
                k = k*2;
                a = pb[a];
            }
            else{

                if(si[pa[a]] + si[pb[a]] < k){
                    cout << "none\n";
                    break;
                }

                ll nextK = (k + k%2)/2;
                if(k%2 == 1){
                    
                    if(nextK > si[pa[a]]){
                        k = k-si[pa[a]];
                        a = pb[a];
                    }
                    else{
                        if(nextK > si[pb[a]]) k = k - si[pb[a]];
                        else k = nextK;
                        a = pa[a];
                        
                    }
                }else{
                    if(nextK > si[pb[a]]){
                       
                        k = k-si[pb[a]];
                        a = pa[a];
                    }
                    else{
                        
                        if(nextK > si[pa[a]]) k = k - si[pa[a]];
                        else k = nextK;
                        
                        a = pb[a];
                       
                    }
                }
                
            }
        }
    }
}
                        
