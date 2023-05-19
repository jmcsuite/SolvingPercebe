#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=200001;
namespace suffix_tree{
    // nodes from [0, sz); //root is 0
    const long long inf = 1e9;
    char s[maxn];
    int to[2*maxn][40];
    int len[2*maxn], fpos[2*maxn], link[2*maxn];
    int node=0, pos=0;
    int sz=1, n=0;

    int lid=0;
    int leaves[2*maxn];

    int make_node(int _pos, int _len){
        fpos[sz] = _pos;
        len[sz] = _len;
        return sz++;
    }

    void go_edge(){
        while(pos>len[to[node][(int)s[n-pos]]]){
            node = to[node][(int)s[n-pos]];
            pos -= len[node];
        }
    }

    void add_letter(int c){
        s[n++] = c;
        pos++;
        int last=0;
        while(pos>0){
            go_edge();
            int edge = s[n-pos];
            int &v = to[node][edge];
            int t = s[fpos[v] + pos - 1];
            if(v == 0){
                v = make_node(n-pos, inf);
                link[last]=node;
                leaves[lid++]=v;
                last=0;
            }
            else if(t == c){
                link[last]=node;
                return;
            }
            else{
                int u = make_node(fpos[v],pos-1);
                to[u][c] = make_node(n-1,inf);
                leaves[lid++]=to[u][c];

                to[u][t] = v;
                fpos[v] += pos-1;
                len[v] -= pos-1;
                v=u;
                link[last] = u;
                last = u;
            }
            if(node == 0) pos--;
            else node=link[node];
        }
    }

    void add_string(string& x){
        ll i=n;
        node=0; pos=0;
        len[0]=inf;
        for(char c: x) add_letter(c);
        for(int j=i; j<n; j++) len[leaves[j]] = n-fpos[leaves[j]];
        len[0]=0;
    }

    ll match_count[2*maxn];
    void match(ll node, string& c, ll mc){
        match_count[node]++;
    }

    void search(string& c){
        ll node=0;
        ll sz=0;
        for(size_t i=0; i<c.size(); i++){
            sz++;
            if(len[node] < sz){ 
                node = to[node][(int)c[i]];
                sz=1;
            }
            ll t = s[fpos[node]+sz-1];
            if(node == 0 || t != c[i]) return;
        }
        match(node,c,c.size());
    }

    void prop(ll node, ll c){
        match_count[node] += c;
        for(int i=0; i<40; i++){
            if(to[node][i] == 0) continue;
            prop(to[node][i], match_count[node]);
        }
    }

    void clear(){
        for(int i=0; i<2*maxn; i++){
            match_count[i]=0;
            len[i]=fpos[i]=link[i]=leaves[i]=0;
            for(int j=0; j<40; j++) to[i][j]=0;
        }
        node=pos=n=lid=0;
        sz=1;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; string copy_s;
    cin>>s;
    for(size_t i=0; i<s.size(); i++) s[i]-='a';
    copy_s = s;
    s.push_back(27);
    ll N; cin>>N;
    vector<string> vs(N); for(int i=0; i<N; i++) cin>>vs[i];
    for(int i=0; i<N; i++){
        for(size_t j=0; j<vs[i].size(); j++) vs[i][j]-='a';
    }

    suffix_tree::add_string(s);
    for(int i=0; i<N; i++) suffix_tree::search(vs[i]);
    suffix_tree::prop(0,0);

    vll dp(s.size());
    for(size_t i=0; i<s.size(); i++){
        dp[i] = suffix_tree::match_count[suffix_tree::leaves[i]];
    }

    string t = copy_s;
    reverse(t.begin(), t.end()); t.push_back(27);
    for(int i=0; i<N; i++) reverse(vs[i].begin(), vs[i].end());
    suffix_tree::clear();
    suffix_tree::add_string(t);
    for(int i=0; i<N; i++) suffix_tree::search(vs[i]);
    suffix_tree::prop(0,0);

    ll ans = 0;
    for(size_t i=0; i<t.size(); i++){
        ll x = suffix_tree::match_count[suffix_tree::leaves[i]];
        ans = (ans + x*dp[s.size() - 1 - i]);
    }
    cout << ans << '\n';
}
         

    


