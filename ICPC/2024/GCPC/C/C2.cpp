#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int mod = 999999193;

bool isVar(string& s) {
    if (s.size() != 1) return false;
    if (s[0] >= 'a' && s[0] <= 'z') return true;
    if (s[0] >= 'A' && s[0] <= 'Z') return true;
    return false;
}

string getGeneric(vector<string>& vs) {
    const char t = '#';
    string ans;
    int i = 0;
    for (string& s : vs) {
        if (isVar(s)) ans.push_back(t);
        else ans += s;
        if (i == (int)vs.size() - 1) continue;
        ans += '_';
        i++;
    }
    return ans;
}

const int mv = 40;
const int ran = 120;

void buildPrefixSum(vector<string>& vars, vector<ll>& vl) {
    map<char,ll> mp;
    int p = 1;
    int id = 1;
    for (string& s: vars) {
        if (mp.find(s[0]) == mp.end()) mp[s[0]] = id++;
        vl.push_back(p*mp[s[0]]);
        p = (p*ran)%mod;
    }
    vl[0] = vl[0] % mod;
    for (int i = 1; i < (int)vl.size(); i++) vl[i] = (vl[i] + vl[i-1])%mod;
}

void buildList(vector<string>& input, vector<vector<ll>>& vadj, vector<ll>& idx) {
    vector<string> vars;
    int i = 0;
    for (string& s: input) {
        if (isVar(s)) vars.push_back(s);
        if (isVar(s)) idx.push_back(i);
        i+=s.size()+1;
    }
    vadj.resize(vars.size());
    for (size_t i = 0; i < vars.size(); i++) { 
        vector<string> vs1(vars.begin() + i, vars.end());
        buildPrefixSum(vs1, vadj[i]);
    }
}

vector<int> kmp(string& s) {
    int n = s.size();
    vector<int> vs(n);
    for (int i=1; i < n; i++) {
        int j = vs[i-1];
        while(j!=0 && s[i] != s[j]) {
            j = vs[j-1];
        }
        if (s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}

vector<int> getMatches(string& genA, string& genQ) {
    string c = genQ + "*" + genA;
    vector<int> knuth = kmp(c);
    vector<int> ans;
    for (size_t i = genQ.size(); i < c.size(); i++) {
        if (knuth[i] == (int)genQ.size()) ans.push_back(i-genQ.size()*2);
    }
    return ans;
}

ll getHash(vector<string>& vars) {
    vector<ll> vl; 
    buildPrefixSum(vars, vl);
    return vl[(int)vl.size()-1];
}




int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N; cin >> N;
    vector<string> input(N);
    for (int i = 0; i < N; i++) cin >> input[i];
    string genericInput = getGeneric(input);
    vector<ll> idx;
    vector<vll> prefixList;
    buildList(input, prefixList, idx);
    ll Q; cin >> Q;
    while (Q--) {
        ll M; cin >> M; 
        vector<string> q(M);
        for (int i = 0; i < M; i++) cin >> q[i];
        vector<string> vars;
        int myid = -1;
        int j = 0;
        for (int i = 0; i < M; i++) {
            if (isVar(q[i])) vars.push_back(q[i]);
            if (isVar(q[i]) && myid == -1) myid = j;
            j += q[i].size() + 1;
        }

        string genQ = getGeneric(q);
        vector<int> matches = getMatches(genericInput, genQ);

        if (vars.empty()) {
            cout << (matches.empty() ? "no" : "yes") << endl;
            continue;
        }
        set<int> st; 
        for (int x : matches) st.insert(x);
        ll h = getHash(vars);
        h %= mod; h += mod; h %= mod;
        bool mat = false;
        for (int i = 0; i < (int)prefixList.size(); i++) {
            if (prefixList[i].size() < vars.size()) continue;
            ll h2 = prefixList[i][vars.size() - 1];
            h2%=mod; h2 += mod; h2 %= mod;
            if (h2 == h && (st.find(idx[i]-myid) != st.end())) mat = true;
        }
        cout << (mat ? "yes" : "no") << endl;
    }
}
