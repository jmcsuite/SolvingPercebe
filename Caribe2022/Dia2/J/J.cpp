#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

struct aho{
    vector<string> vs;

    vll val;
    vll smatch;
    vll p;
    vll pChar;
    vll fLink;
    vll oLink;
    vector<map<ll,ll>> vadj;
   

    ll nCount=1;
    const long long root=0;

    void addstring(string& s, ll id){
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
        ll total=1;
        nCount=1;
        for(string& s: vs) total+=s.size();

        val.clear();
        smatch.clear();
        p.clear();
        pChar.clear();
        vadj.clear();
        oLink.clear();
        fLink.clear();

        val.resize(total);
        smatch.resize(total);
        p.resize(total);
        pChar.resize(total);
        fLink.resize(total);
        oLink.resize(total);
        vadj.resize(total);

        for(int i=0; i<total; i++) smatch[i]=-1;
        pChar[root]=-1;
        ll id=0;

        for(string& s: vs) addstring(s,id++);
        queue<ll> q; q.push(root);
        while(!q.empty()){
            ll x=q.front(); q.pop();
            for(pll yy: vadj[x]) q.push(yy.second);
            ll nx=fLink[p[x]];
            ll c = pChar[x];
            while(nx != root && vadj[nx].find(c) == vadj[nx].end()) nx = fLink[nx];

            if(vadj[nx].find(c) == vadj[nx].end() || vadj[nx][c] == x) fLink[x]=root;
            else fLink[x]=vadj[nx][c];

            if(smatch[fLink[x]] != -1) oLink[x] = fLink[x];
            else oLink[x] = oLink[fLink[x]];
        }
    }

    ll ans;
    void match(ll node, ll pos){
        ans++;
    }

    ll ah(string& T){
        ans=0;
        ll x=root;
        for(int c=0; c<(ll)T.size(); c++){
            while(x!=root && vadj[x].find(T[c]) == vadj[x].end()) x = fLink[x];
            if(vadj[x].find(T[c]) == vadj[x].end()) continue;
            x = vadj[x][T[c]];
            if(smatch[x] != -1) match(x,c);
            ll mx = oLink[x];
            while(mx != root){
                match(mx,c);
                mx = oLink[mx];
            }
        }
        return ans;
    }
};


struct multAho{
    const long long maxb = 20;
    vector<vector<aho>> myAhos;

    void merge(aho& a, aho& b){
        for(string& s: b.vs) a.vs.push_back(s);
        a.build();
        return;
    }

    void add(string s){
        aho one; one.vs.push_back(s);
        one.build();
        for(int i=0; i<maxb; i++){
            if(myAhos[i].size() % 2 == 0){
                myAhos[i].push_back(one);
                return;
            }
            merge(one, myAhos[i][myAhos[i].size()-1]);
            myAhos[i].push_back(one);
        }
    }

    ll query(string& T){
        ll ans=0;
        for(int i=0; i<maxb; i++){
            if(myAhos[i].size() % 2 == 0) continue;
            ans += myAhos[i][myAhos[i].size()-1].ah(T);
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    multAho a;
    multAho b;
    a.myAhos.resize(20); b.myAhos.resize(20);
    ll N; cin>>N; 
    for(int i=0; i<N; i++){
        ll q; string t; cin>>q>>t;
        if(q == 1) a.add(t);
        if(q == 2) b.add(t);
        if(q == 3) cout << a.query(t)-b.query(t) << endl;
        /*if(q == 3){
            cout << "in A: " << a.query(t) << endl;
            cout << "in B: " << b.query(t) << endl;
        }*/
    }

}

