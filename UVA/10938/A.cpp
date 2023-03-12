#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 5002;

namespace LCA{
    const int maxPow = 60;
    int lifting[maxn][maxPow];
    int in[maxn];
    int out[maxn]; 
    int timeTransversal=0;

    void clear(){
        timeTransversal=0;
    }

    void build(int x, int p, vector<vll>& vadj){
        lifting[x][0] = p;
        in[x]=timeTransversal++;
        for(int i=0; i<maxPow-1; i++){
            lifting[x][i+1] = lifting[lifting[x][i]][i];
        }
        for(int y : vadj[x]){
            if(y == p) continue;
            build(y,x,vadj);
        }
        out[x]=timeTransversal++;
    }

    int getKthParent(int x, int k){
        if(k == 0) return x;
        int nextBit = (k&(-k));
        return getKthParent(lifting[x][__builtin_ctz(k)],k-nextBit);
    }

    bool isAncestor(int x, int y){ //ancestor x of y
        return (in[x] <= in[y] && out[x] >= out[y]);
    }

    int lca(int x, int y){
        if(isAncestor(x,y)) return x;
        if(isAncestor(y,x)) return y;
        //Move x;
        for(int pow2 = maxPow-1; pow2>=0; pow2--){
            if(!isAncestor(lifting[x][pow2],y)){
                x = lifting[x][pow2];
            }
        }
        return lifting[x][0];
    }
}
//Construir depths; finalizar solucion

void DFS(ll x, ll p, vector<vll>& vadj, int d, vll& depth){
    depth[x] = d;
    for(int y: vadj[x]){
        if(y == p) continue;
        DFS(y, x, vadj, d+1, depth);
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while(1){
        cin>>N;
        if(N == 0) return 0;
        vector<vll> vadj(N);
        for(int i=0; i<N-1; i++){
            int a,b; cin>>a>>b;
            a--; b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }
        LCA::clear();
        LCA::build(0,0,vadj);
        vll depth(N);
        DFS(0,0, vadj, 0, depth);
        ll Q; 
        cin>>Q;
        /*
        for(int i=0; i<N; i++){
            cout << "LIFTING: " << i+1 << ": ";
            for(int j=0; j<3; j++){
                cout << LCA::lifting[i][j]+1 << ' ';
            }
            cout << endl;
        }*/

        while(Q--){
            int a,b; cin>>a>>b;
            a--; b--;
            int lca = LCA::lca(a,b);
            // cout << "LCA Query " << a+1 << ' ' << b+1 << ": " << lca+1 << endl;
            ll disA = depth[a]-depth[lca];
            ll disB = depth[b]-depth[lca];
            ll disTot = disA+disB;
            if(disA<disB) a = b;
            if(disTot%2 == 0){
                cout << "The fleas meet at " << LCA::getKthParent(a,disTot/2)+1 << ".\n";
                continue;
            }
            ll aa = LCA::getKthParent(a, disTot/2) + 1;
            ll bb = LCA::getKthParent(a, disTot/2 + 1) + 1;
            cout << "The fleas jump forever between " << min(aa,bb) << " and " << max(aa,bb) << ".\n";
        }
    }
} 
