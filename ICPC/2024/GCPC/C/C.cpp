#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

bool isvar(string& s) {
    if (s.size() != 1) return false;
    if (s[0] >= 'a' && s[0] <= 'z') return true;
    if (s[0] >= 'A' && s[0] <= 'Z') return true;
    return false;
}

string getformat(vector<string>::iterator begin, vector<string>::iterator end) {
    string ans;
    int i = 0;
    map<char,int> mp;
    for (;begin != end; begin++) {
        if (!isvar(*begin)) {
            for (char c: *begin) ans.push_back(c);
            ans.push_back('_');
            continue;
        }
        if (mp.find(begin[0][0]) == mp.end()) mp[begin[0][0]] = i++;
        ans.push_back('a' + mp[begin[0][0]]);
        ans.push_back('_');
        if (i > 'z') i = 'A'-'a';
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vector<string> vs(N);
    vector<string> suffix(N);
    for (int i = 0; i < N; i++) cin >> vs[i];
    for (int i = 0; i < N; i++) suffix[i] = getformat(vs.begin()+i, vs.end());
    sort(suffix.begin(), suffix.end());

    ll Q; cin >> Q; 
    while (Q--) {
        ll M; cin >> M;
        vector<string> vq(M);
        for (int i = 0; i < M; i++) cin >> vq[i];
        string s = getformat(vq.begin(), vq.end());

        ll ans = N, dis = N;
        while (dis) {
            if (ans - dis >= 0 && suffix[ans-dis] >= s) ans-=dis;
            else dis/=2;
        }
        if (ans == N || suffix[ans].size() < s.size()) {
            cout << "no\n";
            continue;
        }
        bool se = true;
        for (size_t i = 0; i < s.size(); i++) {
            if (s[i] != suffix[ans][i]) se = false;
        }
        cout << (se ? "yes\n" : "no\n");
    }
}
