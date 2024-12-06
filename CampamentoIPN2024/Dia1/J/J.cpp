#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

string t[6] = {"S", "M", "L", "XL", "XXL", "XXXL"};
map<string, int> mp{{"S", 0}, {"M", 1}, {"L", 2}, {"XL", 3}, {"XXL", 4}, {"XXXL", 5}};

int cc[6]; 


int comma(string x) {
    for (size_t i = 0; i < x.size(); i++) {
        if (x[i] == ',') return i;
    }
    return -1;
}

struct st{
    int id;
    int s1;
    int s2;
    st(int a, int b, int c) : id(c), s1(a), s2(b) {}
};


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < 6; i++) {
        ll x; cin >> x; 
        cc[i] = x;
    }

    ll N; cin >> N;
    vector<ll> ans(N, -1);
    vector<st> in;

    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        int com = comma(s);
        if (com == -1) {
            cc[mp[s]]--;
            if (cc[mp[s]] >= 0) ans[i] = mp[s];
            continue;
        }
        string s1; string s2;
        s1 = s.substr(0, com);
        s2 = s.substr(com+1);
        in.push_back({mp[s1], mp[s2], i});
    }
    sort(in.begin(), in.end(), [](st& a, st& b) {
            return a.s1 < b.s1;
            });

    for (auto& st : in) {
        if (cc[st.s1] > 0) {
            cc[st.s1]--;
            ans[st.id] = st.s1;
            continue;
        }
        if (cc[st.s2] > 0) {
            cc[st.s2]--;
            ans[st.id] = st.s2;
        }
    }
    
    bool se = true;
    for (int i = 0; i < N; i++) if (ans[i] == -1) se = false;
    if (!se) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (int i = 0; i < N; i++) { 
        cout << t[ans[i]] << '\n';
    }
}

