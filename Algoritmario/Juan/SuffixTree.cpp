namespace suffix_tree{
    // nodes from [0, sz); //root is 0
    // maxn = maxn+1 if string has special character
    const long long inf = 1e9;
    char s[maxn];
    int to[2*maxn][40];
    int len[2*maxn], fpos[2*maxn], link[2*maxn];
    int node=0, pos=0;
    int sz=1, n=0;

    int lid=0;
    int leaves[2*maxn];

    void match(ll node, string& c, ll mc){
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
        ll i = n;
        node=0; pos=0;
        len[0]=inf;
        for(char c: x) add_letter(c);
        for(int j=i; j<n; j++) len[leaves[j]] = n-fpos[leaves[j]];
        // from [i, n) are leaves
        len[0]=0;
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
}

