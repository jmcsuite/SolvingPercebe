#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

vector<pll> ans;
ll one=0;
ll a,b,c;

const int maxn=2e5;
ll vl[maxn];
ll N;

void setup() {
    ans.clear();
    a = b = c = 0;
    for (int i=0; i<N; i++) {
        if (vl[i] == 1) one=i;
        if (vl[i] == 1) b++;
        else if (vl[i] == 2) c++;
        else a++;
    }
}

void print() {
    cout << ans.size() << '\n';
    for (pll p : ans) cout << ++p.first << ' ' << ++p.second << '\n';
}

void sw() {
    queue<int> q;
    for (int i=0; i<a; i++) if(vl[i]==2) q.push(i);
    queue<int> p;
    for (int i=a+b; i<N; i++) if(vl[i]==0) p.push(i);

    while ((!q.empty()) && (!p.empty())) {
        ll i, j; 
        i = q.front(); q.pop();
        j = p.front(); p.pop();

        if (one < a) {
            ans.push_back({one,j});
            ans.push_back({i,j});

            swap(vl[j],vl[one]);
            swap(vl[i],vl[j]);
            one=i;
        }
        else {
            ans.push_back({i,one});
            ans.push_back({i,j});
            swap(vl[i], vl[one]);
            swap(vl[i], vl[j]);
            one=j;
        }
    }

    if (!q.empty()) {
        ll i = q.front(); q.pop();
        ans.push_back({i,one});
        swap(vl[i], vl[one]);
        one=i;
    }

    if (!p.empty()) {
        ll i = p.front(); p.pop();
        ans.push_back({one, i});
        swap(vl[i], vl[one]);
        one=i;
    }
}

void dd(int x, int beg, int end, int y, int by, int ey) {
    queue<int> q;
    for (int i=beg; i<end; i++) if (vl[i] == x) q.push(i);
    queue<int> p;
    for (int i=by; i<ey; i++) if (vl[i] == y) p.push(i);

    while ((!q.empty()) && (!p.empty())) {
        ll i,j;
        i = q.front(); q.pop();
        j = p.front(); p.pop();
        if (vl[i] > vl[j]) ans.push_back({i,j});
        else ans.push_back({j,i});
        swap(vl[i],vl[j]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) {
        cin>>N;
        for (int i=0; i<N; i++) cin>>vl[i];
        setup();
        vl[one]=3;
        dd(1,0,a,0,a,a+b);
        dd(1,a+b,N,2,a,a+b);
        dd(1,0,a,2,a,a+b);
        dd(1,a+b,N,0,a,a+b);
        vl[one]=1;

        sw();
        dd(1,0,a,0,a,a+b);
        dd(1,a+b,N,2,a,a+b);
        print();
    }
}
