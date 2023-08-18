#include<bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100001;
namespace suffix_tree{
    // nodes from [0, sz); //root is 0
    // maxn = maxn+1 if string has special character
    const long long inf = 1e9;
    char s[maxn];
    int to[2*maxn][28];
    int len[2*maxn], fpos[2*maxn], link[2*maxn];
    int node=0, pos=0;
    int sz=1, n=0;

    int lid=0;

    vpll matches[2*maxn];
    void match(ll node, string& c, ll mc, ll val){
        matches[node].push_back({mc,val});
        // match what now
    }

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
                last=0;
            }
            else if(t == c){
                link[last]=node;
                return;
            }
            else{
                int u = make_node(fpos[v],pos-1);
                to[u][c] = make_node(n-1,inf);

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
        node=0; pos=0;
        len[0]=inf;
        for(char c: x) add_letter(c);
        len[0]=0;
    }

    void search(string& c, ll val){
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
        match(node,c,c.size(),val);
    }

    ll depth[2*maxn];
    vpll vadj[maxn];
    void prop(ll x, vpll& tmp, ll d){
        bool se=true;
        depth[x] = d+len[x];
        for(pll y: matches[x]) tmp.push_back(y);
        for(int i=0; i<28; i++){
            if(to[x][i] == 0) continue;
            se=false;
            prop(to[x][i],tmp,depth[x]);
        }
        if(se){
            len[x] = n-fpos[x];
            depth[x]=d+len[x];
            ll leafPos = n-depth[x];
            for(pll y: tmp) vadj[leafPos].push_back(y);
        }
        tmp.erase(tmp.end()-matches[x].size(), tmp.end());
    }
}

const long long modh = 999999433;
ll hsh(string& s){
    long long pow=31;
    long long h=0;
    for(char c: s){
        h = (h*pow)%modh;
        h = (h + c + 1);
    }
    return h;
}


const long long mod = 1000000007;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<ll,ll> mp;
    vector<string> vs;
    ll N; cin>>N;
    for(int i=0; i<N; i++){
        string s;
        cin>>s;
        for(size_t j=0; j<s.size(); j++) s[j]-='a';
        ll h = hsh(s);
        mp[h]++;
        if(mp[h] == 1) vs.push_back(s);
    }

    string t; cin>>t;
    for(size_t j=0; j<t.size(); j++) t[j]-='a';
    t.push_back(27);

    suffix_tree::add_string(t);
    for(string& s: vs){
        ll h = hsh(s);
        ll c = mp[h];
        suffix_tree::search(s, c);
    }
    vpll tmp;
    suffix_tree::prop(0,tmp,0);
    vector<long long> dp(t.size());
    dp[t.size() - 1]=1;
    for(int i=t.size()-2; i>=0; i--){
        for(pll yy: suffix_tree::vadj[i]){
            dp[i] = dp[i] + (dp[yy.first+i]*(long long)yy.second)%mod;
            dp[i] = dp[i]%mod;
        }
    }
    cout << dp[0] << '\n';
}




