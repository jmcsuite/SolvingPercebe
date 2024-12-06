#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=200001;
const long long mod = 1000000007;

namespace aho{
    vector<string> vs;
    ll val[maxn];
    ll smatch[maxn];

    ll p[maxn];
    ll pChar[maxn];
    map<ll,ll> vadj[maxn];

    ll nCount=1;
    const long long root=0;

    ll dp[maxn]; 

    ll fLink[maxn];
    ll oLink[maxn];

    void addString(string& s,ll id){
        ll i=root;
        for(char c: s){
            if(vadj[i].find(c) != vadj[i].end()){
                i = vadj[i][c];
                continue;
            }
            ll node = nCount++;
            p[node]=i;
            pChar[node]=c;
            vadj[i][c]=node;
            i=node;
        }
        smatch[i]=id;
        val[i]++; 
    }


    void build(){
        for(int i=0; i<maxn; i++) smatch[i]=-1;
        pChar[root]=-1;
        ll id=0;

        for(string& s: vs) addString(s,id++);
        queue<ll> q; q.push(root);

        while(!q.empty()){
            ll x=q.front(); q.pop();
            for(pll yy: vadj[x]) q.push(yy.second);

            ll nx = fLink[p[x]];
            ll c = pChar[x];
            while(nx != root && vadj[nx].find(c) == vadj[nx].end()) nx = fLink[nx];

            if(vadj[nx].find(c) == vadj[nx].end() || vadj[nx][c] == x) fLink[x]=root;
            else fLink[x]=vadj[nx][c];

            if(smatch[fLink[x]] != -1) oLink[x] = fLink[x];
            else oLink[x] = oLink[fLink[x]];


        }
    }

    void match(ll node, ll pos){
        ll sid = smatch[node];
        ll sz = vs[sid].size();
        if(pos-sz < 0) dp[pos] = val[node];
        else dp[pos] = (dp[pos]+dp[pos-sz]*val[node])%mod;
    }

    void aho(string& T){
        ll x=root;
        for(int c=0; c<(ll)T.size(); c++){
            while(x != root && vadj[x].find(T[c]) == vadj[x].end()) x = fLink[x];
            if(vadj[x].find(T[c]) == vadj[x].end()) continue;
            x = vadj[x][T[c]];
            if(smatch[x] != -1) match(x,c);
            ll mx = oLink[x];
            while(mx != root){
                match(mx,c);
                mx = oLink[mx];
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M; cin>>M;
    for(int i=0; i<M; i++){
        string s; cin>>s;
        for(size_t j=0; j<s.size(); j++) s[j]-='a';
        aho::vs.push_back(s);
    }

    string t; cin>>t;
    for(size_t j=0; j<t.size(); j++) t[j]-='a';
    aho::build();
    aho::aho(t);
    cout << aho::dp[t.size()-1] << '\n';
}



    
