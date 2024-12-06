#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=1001;
char ans[maxn];
vll vadj[maxn];
ll vis[maxn];
ll vl[2*maxn];

bool DFS(ll x, ll c) {
    if (vis[x] != 0 && vis[x] != c) return false;
    if (vis[x] != 0) return true;
    vis[x]=c;
    bool pos=true;
    for (ll y: vadj[x]) {
        pos &= DFS(y, (c==1 ? 2 : 1));
    }
    return pos;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<2*N; i++) cin >> vl[i];
    for (int i=0; i<2*N; i++) {
        if (vl[i]<0) continue;
        for (int j=1; j<=N; j++) vis[j]=0;
        for (int j=i+1; vl[i]!=vl[j]*-1; j++) {
            if (vl[j]>0) vis[vl[j]]++;
            else vis[vl[j]*-1]--; 
        }
        for (int j=1; j<=N; j++) {
            if (vis[j]) vadj[vl[i]].push_back(j);
            if (vis[j]) vadj[j].push_back(vl[i]);
        }
    }
    bool pos = true;
    for (int i=1; i<=N; i++) vis[i]=0;
    for (int i=1; i<=N; i++) {
        if (vis[i]!=0) continue;
        pos &= DFS(i, 1);
    }
    if (!pos) {
        cout << "*\n";
        return 0;
    }
    for (int i=1; i<=N; i++) cout << (vis[i]==1 ? 'S' : 'G');
    cout << '\n';
}
