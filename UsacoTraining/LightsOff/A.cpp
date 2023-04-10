#include<bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=1048577;
const int maxm = 40;


ll nums[maxn];
ll mp[maxn];
bool DP[maxn][41];

ll fromString(string& a){
    ll ans = 0;
    for(char x: a){
        ans *= 2;
        ans+= int(x)-'0';
    }
    return ans;
}
ll mBit;
ll N;

ll rotate(ll x){
    ll nex=x/2;
    if(x%2) nex+= mBit;

    //cout << "ROTATION: " << x << ' ' << nex << ' ' << mBit << endl;
    return nex;
}

ll rotateInv(ll x){
    if((x & (mBit) ) == 0) return x*2;
    return ((x-mBit)*2 + 1);
}


ll getXor(ll x, ll bit){
    ll pos = N-1-bit;
    return ( x ^ ( ll(1) << pos));
}

ll apply(ll x, string& st){
   ll bb = mBit;
   for(char c: st){
       if(c == '1') x = (x ^ bb);
       bb/=2;
   }
   return x;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin>>Q>>N;
    mBit = (ll(1) << (N-1));

    ll NN = (ll(1) << N);
    mp[0] = 0;
    nums[0] = 0;
    ll cant=0;
    cant++;

    // Get unique numbers
    for(ll i=0; i<NN; i++){
        bool se = true;
        ll x = i;
        for(int j=0; j<N; j++){
            if(mp[x] == x){
                se = false;
                mp[i] = x;
                break;
            }
            x = rotate(x);
        }
        if(se){
            mp[i] = i;
            nums[cant] = i;
            cant++;
        }
    }

    /* cout CANT
    for(int i=0; i<cant; i++) cout <<nums[i] << ' ';
    cout << endl;*/
    

    // Fill DP // FALTA HACER QUE SI NO ESTA EN MP, NO PROPAGARLO
    DP[0][0]=1;
    ll maxiM = N+1;

    // INICIO
    //cout << "inicio " << DP[2][3] << endl;
    for(int j=0; j<maxiM; j++){
        for(int i=0; i<cant; i++){
            //cout << "ll prev X: " << nums[i] << endl;
            ll x=nums[i];
            if(!DP[x][j]) continue;
            //if(GEN[x][j%3]) continue;
            //GEN[x][j%3] =1;
            for(int k=0; k<j+1; k++){
                x = getXor(x,k%N);
            }
            ll izq=0;
            ll der=j+1; der%=N;
            
            for(int k=0; k<N; k++){
                //cout << "x: " << x << " j: " << j << " mp: " << mp[x] << endl;
                DP[mp[x]][j+1]=1;
                x = getXor(x, izq);
                x = getXor(x, der);
                izq++; izq%=N;
                der++; der%=N;
            }
        }
    }
    /*
    cout << "fin" << DP[2][3] << endl;
    //cout << "Battle of mp" << endl;
    //cout << rotate(3) << endl;
    //cout << mp[5] << ' ' << mp[3] << endl;
    for(int i=0; i<8; i++) cout << i << ' ' << mp[i] << endl;
    for(int i=0; i<8; i++){
        for(int k=0; k<=6; k++){
            cout << DP[i][k] << ' ' << i << k << endl;;
        }
        cout << endl;
    }
    cout << "ULRA FIN" << DP[2][3] << endl; */

    for(int i=0; i<Q; i++){
        string a,b;
        cin>>a>>b;
        ll xa = fromString(a);
        ll xd = fromString(b);
        bool se = false;
        ll xc = xa;
        if(xa == 0){
            cout << 0 << '\n';
            continue;
        }
        //cout << "XC: " << xc << ' ' << DP[0][0] << ' ' << mp[0] << endl;
        //cout << "TEST CASE: " << endl;
        for(int k=0; k<=maxiM; k++){
            ll xb = xc;
                //cout << xb << ' ' << k << endl;
            if(DP[mp[xb]][k]) se=true;
            if(se){ 
                cout << k << '\n';
                break;
            }
            xc = (xc^xd);
            //cout << xc << endl;
            xc = rotateInv(xc);
            //cout << xc << endl;
        }
    }
}
