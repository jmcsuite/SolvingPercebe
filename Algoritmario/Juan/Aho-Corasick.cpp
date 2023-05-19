
namespace aho{
    vector<string> vs;
    ll val[maxn+1];
    ll smatch[maxn+1];

    ll p[maxn+1];
    ll pchar[maxn+1];
    map<ll,ll> vadj[maxn+1];

    ll nCount=1;
    const long long root=0;

    ll flink[maxn+1];
    ll olink[maxn+1];

    void addString(string& s,ll id){
        ll i=root;
        for(char c: s){
            if(vadj[i].find(c) != vadj[i].end()){
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
        val[i]++; 
    }


    void build(){
        for(int i=0; i<maxn; i++) smatch[i]=-1;
        pchar[root]=-1;
        ll id=0;

        for(string& s: vs) addString(s,id++);
        queue<ll> q; q.push(root);

        while(!q.empty()){
            ll x=q.front(); q.pop();
            for(pll yy: vadj[x]) q.push(yy.second);

            ll nx = flink[p[x]];
            ll c = pchar[x];
            while(nx != root && vadj[nx].find(c) == vadj[nx].end()) nx = flink[nx];

            if(vadj[nx].find(c) == vadj[nx].end() || vadj[nx][c] == x) flink[x]=root;
            else flink[x]=vadj[nx][c];

            if(smatch[flink[x]] != -1) olink[x] = flink[x];
            else olink[x] = olink[flink[x]];


        }
    }

    void match(ll node, ll pos){
        // match, at T[pos]. If you need the matching P, use vs[smatch[node]]
    }

    void aho(string& T){
        ll x=root;
        for(int c=0; c<(ll)T.size(); c++){
            while(x != root && vadj[x].find(T[c]) == vadj[x].end()) x = flink[x];
            if(vadj[x].find(T[c]) == vadj[x].end()) continue;
            x = vadj[x][T[c]];
            if(smatch[x] != -1) match(x,c);
            ll mx = olink[x];
            while(mx != root){
                match(mx,c);
                mx = olink[mx];
            }
        }
    }
}
