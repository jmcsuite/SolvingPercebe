#include<bits/stdc++.h>
using namespace std;
using ll = long long;


int main(int argc, char** argv){
    int n = stoi(argv[1]);
    int N = n;
    cout << 1 << '\n';
    cout << n << '\n';
    for(int i=1; i<N; i++){
        cout << i << ' ' << i+1 << ' ' << 10000 << ' ' << 0 << '\n';
    }
    cout << 2 << '\n';
    cout << 1 << ' ' << n << '\n';
    cout << n << ' ' << 1 << '\n';
}

