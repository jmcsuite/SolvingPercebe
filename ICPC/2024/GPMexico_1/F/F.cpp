#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxs = 4e5;
const int maxn = 2*maxs;

namespace suffix_tree {
    const long long inf = 1e9;
    char s[maxn];
    int to[2*maxn][28];
    int dp[2*maxn];
    int dp2[2*maxn];
    int len[2*maxn], fpos[2*maxn], link[2*maxn];
    int node=0, pos=0;
    int sz=1, n=0;

    int lid=0;
    int leaves[2*maxn];

    void match(ll node, string& c, ll mc) {
        // match
    }

    int make_node(int _pos, int _len) {
        fpos[sz] = _pos;
        len[sz] = _len;
        return sz++;
    }

    void go_edge() {
        while(pos>len[to[node][(int)s[n-pos]]]){
            node = to[node][(int)s[n-pos]];
            pos -= len[node];
        }
    }

    void add_letter(int c) {
        s[n++] = c;
        pos++;
        int last = 0;
        while (pos>0) {
            go_edge();
            int edge = s[n-pos];
            int &v = to[node][edge];
            int t = s[fpos[v] + pos - 1];
            if (v == 0) {
                v = make_node(n-pos, inf);
                link[last]=node;
                leaves[lid++]=v;
                last = 0;
            }
            else if (t == c) {
                link[last]=node;
                return;
            }
            else {
                int u = make_node(fpos[v], pos-1);
                to[u][c] = make_node(n-1, inf);
                leaves[lid++]=to[u][c];
                to[u][t] = v;
                fpos[v] += pos-1;
                len[v] -= pos-1;
                v=u;
                link[last] = u;
                last = u;
            }
            if (node == 0) pos--;
            else node=link[node];
        }
    }

    void add_string(string& x, ll b) {
        ll i=n;
        node=0; pos=0;
        len[0]=inf;
        for(char c: x) add_letter(c);
        for(int j=i; j<n; j++) len[leaves[j]] = n-fpos[leaves[j]];
        if (b) {
            for(int j=0; j<(int)x.size()/2; j++) dp[leaves[i+j]] = 1;
        }
        else {
            for(int j=0; j<(int)x.size()/2; j++) dp2[leaves[i+j]] = 1;
        }
        len[0] = 0;
    }

    void prop_dp(ll x, ll M, ll l) {
        l += len[x];
        for (int i = 0; i < 28; i++) {
            if (!to[x][i]) continue;
            int y = to[x][i];
            prop_dp(y, M, l);
            if (l >= M) {
                dp[x] += dp[y];
                dp[y] = 0;
            }
        }
    }

    ll ans = 0;
    ll solve(ll x, ll cc) {
        //cout << "Enter: " << x << ' ' << cc << ' ' << dp2[x] << endl;
        cc += dp2[x];
        for(int i = 0; i < 28; i++) {
            if (!to[x][i]) continue;
            //cout << "Edge: " << i << ' ' << char(i+'a') << endl;
            cc = solve(to[x][i], cc);
        }
        ans += cc*dp[x];
        //cout << "Exit: " << x << ' ' << cc << endl;
        return cc;
    }

    void Debug(ll x) {
        cout << "Enter: " << x << ' ' << len[x] << endl;
        for(int i = 0; i < 28; i++) {
            if (!to[x][i]) continue;
            cout << "Edge: " << i << ' ' << char(i+'a') << endl;
            Debug(to[x][i]);
        }
        cout << "Exit" << endl;
    }

    void DebugAll() {
        for (int i = 0; i < 18; i++) {
            cout << i << ": " << dp[i] << endl;
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M; cin >> M;
    string a, b; cin >> a >> b;
    for(int i = 0; i < M; i++) a[i]-='a';
    for(int i = 0; i < M; i++) b[i]-='a';
    for(int i = 0; i < M-1; i++) a.push_back(a[i]);
    for(int i = 0; i < M-1; i++) b.push_back(b[i]);

    a.push_back('z'+1-'a');
    b.push_back('z'+2-'a');
    suffix_tree::add_string(b, 1);
    suffix_tree::add_string(a, 0);
    suffix_tree::prop_dp(0, M, 0);
    //suffix_tree::Debug(0);
    //suffix_tree::DebugAll();
    suffix_tree::solve(0, 0);
    cout << suffix_tree::ans << '\n';
}
