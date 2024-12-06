#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 1e6;
const int m1 = 999999323;
const int m2 = 999999191;

namespace aho{
    vector<string> vs;
    vector<ll> xx;
    vector<ll> yy;
    ll v1[maxn+1];
    ll v2[maxn+1];
    ll smatch[maxn+1];
    ll p[maxn+1];
    ll pchar[maxn+1];
    map<ll,ll> vadj[maxn+1];
    ll nCount=1;
    const long long root=0;

    ll flink[maxn+1];
    ll olink[maxn+1];

    void addString(string& s, ll id, ll x, ll y) {
        ll i = root;
        for (char c: s) {
            if (vadj[i].find(c) != vadj[i].end()) {
                i = vadj[i][c];
                continue;
            }
            ll node = nCount++;
            p[node]=i;
            pchar[node]=c;
            vadj[i][c]=node;
            i=node;
        }
        smatch[i]=id;
        v1[i] = (v1[i] + x)%m1;
        v2[i] = (v2[i] + y)%m2;
    }

    void build() {
        for (int i = 0; i < maxn; i++) smatch[i]=-1;
        pchar[root]=-1;
        ll id=0;
        for(string& s: vs) {
            addString(s, id, xx[id], yy[id]);
            id++;
        }

        queue<ll> q; q.push(root);
        while (!q.empty()) {
            ll x=q.front(); q.pop();
            for(pll yy: vadj[x]) q.push(yy.second);


            ll nx = flink[p[x]];
            ll c = pchar[x];
            while (nx != root && vadj[nx].find(c) == vadj[nx].end()) nx = flink[nx];
            if (vadj[nx].find(c) == vadj[nx].end() || vadj[nx][c] == x) flink[x] = root;
            else flink[x]=vadj[nx][c];

            if(smatch[flink[x]] != -1) olink[x] = flink[x];
            else olink[x] = olink[flink[x]];

            v1[x] = (v1[x] + v1[olink[x]])%m1;
            v2[x] = (v2[x] + v2[olink[x]])%m2;
        }
    }

    void aho(string& T){
        ll x=root;
        ll a = 0;
        ll b = 0;
        for(int c=0; c < (ll)T.size(); c++) {
            while( x != root && vadj[x].find(T[c]) == vadj[x].end()) x = flink[x];
            if (vadj[x].find(T[c]) == vadj[x].end()) continue;
            x = vadj[x][T[c]];
            a = (v1[x] + a)%m1;
            b = (v2[x] + b)%m2;
        }
        if (a == 0 && b == 0) cout << "yes\n";
        else cout << "no\n";
    }
}

ll f[maxn];
ll s1[maxn];
ll s2[maxn];

ll fi(ll x) {
    if (f[x] == x) return x;
    return f[x] = fi(f[x]);
}

void un(ll a, ll b) {
    ll pa = fi(a);
    ll pb = fi(b);
    if (pa == pb) return;
    s1[pa] = (s1[pa] + s1[pb])%m1;
    s2[pa] = (s2[pa] + s2[pb])%m2;
    f[pb] = pa;
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M,Q; cin >> N >> M >> Q;
    string s; 
    getline(cin, s);
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        getline(cin, s);
        aho::vs.push_back(s);
    }

    map<ll,ll> mp1;
    map<ll,ll> mp2;
    for (int i = 0; i < N; i++) {
        f[i] = i;
        mp1[i] = rand();
        s1[i] = mp1[i];

        mp2[i] = rand();
        s2[i] = mp2[i];
    }
    for (int i = 0; i < M; i++) {
        ll a,b; cin >> a >> b;
        a--; b--; un(a,b);
    }
    for (int i = 0; i < N; i++) {
        ll pi = fi(i);
        if (pi == i) aho::xx.push_back(mp1[i] - s1[pi]);
        else aho::xx.push_back(mp1[i]);

        if (pi == i) aho::yy.push_back(mp2[i] - s2[pi]);
        else aho::yy.push_back(mp2[i]);
    }
    aho::build();

    getline(cin,s);
    for (int i = 0; i < Q; i++) {
        getline(cin,s);
        aho::aho(s);
    }
}
