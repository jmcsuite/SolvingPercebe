#include<bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 1000000;
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

    ll mask[2*maxn];
    int it=0;
    void add_string(string& x){
        ll i=n;
        node=0; pos=0;
        len[0]=inf;
        for(char c: x) add_letter(c);
        for(int j=i; j<n; j++) {
            len[leaves[j]] = n-fpos[leaves[j]];
            mask[leaves[j]] = 1<<it;
        }
        it++;
        len[0]=0;
    }

    ll depth[2*maxn];
    ll ans=0;
    void build(ll x, ll d){
        depth[x] = len[x]+d;
        for(size_t i=0; i< 40; i++){
            if(to[x][i] == 0) continue;
            build(to[x][i], depth[x]);
            mask[x] |= mask[to[x][i]];
        }
        if(__builtin_popcount(mask[x]) == it) ans = max(ans, depth[x]);
    }
}

int main(){
    string s;
    ll it = 'z'+1;
    while(getline(cin,s)){
        s.push_back(it);
        for(size_t i=0; i<s.size(); i++) s[i] = s[i]-'a';
        it++;
        suffix_tree::add_string(s);
    }
    suffix_tree::build(0,0);
    cout << suffix_tree::ans << '\n';
}

        


        




