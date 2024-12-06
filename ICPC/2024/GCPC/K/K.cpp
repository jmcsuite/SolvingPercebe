#include <bits/stdc++.h>
using namespace std;
using ll = long long;

char th(char a) {
    switch(a) {
        case 'p':
            return 'q';
        case 'q':
            return 'p';
        case 'b':
            return 'd';
        case 'd':
            return 'b';
        default:
            return '0';
    }
}

char tv(char a) {
    switch(a) {
        case 'p':
            return 'b';
        case 'b':
            return 'p';
        case 'q':
            return 'd';
        case 'd':
            return 'q';
        default:
            return '0';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s; cin >> s;
    string q; cin >> q;
    map<char, int> mp;
    for (char c: q) mp[c]++;
    if (mp['h']%2) {
        reverse(s.begin(), s.end());
        for (char& c: s) c = th(c);
    }
    if (mp['r']%2) {
        reverse(s.begin(), s.end());
        for (char& c: s) c = tv(c);
        for (char& c: s) c = th(c);
    }
    if (mp['v']%2) {
        for (char& c: s) c = tv(c);
    }
    cout << s << '\n';
}
