#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int vadj[100][100];
int dp[100][100][1024];

ll N, M;
ll pa, pb;
ll ea, eb;
int ans = 1000000;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1,0,-1, 0};

bool valid(ll i, ll j){
    if(i < 0) return false;
    if( j < 0) return false;
    if(i >= N || j >= M) return false;
    return true;
}

void DFS(ll i, ll j, int x){
    //cout << i <<  ' ' << j << endl;
    if(!valid(i,j)) return;
    x = x | (1 << vadj[i][j]);
    if(i == ea && j == eb) {
        ans = min(ans,  __builtin_popcount(x));
        return;
    }
    if(dp[i][j][x]) return;
    dp[i][j][x] = 1;
    for(int k = 0; k < 4; k++){
        DFS(i+dx[k], j+dy[k], x);
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    cin >> pa >> pb;
    cin >> ea >> eb;
    pa--; pb--;
    ea--; eb--;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> vadj[i][j];
            vadj[i][j]--;
        }
    }
    DFS(pa, pb, 0);
    cout << ans << '\n';
}
