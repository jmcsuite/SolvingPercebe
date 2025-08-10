#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxx = 5;
ll mm[maxx][3] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,1}, {1,2,3}};
ll aa[maxx];

namespace Gaus {
const int maxn = 3;
ll mat[maxn][maxn];
ll ans[maxn];

void Jordan(ll n) {
    for (int i=0; i<n; i++) {
        int l=i;
        for (int j=i; j<n; j++) {
            if (mat[j][i] == 1){
                l = j;
                break;
            }
        }

        assert(mat[l][i] == 1);
        for (int j=0; j<n; j++) swap(mat[i][j],mat[l][j]);
        swap(ans[i], ans[l]);

        for (int j=i+1; j<n; j++) {
            ans[j] = (ans[j] - mat[j][i]*ans[i]);
            for (int k=n-1; k>=i; k--) {
                mat[j][k] -= mat[j][i] * mat[i][k];
            }
        }
    }

    for (int i=n-1; i>=0; i--) {
        assert((ans[i] % mat[i][i]) == 0);
        ans[i] = ans[i] / mat[i][i];
        for (int k=i-1; k>=0; k--) {
            ans[k] -= ans[i] * mat[k][i];
        }
    }
}
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i=0; i<maxx; i++) {
        cout << mm[i][0] << ' ' << mm[i][1] << ' ' << mm[i][2] << endl;
        cin >> aa[i];
    }

    for (int i=0; i<maxx; i++) {
        for (int j=i+1; j<maxx; j++) {
            for (int k=j+1; k<maxx; k++) {
                for (int l=k+1; l<maxx; l++) {

                    for (int pp=0; pp<3; pp++) {
                        Gaus::mat[0][pp] = mm[i][pp];
                        Gaus::mat[1][pp] = mm[j][pp];
                        Gaus::mat[2][pp] = mm[k][pp];
                    }
                    Gaus::ans[0] = aa[i];
                    Gaus::ans[1] = aa[j];
                    Gaus::ans[2] = aa[k];
                    Gaus::Jordan(3);
                    ll t = mm[l][0] * Gaus::ans[0] + mm[l][1] * Gaus::ans[1]
                        + mm[l][2] * Gaus::ans[2];
                    if (t == aa[l]) {
                        cout << Gaus::ans[0] << ' ' << Gaus::ans[1] << ' '
                            << Gaus::ans[2] << '\n';
                        return 0;
                    }
                }
            }
        }
    }
}
