#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using vadj = vector<vector<ll>>;

int dx[4] = { -1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
ll N, M;

ll comp_count = 0;
void DFS(int i, int j, vadj& adj, vadj& cc, int c) {
    if(cc[i][j] != -1) return;
    comp_count++;
    cc[i][j] = c;
    for (int k = 0; k < 4; k++) {
        ll ni = i + dx[k];
        ll nj = j + dy[k];
        if (ni < 0 || ni == N) continue;
        if (nj < 0 || nj == M) continue;
        if (!adj[ni][nj]) continue;
        DFS(ni, nj, adj, cc, c);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N >> M;
        vadj adj(N, vector<ll>(M));
        vadj cc(N, vector<ll>(M, -1));
        vector<ll> gross(N*M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char a; cin >> a;
                adj[i][j] = (a == '#' ? 1 : 0);
            }
        }
        ll c = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (cc[i][j] != -1) continue;
                if (adj[i][j] == 0) continue;
                comp_count = 0;
                DFS(i,j,adj,cc,c);
                gross[c] = comp_count;
                c++;
            }
        }
        ll ans = 0;

        /*
        cout << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                //cout << (cc[i][j] != -1 ? gross[cc[i][j]] : 0)  << ' ';
                cout << cc[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << endl;
        */

        for (int i = 0; i < N; i++) {
            ll sum = 0;
            set<ll> st;
            for (int j = 0; j < M; j++) {
                if (i > 0 && adj[i-1][j]) st.insert(cc[i-1][j]);
                if (i+1 < N && adj[i+1][j]) st.insert(cc[i+1][j]);
                if (adj[i][j]) st.insert(cc[i][j]);
                if (!adj[i][j]) sum++;
            }
            for (auto x : st) sum += gross[x];
            ans = max(ans, sum);
        }


        for (int j = 0; j < M; j++) {
            ll sum = 0; set<ll> st;
            for (int i = 0; i < N; i++) {
                if (j > 0 && adj[i][j-1]) st.insert(cc[i][j-1]);
                if (j + 1 < M && adj[i][j+1]) st.insert(cc[i][j+1]);
                if (adj[i][j]) st.insert(cc[i][j]);
                if (!adj[i][j]) sum++;
            }
            for (auto x : st) sum += gross[x];
            ans = max(ans, sum);
        }

        cout << ans << '\n';
    }
}
