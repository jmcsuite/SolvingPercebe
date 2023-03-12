namespace LCA{
    const int maxPow = 30;
    int lifting[maxn][maxPow];
    int in[maxn];
    int out[maxn];
    int timeTransversal=0;

    void clear(){ // CALL THIS
        timeTransversal=0;
    }

    void build(int x, int p, vector<vll>& vadj){
        lifting[x][0] = p;
        in[x]=timeTransversal++;
        for(int i=0; i<maxPow-1; i++){
            lifting[x][i+1] = lifting[lifting[x][i]][i]; 
        }
        for(int y: vadj[x]){
            if(y == p) continue;
            build(y,x,vadj);
        }
        out[x]=timeTransversal++;
    }

    int getKthParent(int x, int k){ // Only if you want to know this
        if(k == 0) return x;
        int nextBit = (k&(-k));
        return getKthParent(lifting[x][__builtin_ctz(k)],k-nextBit);
    }

    bool isAncestor(int x, int y){ // ancestor x of y
        return (in[x] <= in[y] && out[x] >= out[y]);
    }

    int lca(int x, int y){
        if(isAncestor(x,y)) return x;
        if(isAncestor(y,x)) return y;
        //Moving x;
        for(int pow2 = maxPow-1; pow2>=0; pow2--){
            if(!isAncestor(lifting[x][pow2],y)){
                x = lifting[x][pow2];
            }
        }
        return lifting[x][0];
    }
}
