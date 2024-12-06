#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll sum(int a, int b) {
    long long bit = 1;
    long long carry = 0;
    long long ans = 0;

    while (bit  <= a || bit <= b) {
        long long current = (a&bit) ^ (b&bit) ^ (carry);
        ans |= current;
        //cout << bit << ' ' << carry << ' ' << (a&bit) << ' ' << (b&bit) << ' ' << ans << endl;
        carry = ( ((a&bit) & (b&bit)) | ( (b&bit) & carry) | (carry & (a&bit))) << 1;
        bit <<= 1;
    }
    ans |= carry;
    return ans;
}

int main () {
    srand(time(NULL));
    ll a = rand();
    ll b = rand();
    //ll a = 14;
    //ll b = 16;

    //cout << a << ' ' << b << ' ' << sum(a,b) << '\n';
    assert( (a+b) == sum(a,b));
}
