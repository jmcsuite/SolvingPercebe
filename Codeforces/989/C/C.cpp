#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn=1e3;
ll N,M;

const int dx[4] = {1, 0, -1, 0}; //Down, Left, Up, Right
const int dy[4] = {0, -1, 0, 1}; 

map<char,int> mp = {{'D',0}, {'L',1}, {'U',2}, {'R',3}};

char vadj[maxn][maxn];
ll vis[maxn][maxn];

bool check(ll i, ll j) {
    if (i < 0 || i >= N) return false;
    if (j < 0 || j >= M) return false;
    return true;
}

ll DFS(ll x, ll y) {
    if (!check(x,y)) return 2; // oob;
    if (vis[x][y] == 1) return 3; //cycle;
    if (vis[x][y]) return vis[x][y]; // cycle or oob;

    vis[x][y]=1;
    if (vadj[x][y] == '?') {
        ll ans=0;
        for (int k=0; k<4; k++) ans = max(ans, DFS(x+dx[k], y+dy[k]));
        return vis[x][y]=ans;
    }

    ll k=mp[vadj[x][y]];
    return vis[x][y]=DFS(x+dx[k],y+dy[k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) {
        cin>>N>>M;
        for(int i=0; i<N; i++) {
            for (int j=0; j<M; j++) cin>>vadj[i][j];
            for (int j=0; j<M; j++) vis[i][j]=0;
        }

        for (int i=0; i<N; i++) for (int j=0; j<M; j++) DFS(i,j);
        ll ans = 0;
        for (int i=0; i<N; i++){
            for (int j=0; j<M; j++) {
                if (vis[i][j]==3) ans++;
            }
        }
        cout << ans << '\n';
    }
}
