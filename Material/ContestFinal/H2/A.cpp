#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vadj = vector<vll>;

ll N, M, cc, maxi, mini, maxj, minj;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void DFS(ll x, ll y, vadj& adj, vadj& vis) {
    if (vis[x][y]) return;
    if (adj[x][y] == 0) return;
    vis[x][y] = 1;
    cc++;

    mini = min(mini, x);
    maxi = max(maxi, x);
    minj = min(minj, y);
    maxj = max(maxj, y);

    for (int k = 0; k < 4; k++) {
        ll ni = x + dx[k];
        ll nj = y + dy[k];
        if (ni < 0 || ni >= N) continue;
        if (nj < 0 || nj >= M) continue;
        DFS(ni, nj, adj, vis);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        //cout << "Test: " << endl;
        cin >> N >> M;
        vadj adj(N, vll(M));
        vadj vis(N, vll(M, 0));
        vadj s(N+1, vll(M+1,0));
        vll rows(N, 0);
        vll cols(M, 0);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c; cin >> c;
                adj[i][j] = (c == '#' ? 1 : 0);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (vis[i][j]) continue;
                if (adj[i][j] == 0) continue;
                cc = 0; mini = maxi = i; minj = maxj = j;
                DFS(i, j, adj, vis);

                mini--; minj--; maxi++; maxj++;
                mini = max(0ll, mini); 
                minj = max(0ll, minj);
                rows[mini] += cc;
                cols[minj] += cc;
                maxi = min(N-1, maxi);
                maxj = min(M-1, maxj);

                if (maxi < N-1) rows[maxi+1] -= cc;
                if (maxj < M-1) cols[maxj+1] -= cc;

                s[mini][minj] += cc;
                s[maxi+1][minj] -= cc;
                s[mini][maxj+1] -= cc;
                s[maxi+1][maxj+1] += cc;
                /*if (i == 0 && j == 0) {
                    cout << "PERO: " << endl;
                    cout << mini << ' ' << minj << ' ' << maxi << ' ' << maxj << endl;
                }*/
            }
        }

        for (int i = 1; i < N; i++) rows[i] += rows[i-1];
        for (int j = 1; j < M; j++) cols[j] += cols[j-1];

        /*
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << s[i][j] << ' ';
            }
            cout << endl;
        }*/

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i > 0) s[i][j] += s[i-1][j];
                if (j > 0) s[i][j] += s[i][j-1]; 
                if (i > 0 && j > 0) s[i][j] -= s[i-1][j-1];
            }
        }

        
        for (int i = 0; i < N; i++) {
            ll x = 0;
            for (int j = 0; j < M; j++) if (adj[i][j] == 0) x++;
            rows[i] += x;
        }
        for (int j = 0; j < M; j++) {
            ll x = 0;
            for (int i = 0; i < N; i++) if (adj[i][j] == 0) x++;
            cols[j] += x;
        }

        ll ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll x = rows[i] + cols[j] - s[i][j];
                if (adj[i][j] == 0) x--;
                ans = max(x, ans);
            }
        }
        cout << ans << '\n';
        
        /*
        cout << "Test: \n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll x = rows[i] + cols[j] - s[i][j];
                //if (adj[i][j] == 0) x--;
                cout << x << ' ' << rows[i] << ' ' << cols[j] << ' ' << s[i][j] << endl;
            }
            cout << endl;
        }
        cout << endl;
        */


        /*for (int i = 0; i < N; i++) cout << rows[i] << ' ';
        cout << endl;
        for (int i = 0; i < M; i++) cout << cols[i] << ' ';
        cout << '\n' << endl;*/
        
        /*
        ll ans = 0;
        for (int i = 0; i < N; i++) {
            ll x = rows[i];
            for (int j = 0; j < M; j++) {
                if (adj[i][j] == 0) x++;
            }
            ans = max(ans, x);
        }

        for (int j = 0; j < M; j++) {
            ll x = cols[j];
            for (int i = 0; i < N; i++) {
                if (adj[i][j] == 0) x++;
            }
            ans = max(ans, x);
        }
        cout << ans << '\n';
        */
    }
}
