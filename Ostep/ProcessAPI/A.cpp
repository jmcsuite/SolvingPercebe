#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Invalid arguments. Suma A B, imprime A+B" << endl;
        return 0;
    }
    int a = stoi(argv[1]);
    int b = stoi(argv[2]);
    cout << a + b << endl;
}
