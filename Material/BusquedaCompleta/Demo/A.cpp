#include <bits/stdc++.h> // incluye todo.
using namespace std; 
using ll = long long;  


bool check(int a, int b) {
    string aa = to_string(a);
    string bb = to_string(b);

    // **abc
    while (a  < 10000){
        aa  = "0" + aa;
        a*=10;
    }

    while (b < 10000) {
        bb = "0" + bb;
        b*=10;
    }

    //if (a == 79546) cout << bb << endl;

    vector<int> v(10);
    for (char c : aa) v[c-'0']++; // resta ascii
    for (char c : bb) v[c-'0']++;
    // for (int i = 0; i < bb.size(); i++) v[bb[i]-'0']++;
    for (int x : v) if (x != 1) return false; // cheecar freq
    return true;
}
void print (int i , int j) {
    int N = i/j;
    string a = to_string(i);
    string b = to_string(j);

    if (i < 10000) a = "0" + a; //  numero mas chico de 5 dig
    if (j < 10000) b = "0" + b;
    cout << a << " / " << b << " = " << N << '\n';
}

int main () {
    ios::sync_with_stdio(0); // rutinas fast io
    cin.tie(0);
    ll N; // long long N = basura;
    bool first = true;
    while (cin >> N, N) { 
        if (!first) cout << '\n';
        first = false;
        bool ans = false;
       for (int i = 1000 ; i < 100000; i++) {
           if (i%N != 0) continue; /// abcde / fghtn = N -> abcde / N = fghtn
           if (check(i, i/N)) {
                   ans = true;
                   print(i, i/N);
           }
       }
       if (ans) continue;
       cout << "There are no solutions for " << N << ".\n";
    }
}
