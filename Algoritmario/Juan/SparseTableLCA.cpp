const int maxn=1e5+7;

namespace SparseLCA{
    const int maxPow = 30;
    ll f1[maxn];
    ll depth[2*maxn];
    ll depthAns[2*maxn];
    ll cc=0;
    ll dpVal[2*maxn][maxPow];
    ll dpAns[2*maxn][maxPow];

    void build(int x, int p, int d, vll vadj[maxn]){
        f1[x]=cc;
        depth[cc]=d;
        depthAns[cc]=x;
        cc++;
        for(ll y: vadj[x]){
            if(y==p) continue;
            build(y,x,d+1,vadj);
            depth[cc]=d;
            depthAns[cc]=x;
            cc++;
        }
    }

    void buildPow(ll N){
        for(int i=0; i<(2*N-1); i++){
            dpAns[i][0]=depthAns[i];
            dpVal[i][0]=depth[i];
        }
        for(int j=1; j<maxPow; j++){
            for(int i=0; i<(2*N-1); i++){
                dpAns[i][j]=dpAns[i][j-1];
                dpVal[i][j]=dpVal[i][j-1];
                int nex = i+(1<<(j-1));
                if(nex >= 2*N-1) continue;
                if(dpVal[nex][j-1] < dpVal[i][j]){
                    dpVal[i][j]=dpVal[nex][j-1];
                    dpAns[i][j]=dpAns[nex][j-1];
                }
            }
        }
    }

    ll query(ll a, ll b){
        ll pa = f1[a];
        ll pb = f1[b];
        ll fa = min(pa,pb); ll fb = max(pa,pb);
        ll dis = fb-fa+1;
        ll pp = 63-__builtin_clzll(dis);
        ll nex = fb-(1<<pp)+1;
        ll ans = dpAns[fa][pp];

        if(dpVal[nex][pp] < dpVal[fa][pp]) return dpAns[nex][pp];
        return ans;
    }

    void preprocess(ll x, ll N, vll vadj[maxn]){
        cc=0;
        build(x,x,0,vadj);
        buildPow(N);
    }
}
