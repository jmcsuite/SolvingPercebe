#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=2e5+1;
string st[maxn];
ll ct[maxn];

const int M=26;
ll sz[maxn][M];
ll last[maxn][M];
ll branch[maxn][M];
const long long maxLL = (ll)1e18+1;

void func(ll c, ll idx, ll carry, ll L, ll R){
    if(carry > R) return;
    if(sz[idx][c] + carry <= L) return;
    if(branch[idx][c] == -1){
        cout << char( last[idx][c]+'a');
        return;
    }
    ll cc = branch[idx][c];
    for(char nex: st[cc]){
        func(nex,cc+1,carry,L,R);
        carry+=sz[cc+1][(int)nex];
        if(carry >= maxLL) carry = maxLL;
    }
}
    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,L,R;
    cout << (ll)1e18+1 << endl;
    cout << ll(1e18+1) << endl;
    cin>>L>>R>>N;
    L--; R--;
    for(int i=0; i<N; i++){
        char c; string s;
        cin>>c>>s;
        for(size_t j=0; j<s.size(); j++) s[j]-='a';
        int a = c-'a';
        ct[i]=a;
        st[i]=s;
    }

    // SIZE
    for(int j=0; j<M; j++) sz[N][j]=1;
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<M; j++) {
            sz[i][j] = sz[i+1][j];
            if(ct[i] == j){
                ll currSz=0;
                for(char c : st[i]){
                    currSz += sz[i+1][(int)c];
                    if(currSz >= maxLL) currSz = maxLL;
                }
                sz[i][j] = currSz;
            }
        }
    }
    // LAST;
    for(int j=0; j<M; j++) last[N][j]=j;
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<M; j++){
            last[i][j]=last[i+1][j];
            if(ct[i] == j){
                last[i][j] = last[i+1][(int)st[i][0]];
            }
        }
    }

    // branch
    for(int j=0; j<M; j++) branch[N][j]=-1;
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<M; j++){
            branch[i][j]=branch[i+1][j];
            if(ct[i] == j && st[i].size() > 1) branch[i][j] = i;
            if(ct[i] == j && st[i].size() == 1) branch[i][j] = branch[i+1][(int)st[i][0]];
        }
    }
    /*

    cout << "SIZE " << endl;
    for(int i=0; i<=N; i++){
        for(int j=0; j<M; j++){
            cout << sz[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "END SIZE" << endl;
    cout << endl;
    cout << "last" << endl;
    for(int i=0; i<=N; i++){
        for(int j=0; j<M; j++){
            cout << last[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "END LAST" << endl;
    cout << endl;
    cout << "BRANCH" << endl;
    for(int i=0; i<=N; i++){
        for(int j=0; j<M-5; j++){
            cout << branch[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "END BRANCH" << endl; */

    func(0,0,0,L,R);
    cout << '\n';
}
