
namespace aho{
    vector<string> vs;
    ll val[maxn+1];
    ll smatch[maxn+1];

    ll p[maxn+1];
    ll pChar[maxn+1];
    map<ll,ll> vadj[maxn+1];

    ll nCount=1;
    const long long root=0;

    ll fLink[maxn+1];
    ll oLink[maxn+1];

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
        // match, at T[pos]. If you need the matching P, use vs[smatch[node]]
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
