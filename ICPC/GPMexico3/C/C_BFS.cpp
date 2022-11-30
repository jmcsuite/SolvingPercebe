#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1e3 + 2;
int ver[maxn][maxn];
int hor[maxn][maxn];

void UP(pll A, pll B){
    if(A.first == B.first){
        ll ini = min(A.second, B.second);
        ll fin = max(A.second, B.second);
        hor[A.first][ini]++;
        hor[A.first][fin]--;
        //cout << A.first << ' ' << ini << ' ' << fin << endl;
        return;
    }
    ll ini = min(A.first, B.first);
    ll fin = max(A.first, B.first);
    ver[ini][A.second]++;
    ver[fin][A.second]--;
}

int dx[4] = {-1, 0, 1, 0}; // up, right, down, left
int dy[4] = {0, 1, 0, -1};

int vis[maxn][maxn];

bool Valid(ll x, ll y, ll dx, ll dy, ll in){
    if(dx < 0 || dx >= maxn || dy < 0 || dy >= maxn) return false;
    if(vis[dx][dy] != 0) return false;
    if(in == 0) return (hor[x][y] == 0);
    if(in == 3) return (ver[x][y] == 0);
    if(in == 2) return (hor[x+1][y] == 0);
    if(in == 1) return (ver[x][y+1] == 0);
    return false;
}

ll ans = 0;
ll thisAns = 0;
void DFS(ll i, ll j, ll x){
    if(vis[i][j] != 0) return; 
    queue<pll> q;
    q.push(pll(i,j));
    while(!q.empty()){
        auto pp = q.front();
        q.pop();
        i = pp.first;
        j = pp.second;
    //cout << i << ' ' << j << endl;
    //cout << thisAns << endl;
        vis[i][j] = x;
        thisAns++;
        ans = max(ans, thisAns);
        for(int k = 0; k < 4; k++){
            ll di = i + dx[k];
            ll dj = j + dy[k];
            if(Valid(i, j, di, dj, k)){ 
                q.push(pll(di,dj));
                vis[di][dj] = x;
            }
        }
    }
}
    


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    pll ini;
    pll prev;
    cin >> ini.first >> ini.second;
    prev.first = ini.first;
    prev.second = ini.second;

    for(int i = 0; i < N; i++){
        pll aa;
        cin >> aa.first >> aa.second;
        UP(prev, aa);
        prev.first = aa.first;
        prev.second = aa.second;
    }
    UP(prev, ini);
    for(int j = 0; j < maxn; j++){
        for(int i = 1; i < maxn; i++) hor[j][i]+=hor[j][i-1];
        for(int i = 1; i < maxn; i++) ver[i][j] += ver[i-1][j];
    }
    
    for(int i = 0; i < maxn; i++){
        for(int j = 0; j < maxn; j++){
            thisAns = 0;
            //cout << i << ' ' << j << endl;
            if(vis[i][j] == 0) DFS(i, j, 1);
            if(i == 0 && j == 0) ans = 0;
        }
    }

  
    //DFS(1, 1, 1);

    cout << ans << '\n';
}
