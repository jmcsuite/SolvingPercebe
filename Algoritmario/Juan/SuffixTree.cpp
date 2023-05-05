const int maxn=100000;

namespace SuffixTree{
    // Nodes go from [1 to nodeCount]
    map<int,int> to[2*maxn];
    ll p[2*maxn];
    ll len[2*maxn];
    ll idx[2*maxn];
    char s[maxn];
    ll link[2*maxn];
    ll n=0; ll j=0; ll pos=0;
    ll node=1;
    const int root=1;
    ll nodeCount=1;

    void subo(){
        while(node != root && link[node] == 0){
            pos -= len[node];
            node = p[node];
        }
    }

    void bajo(){
        while(pos < n-1 && to[node][s[pos]] != 0 && len[to[node][s[pos]]] != -1 && len[to[node][s[pos]]] <= n-pos-1){
            ll tempPos = pos;
            pos+=len[to[node][s[pos]]];
            node = to[node][s[tempPos]];
        }
    }

    void add(char c){
        s[n++] = c;
        bool next = true;
        int prev = 0;

        while(next && j!=n){
            if(node == root) pos=j;
            bajo();
            if(to[node][s[pos]] == 0){
                nodeCount++;
                to[node][s[pos]] = nodeCount;
                p[nodeCount] = node;
                len[nodeCount] = -1;
                idx[nodeCount] = n-1;
                next=true;
                link[prev]=node;
                prev=0;
                j++;
            }else{
                char t = s[idx[to[node][s[pos]]] + n-1-pos];
                if(s[n-1] == t){
                    next=false;
                    link[prev]=node;
                }else{
                    nodeCount++;
                    ll child = to[node][s[pos]];
                    p[child] = nodeCount;
                    if(len[child] != -1) len[child] -= n-1-pos;
                    idx[child] += n-1-pos;
                    idx[nodeCount] = pos;
                    len[nodeCount] = n-1-pos;
                    p[nodeCount]=node;
                    to[node][s[pos]] = nodeCount;

                    nodeCount++;
                    len[nodeCount] = -1;
                    idx[nodeCount] = n-1;
                    p[nodeCount] = nodeCount-1;
                    to[nodeCount-1][s[n-1]] = nodeCount;
                    to[nodeCount-1][t] = child;
                    link[prev]=nodeCount-1;
                    prev = nodeCount-1;
                    next = true;
                    j++;
                }
            }

            if(next && j!=n){
                subo();
                if(node == root) pos = j;
                else node = link[node];
            }
        }
    }

    void setLen(){
        for(int i=1; i<=nodeCount; i++){
            if(len[i] == -1) len[i] = n-idx[i];
        }
    }
}


