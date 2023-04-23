#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=100000;

namespace SuffixTree{
    map<int,int> to[2*maxn];
    ll p[2*maxn];
    ll len[2*maxn];
    ll idx[2*maxn];
    char s[2*maxn];
    ll link[2*maxn];
    ll n=0; ll j=0; ll pos=0; //[j, n] // pos es el caracter que busco
    ll node=1;
    const int root = 1;
    ll nodeCount=1;

    void subo(){
        while(node != root && link[node] == 0){
            pos -= len[node];
            node = p[node];
        }
    }

    void bajo(){
        // bajo al n-1
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
        //cout << "I start with : " << node << ' ' << j << ' ' << pos << endl;
        while(next && j != n){
            if(node == root) pos = j;
            //cout << "NODE after up: " << node << endl;
            //cout << "NODE before down: " << node << ' ' << pos << endl;
            bajo();
            //cout << "NODE after down: " << node << ' ' << pos << endl;
            if(to[node][s[pos]] == 0){
                nodeCount++;
                to[node][s[pos]] = nodeCount;
                p[nodeCount] = node;
                len[nodeCount]= -1;
                idx[nodeCount] = n-1;
                next=true;
                link[prev]=node;
                prev = 0;
                j++;

                //creo nodo
            }else{
                char t = s[idx[to[node][s[pos]]] + n-1-pos];
                //cout << "THIS IS t: " << t << endl;
                if(s[n-1] == t){
                    // rule 3
                    next=false;
                    link[prev]=node;
                }
                else{
                    nodeCount++;
                    ll child = to[node][s[pos]];
                    p[child] = nodeCount;
                    if(len[child] != -1) len[child] -= n-1-pos;
                    idx[child]+= n-1-pos;
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
            //cout << "NEXT VALUE: " << next << ' ' << pos << endl;
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
    ll sz[2*maxn];

    void print(){
        for(int i=1; i<= nodeCount; i++){
            cout << "Node: " << i << " len: " << len[i] << " size: " << sz[i] << endl;
            for(char a='a'; a<='z'; a++){
                if(to[i][a] != 0){
                    cout << "i to: " << a << " , " << to[i][a] << endl;
                }
            }
        }
    }


    void setSz(ll x){
        for(char i='a'; i<='z'; i++){
            if(to[x][i] == 0) continue;
            setSz(to[x][i]);
            sz[x] += sz[to[x][i]];
            sz[x] += len[to[x][i]];
        }
    }

    string ans;
    void solve(ll x, ll cant){
        //cout << "Solve: " << x << ' ' << cant << endl;
        for(char i='a'; i<='z'; i++){
            if(to[x][i] == 0) continue;
            if(len[to[x][i]] >= cant){
                for(int j=idx[to[x][i]]; cant > 0; j++, cant--){
                    ans += s[j];
                }
                return;
            }
            if(len[to[x][i]] + sz[to[x][i]] >= cant){
                for(int j=idx[to[x][i]], k=0; k<len[to[x][i]]; k++,j++){
                    ans+=s[j];
                }
                solve(to[x][i], cant-len[to[x][i]]);
                return;
            }
            cant-=len[to[x][i]] + sz[to[x][i]];
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin>>s;
    for(char i: s){
        SuffixTree::add(i);
    }
    SuffixTree::setLen();
    SuffixTree::setSz(SuffixTree::root);
    //SuffixTree::print();
    ll N; cin>>N;
    SuffixTree::solve(SuffixTree::root, N);
    cout << SuffixTree::ans << endl;
}
